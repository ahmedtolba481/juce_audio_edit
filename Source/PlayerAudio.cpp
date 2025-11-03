#include "PlayerAudio.h"
#include <juce_dsp/juce_dsp.h>
PlayerAudio::PlayerAudio()
{
    formatManager.registerBasicFormats();
}

PlayerAudio::~PlayerAudio()
{
    // Stop waveform generation thread in destructor
    stopWaveformGeneration();
}

void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampler.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    // Initialize effects
    currentSampleRate = sampleRate;
    
    // Prepare DSP effects
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(samplesPerBlockExpected);
    spec.numChannels = static_cast<juce::uint32>(2);
    
    reverb.prepare(spec);
    
    // Initialize reverb parameters
    reverbParams.roomSize = reverbRoomSize;
    reverbParams.wetLevel = reverbWetLevel;
    reverbParams.dryLevel = 1.0f - reverbWetLevel;
    reverb.setParameters(reverbParams);
    
    // Initialize delay buffer
    delayBufferSize = static_cast<int>(sampleRate * 2.0); // 2 seconds max delay
    delayBuffer.setSize(2, delayBufferSize, false, true);
    delayWritePosition = 0;
}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    resampler.getNextAudioBlock(bufferToFill);
    
    // Process audio effects
    processEffects(*bufferToFill.buffer);
    
    // Check A-B loop boundaries after getting audio block
    if (abLoopEnabled && transportSource.isPlaying())
    {
        checkABLoop();
    }
}

void PlayerAudio::releaseResources()
{
    resampler.releaseResources();
    transportSource.releaseResources();
}

juce::String PlayerAudio::convertTagLibString(const TagLib::String& str)
{
    if (str.isEmpty())
        return juce::String();

#ifdef _WIN32
    // TagLib::String::toWString() returns std::wstring, but juce::String does not have a direct constructor for std::wstring.
    // Convert std::wstring to juce::String using CharPointer_UTF16.
    std::wstring wstr = str.toWString();
    return juce::String(juce::CharPointer_UTF16(wstr.c_str()));
#else
    return juce::String(juce::CharPointer_UTF8(str.toCString(true)));
#endif
}

void PlayerAudio::extractMetadata(const juce::File& file)
{
    // Reset metadata
    metadata = AudioMetadata();
    metadata.filename = file.getFileNameWithoutExtension();

    try
    {
        // Create TagLib file reference
#ifdef _WIN32
        TagLib::FileRef tagFile(file.getFullPathName().toWideCharPointer());
#else
        TagLib::FileRef tagFile(file.getFullPathName().toRawUTF8());
#endif

        if (!tagFile.isNull())
        {
            // Extract tag information
            TagLib::Tag* tag = tagFile.tag();
            if (tag && !tag->isEmpty())
            {
                metadata.hasMetadata = true;
                metadata.title = convertTagLibString(tag->title());
                metadata.artist = convertTagLibString(tag->artist());
                metadata.album = convertTagLibString(tag->album());
                metadata.genre = convertTagLibString(tag->genre());

                unsigned int year = tag->year();
                if (year > 0)
                    metadata.year = juce::String(year);
            }

            // Extract audio properties
            TagLib::AudioProperties* properties = tagFile.audioProperties();
            if (properties)
            {
                metadata.duration = properties->lengthInSeconds();
                metadata.bitrate = properties->bitrate();
                metadata.sampleRate = properties->sampleRate();
                metadata.channels = properties->channels();
            }
        }
    }
    catch (const std::exception& e)
    {
        DBG("TagLib error: " << e.what());
        metadata.hasMetadata = false;
    }
    catch (...)
    {
        DBG("Unknown TagLib error");
        metadata.hasMetadata = false;
    }
}

bool PlayerAudio::loadFile(const juce::File& file)
{
    if (file.existsAsFile())
    {
		lastLoadedFile = file;
        extractMetadata(file);
        
        // Stop any ongoing waveform generation
        stopWaveformGeneration();
        
        // Clear existing waveform data
        {
            juce::ScopedLock lock(waveformDataLock);
            waveformData.clear();
        }
        
        // Generate waveform asynchronously (non-blocking)
        generateWaveformAsync(file);

        if (auto* reader = formatManager.createReaderFor(file))
        {
            // Disconnect old source first
            transportSource.stop();
            transportSource.setSource(nullptr);
            readerSource.reset();

            readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);

            // Attach safely to transportSource 
            transportSource.setSource(readerSource.get(),
                0,
                nullptr,
                reader->sampleRate);
            transportSource.start();
            
            // Clear A-B loop when loading new file
            clearABLoop();
            
            return true;
        }
    }
    return false;
}

