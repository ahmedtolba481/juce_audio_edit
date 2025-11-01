#include "PlayerAudio.h"

PlayerAudio::PlayerAudio()
{
    formatManager.registerBasicFormats();
}

PlayerAudio::~PlayerAudio()
{
}

void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampler.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    resampler.getNextAudioBlock(bufferToFill);
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
    resampler.setResamplingRatio(ratio);
}
