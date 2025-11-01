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

bool PlayerAudio::loadFile(const juce::File& file)
{
    if (file.existsAsFile())
    {
        if (auto* reader = formatManager.createReaderFor(file))
        {
            transportSource.stop();
            transportSource.setSource(nullptr);
            readerSource.reset();

            readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);

            transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
            lastLoadedFile = file;
            transportSource.start();
            return true;
        }
    }
    return false;
}

void PlayerAudio::start() { transportSource.start(); }
void PlayerAudio::stop() { transportSource.stop(); }
void PlayerAudio::setGain(float gain) { transportSource.setGain(gain); }
void PlayerAudio::setPosition(double pos) { transportSource.setPosition(pos); }
double PlayerAudio::getPosition() const { return transportSource.getCurrentPosition(); }
double PlayerAudio::getLength() const { return transportSource.getLengthInSeconds(); }
bool PlayerAudio::isPlaying() const { return transportSource.isPlaying(); }

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