void PlayerAudio::start()
{
    transportSource.start();
}

void PlayerAudio::stop()
{
    transportSource.stop();
}

void PlayerAudio::setGain(float gain)
{
    lastVolume = gain;
    transportSource.setGain(gain);
}

void PlayerAudio::setPosition(double pos)
{
    transportSource.setPosition(pos);
}

double PlayerAudio::getPosition() const
{
    return transportSource.getCurrentPosition();
}

double PlayerAudio::getLength() const
{
    return transportSource.getLengthInSeconds();
}

bool PlayerAudio::isPlaying() const
{
    return transportSource.isPlaying();
}

void PlayerAudio::setLooping(bool f)
{
    isLooping = f;
    if (readerSource)
        readerSource->setLooping(f);
    transportSource.setLooping(f);
}

double PlayerAudio::getLengthInSeconds()
{
    return transportSource.getLengthInSeconds();
}

void PlayerAudio::setSpeed(float ratio)
{
    ratio = juce::jlimit(0.25f, 4.0f, ratio);
    lastSpeed = ratio;
    resampler.setResamplingRatio(ratio);
}

// A-B Loop Implementation
void PlayerAudio::setABLoopEnabled(bool enabled)
{
    abLoopEnabled = enabled;
    
    // If enabling A-B loop, disable standard looping
    if (abLoopEnabled)
    {
        setLooping(false);
    }
}

void PlayerAudio::setPointA(double timeInSeconds)
{
    double length = getLengthInSeconds();
    pointA = juce::jlimit(0.0, length, timeInSeconds);
    
    // If point B is already set and is before point A, clear it
    if (pointB >= 0.0 && pointB <= pointA)
    {
        pointB = -1.0;
    }
}

void PlayerAudio::setPointB(double timeInSeconds)
{
    double length = getLengthInSeconds();
    pointB = juce::jlimit(0.0, length, timeInSeconds);
    
    // Ensure point B is after point A
    if (pointA >= 0.0 && pointB <= pointA)
    {
        // Swap if B is set before A
        std::swap(pointA, pointB);
    }
}

void PlayerAudio::clearABLoop()
{
    pointA = -1.0;
    pointB = -1.0;
    abLoopEnabled = false;
}

void PlayerAudio::checkABLoop()
{
    if (!hasValidABLoop())
        return;
    
    double currentPos = getPosition();
    
    // If we've passed point B, jump back to point A
    if (currentPos >= pointB)
    {
        setPosition(pointA);
    }
    // If we're somehow before point A, jump to point A
    else if (currentPos < pointA)
    {
        setPosition(pointA);
    }
}

bool PlayerAudio::isPositionSetA() const
{
    return pointA >= 0.0;
}

bool PlayerAudio::isPositionSetB() const
{
    return pointB >= 0.0;
}

void PlayerAudio::clearPositionA()
{
    pointA = -1.0;
}

void PlayerAudio::clearPositionB()
{
    pointB = -1.0;
}
// Unload Files

void PlayerAudio::unloadFile()
{
    stop();
    transportSource.setSource(nullptr);
    readerSource.reset();
    lastLoadedFile = juce::File();
    
    // Stop waveform generation thread
    stopWaveformGeneration();
    
    // Clear waveform data
    {
        juce::ScopedLock lock(waveformDataLock);
        waveformData.clear();
    }
}

