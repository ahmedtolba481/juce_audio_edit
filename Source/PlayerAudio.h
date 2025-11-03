#pragma once
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

    const AudioMetadata& getMetadata() const { return metadata; }

    juce::File getLastLoadedFile() const { return lastLoadedFile; }

    // A-B Loop functionality
    void setABLoopEnabled(bool enabled);
    bool isABLoopEnabled() const { return abLoopEnabled; }
    void setPointA(double timeInSeconds);
    void setPointB(double timeInSeconds);
    void clearABLoop();
    double getPointA() const { return pointA; }
    double getPointB() const { return pointB; }
    bool hasValidABLoop() const { return pointA >= 0.0 && pointB > pointA; }
   
    /** Returns true if position A is set for A-B looping */
    bool isPositionSetA() const;
    
    /** Returns true if position B is set for A-B looping */
    bool isPositionSetB() const;
    
    /** Clears position A */
    void clearPositionA();
    
    /** Clears position B */
    void clearPositionB();
    // Unload Files
    void unloadFile();
    
    // Waveform functionality
    std::vector<float> getWaveformData() const;
    void generateWaveform(const juce::File& file);
    
    // Async waveform generation
    class WaveformGeneratorThread;
    class WaveformListener
    {
    public:
        virtual ~WaveformListener() = default;
        virtual void waveformDataReady() = 0;
    };
    void setWaveformListener(WaveformListener* listener) { waveformListener = listener; }
    void generateWaveformAsync(const juce::File& file);
    bool isWaveformGenerating() const;

    // Advanced Audio Processing - Effects
    void setReverbEnabled(bool enabled) { reverbEnabled = enabled; }
    void setReverbRoomSize(float roomSize);
    void setReverbWetLevel(float wetLevel);
    float getReverbRoomSize() const { return reverbRoomSize; }
    void setDelayEnabled(bool enabled) { delayEnabled = enabled; }
    void setDelayTime(float delayMs) { delayTimeMs = delayMs; }
    void setDelayFeedback(float feedback) { delayFeedback = feedback; }
    float getDelayFeedback() const { return delayFeedback; }
    
private:
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::ResamplingAudioSource resampler{ &transportSource, false, 2 };
    juce::AudioTransportSource transportSource;

    bool isLooping = false;

    // A-B Loop members
    bool abLoopEnabled = false;
    double pointA = -1.0;  // -1 means not set
    double pointB = -1.0;  // -1 means not set
    void checkABLoop();

    // Metadata
    juce::File lastLoadedFile;
    float lastVolume = 1.0f;
    float lastSpeed = 1.0f;
    AudioMetadata metadata;
    void extractMetadata(const juce::File& file);
    juce::String convertTagLibString(const TagLib::String& str);
    
    // Waveform data
    std::vector<float> waveformData;
    std::unique_ptr<WaveformGeneratorThread> waveformThread;
    mutable juce::CriticalSection waveformDataLock;
    WaveformListener* waveformListener = nullptr;
    
    // Advanced Audio Processing - Effects
    juce::Reverb reverb;
    juce::Reverb::Parameters reverbParams;
    
    bool reverbEnabled = false;
    float reverbRoomSize = 0.5f;
    float reverbWetLevel = 0.3f;
    
    bool delayEnabled = false;
    float delayTimeMs = 200.0f;
    float delayFeedback = 0.3f;
    juce::AudioBuffer<float> delayBuffer;
    int delayBufferSize = 0;
    int delayWritePosition = 0;
    double currentSampleRate = 44100.0;
    
    void processEffects(juce::AudioBuffer<float>& buffer);
    
    // Helper methods
    void setWaveformData(const std::vector<float>& data);
    void stopWaveformGeneration();
};
