#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"

class PlayerGUI : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::Timer  // ADD THIS
    
{
public:
    PlayerGUI();
    ~PlayerGUI() override;
    void resized() override;
    void paint(juce::Graphics& g) override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();
    
    // ADD THIS METHOD
    void timerCallback() override;
    
private:
    PlayerAudio playerAudio;
    bool isMuted = false;
    bool isLooping = false;
    float previousGain = 0.4f;
    
    juce::File lastFile;
    double lastPosition = 0.0;
    double lastVolume = 0.5;
    double lastSpeed = 1.0;
    juce::String lastFullTime;
    bool mutedState = false;
    // GUI elements


 
    juce::ImageButton loadButton;
    juce::Image loadimage;
    juce::ImageButton PlayButton;
    juce::Image playimage;
    juce::Image pauseimage;
    juce::ImageButton restartButton;
    juce::Image restartimage;
    juce::ImageButton BeginButton;
    juce::Image beginimage;
    juce::ImageButton EndButton;
    juce::Image endimage;
    juce::ImageButton MuteButton;
    juce::Image mutedImage;
    juce::Image unmutedImage;
    juce::ImageButton LoopButton;
    juce::Image loopimage;
    juce::Image unloopimage;
    juce::ImageButton forwardButton;
    juce::Image forwardimage;
    juce::ImageButton backwardButton;
    juce::Image backwardimage;
	juce::TextButton loadLast{ "Load Last Session" };
    juce::Slider volumeSlider;
    juce::Slider speedslider;
    juce::Label volumeLabel;
    juce::Label speedLabel;
    
    // ADD THESE NEW MEMBERS FOR POSITION SLIDER
    juce::Slider positionSlider;
    juce::Label currentTimeLabel;
    juce::Label totalTimeLabel;
    bool isDraggingSlider = false;
    
    std::unique_ptr<juce::FileChooser> fileChooser;
    
    // Event handlers
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
    
    // ADD THESE HELPER METHODS
    juce::String formatTime(double timeInSeconds);
    void updatePositionSlider();
    std::unique_ptr<juce::PropertiesFile> propertiesFile;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};
