#pragma once							// PlayerAudio.h
#include <JuceHeader.h>

// TagLib includes
#include "taglib/fileref.h"
#include "taglib/tag.h"
#include "taglib/audioproperties.h"

// Simple metadata structure
struct AudioMetadata
{
    juce::String title;
    juce::String artist;
    juce::String album;
    juce::String year;
    juce::String genre;
    int duration = 0;
    int bitrate = 0;
    int sampleRate = 0;
    int channels = 0;
    bool hasMetadata = false;
    juce::String filename;
};

class PlayerAudio
{
public:
    PlayerAudio();
    ~PlayerAudio();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

    bool loadFile(const juce::File& file);
    void start();
    void stop();
    void setGain(float gain);
    void setPosition(double pos);
    double getPosition() const;
    double getLength() const;
    bool isPlaying() const;
    void setLooping(bool f);
    double getLengthInSeconds();
    void setSpeed(float ratio);
    juce::String formatTime(double timeInSeconds);
    void updatePositionSlider();
    
    // NEW: Get metadata
    const AudioMetadata& getMetadata() const { return metadata; }
    
private:
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::ResamplingAudioSource resampler{ &transportSource, false, 2 };
    juce::AudioTransportSource transportSource;
    bool isLooping = false;
    
    // NEW: Store metadata
    AudioMetadata metadata;
    
    // NEW: Helper method to extract metadata
    void extractMetadata(const juce::File& file);
    juce::String convertTagLibString(const TagLib::String& str);
};

