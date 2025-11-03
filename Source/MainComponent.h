#pragma once // MainComponent.h
#include <JuceHeader.h>
#include "PlayerGUI.h"

class MainComponent : public juce::AudioAppComponent,
                      public juce::DragAndDropContainer,
                      public juce::Slider::Listener
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;
    void releaseResources() override;
    void resized() override;
    void paint(juce::Graphics& g) override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    PlayerGUI player1;
	PlayerGUI player2;
    
    // Mixer controls
    juce::Slider track1VolumeSlider;
    juce::Slider track2VolumeSlider;
    juce::Label track1VolumeLabel;
    juce::Label track2VolumeLabel;
    juce::Label mixerTitleLabel;
    
    // Player labels
    juce::Label player1Label;
    juce::Label player2Label;
    
    // Temporary buffer for mixing
    juce::AudioBuffer<float> tempBuffer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