void PlayerAudio::generateWaveform(const juce::File& file)
{
    waveformData.clear();
    
    if (!file.existsAsFile())
        return;
    
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));
    if (reader == nullptr)
        return;
    
    const juce::int64 numSamples = reader->lengthInSamples;
    const int numChannels = reader->numChannels;
    
    if (numSamples <= 0 || numChannels <= 0)
        return;
    
    // Calculate number of peaks to extract
    const int numPeaks = 512; // Adjust this for more/less detail
    const juce::int64 samplesPerPeak = numSamples / numPeaks;
    
    if (samplesPerPeak <= 0)
        return;
    
    waveformData.resize(numPeaks, 0.0f);
    
    // Create audio buffer for reading samples
    juce::AudioBuffer<float> tempBuffer(static_cast<int>(numChannels), static_cast<int>(samplesPerPeak));
    
    // Read audio in chunks and calculate RMS (root mean square) for each peak
    for (int peakIndex = 0; peakIndex < numPeaks; ++peakIndex)
    {
        const juce::int64 startSample = peakIndex * samplesPerPeak;
        const int numSamplesToRead = static_cast<int>(juce::jmin(samplesPerPeak, numSamples - startSample));
        
        if (numSamplesToRead <= 0)
            break;
        
        // Clear buffer first
        tempBuffer.clear();
        
        // Read samples into buffer - JUCE AudioFormatReader::read signature:
        // read(AudioBuffer<float>*, int destStartSample, int numSamples, int64 sourceStartSample, bool fillLeftoverChannels, bool allowSuffixing)
        bool success = false;
        try {
            success = reader->read(&tempBuffer, 0, numSamplesToRead, startSample, true, true);
        } catch (...) {
            // If reading fails, skip this peak
            continue;
        }
        
        if (!success)
            continue;
        
        // Calculate RMS across all channels
        float sumSquared = 0.0f;
        int totalCount = 0;
        const int actualChannels = juce::jmin(numChannels, tempBuffer.getNumChannels());
        
        for (int channel = 0; channel < actualChannels; ++channel)
        {
            const float* channelData = tempBuffer.getReadPointer(channel);
            if (channelData != nullptr)
            {
                for (int sample = 0; sample < numSamplesToRead && sample < tempBuffer.getNumSamples(); ++sample)
                {
                    const float sampleValue = channelData[sample];
                    sumSquared += sampleValue * sampleValue;
                    totalCount++;
                }
            }
        }
        
        if (totalCount > 0)
        {
            float rms = std::sqrt(sumSquared / static_cast<float>(totalCount));
            waveformData[peakIndex] = juce::jlimit(0.0f, 1.0f, rms);
        }
    }
}

// Async waveform generation implementation
class PlayerAudio::WaveformGeneratorThread : public juce::Thread
{
public:
    WaveformGeneratorThread(PlayerAudio* owner, const juce::File& file, juce::AudioFormatManager& manager)
        : Thread("WaveformGenerator"),
          audioOwner(owner),
          targetFile(file),
          formatManager(manager)
    {
    }

    void run() override
    {
        if (!targetFile.existsAsFile())
            return;

        std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(targetFile));
        if (reader == nullptr)
            return;

        const juce::int64 numSamples = reader->lengthInSamples;
        const int numChannels = reader->numChannels;

        if (numSamples <= 0 || numChannels <= 0)
            return;

        // Calculate number of peaks to extract
        const int numPeaks = 512;
        const juce::int64 samplesPerPeak = numSamples / numPeaks;

        if (samplesPerPeak <= 0)
            return;

        std::vector<float> newWaveformData(numPeaks, 0.0f);

        // Create audio buffer for reading samples
        juce::AudioBuffer<float> tempBuffer(static_cast<int>(numChannels), static_cast<int>(samplesPerPeak));

        // Read audio in chunks and calculate RMS (root mean square) for each peak
        for (int peakIndex = 0; peakIndex < numPeaks; ++peakIndex)
        {
            // Check if thread should exit
            if (threadShouldExit())
                return;

            const juce::int64 startSample = peakIndex * samplesPerPeak;
            const int numSamplesToRead = static_cast<int>(juce::jmin(samplesPerPeak, numSamples - startSample));

            if (numSamplesToRead <= 0)
                break;

            // Clear buffer first
            tempBuffer.clear();

            // Read samples into buffer
            bool success = false;
            try {
                success = reader->read(&tempBuffer, 0, numSamplesToRead, startSample, true, true);
            } catch (...) {
                continue;
            }

            if (!success)
                continue;

            // Calculate RMS across all channels
            float sumSquared = 0.0f;
            int totalCount = 0;
            const int actualChannels = juce::jmin(numChannels, tempBuffer.getNumChannels());

            for (int channel = 0; channel < actualChannels; ++channel)
            {
                const float* channelData = tempBuffer.getReadPointer(channel);
                if (channelData != nullptr)
                {
                    for (int sample = 0; sample < numSamplesToRead && sample < tempBuffer.getNumSamples(); ++sample)
                    {
                        const float sampleValue = channelData[sample];
                        sumSquared += sampleValue * sampleValue;
                        totalCount++;
                    }
                }
            }

            if (totalCount > 0)
            {
                float rms = std::sqrt(sumSquared / static_cast<float>(totalCount));
                newWaveformData[peakIndex] = juce::jlimit(0.0f, 1.0f, rms);
            }
        }

        // Update waveform data on the main thread (safely)
        if (audioOwner != nullptr && !threadShouldExit())
        {
            audioOwner->setWaveformData(newWaveformData);
        }
    }

private:
    PlayerAudio* audioOwner;
    juce::File targetFile;
    juce::AudioFormatManager& formatManager;
};

void PlayerAudio::generateWaveformAsync(const juce::File& file)
{
    // Stop any existing waveform generation
    stopWaveformGeneration();

    // Create and start new thread
    waveformThread = std::make_unique<WaveformGeneratorThread>(this, file, formatManager);
    waveformThread->startThread();
}

bool PlayerAudio::isWaveformGenerating() const
{
    return waveformThread != nullptr && waveformThread->isThreadRunning();
}

void PlayerAudio::stopWaveformGeneration()
{
    if (waveformThread != nullptr)
    {
        waveformThread->stopThread(1000);
        waveformThread.reset();
    }
}

std::vector<float> PlayerAudio::getWaveformData() const
{
    juce::ScopedLock lock(waveformDataLock);
    return waveformData;
}

void PlayerAudio::setWaveformData(const std::vector<float>& data)
{
    {
        juce::ScopedLock lock(waveformDataLock);
        waveformData = data;
    }
    
    // Notify listener on message thread
    if (waveformListener != nullptr)
    {
        juce::MessageManager::callAsync([this]()
        {
            if (waveformListener != nullptr)
                waveformListener->waveformDataReady();
        });
    }
}

void PlayerAudio::processEffects(juce::AudioBuffer<float>& buffer)
{
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();
    
    // Process delay
    if (delayEnabled && delayBufferSize > 0)
    {
        const int delaySamples = static_cast<int>((delayTimeMs / 1000.0) * currentSampleRate);
        
        for (int channel = 0; channel < juce::jmin(numChannels, 2); ++channel)
        {
            float* channelData = buffer.getWritePointer(channel);
            float* delayChannelData = delayBuffer.getWritePointer(channel);
            
            for (int i = 0; i < numSamples; ++i)
            {
                const int readPos = (delayWritePosition - delaySamples + delayBufferSize) % delayBufferSize;
                const float delayedSample = delayChannelData[readPos];
                
                // Store current sample with feedback for next time
                delayChannelData[delayWritePosition] = channelData[i] + delayedSample * delayFeedback;
                
                // Mix delayed signal into output
                channelData[i] += delayedSample;
                
                delayWritePosition = (delayWritePosition + 1) % delayBufferSize;
            }
        }
    }
    
    // Process reverb
    if (reverbEnabled)
    {
        reverbParams.roomSize = reverbRoomSize;
        reverbParams.wetLevel = reverbWetLevel;
        reverbParams.dryLevel = 1.0f - reverbWetLevel;
        reverb.setParameters(reverbParams);
        
        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);
        reverb.process(context);
    }
}

void PlayerAudio::setReverbRoomSize(float roomSize) 
{ 
    reverbRoomSize = roomSize; 
    reverbParams.roomSize = roomSize;
    reverb.setParameters(reverbParams);
}

void PlayerAudio::setReverbWetLevel(float wetLevel) 
{ 
    reverbWetLevel = wetLevel; 
    reverbParams.wetLevel = wetLevel;
    reverbParams.dryLevel = 1.0f - wetLevel;
    reverb.setParameters(reverbParams);
}
