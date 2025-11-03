#include "MainComponent.h"

MainComponent::MainComponent()
{
	addAndMakeVisible(player1);
	addAndMakeVisible(player2);
    setSize(800, 350);  // Increased height to accommodate metadata at top
    setAudioChannels(0, 2);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
	player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    player1.getNextAudioBlock(bufferToFill);
	player2.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    player1.releaseResources();
	player2.releaseResources();
}

void MainComponent::resized()
{
	player1.setBounds(getLocalBounds());
	player2.setBounds(getLocalBounds().withTop(getHeight() / 2).withHeight(getHeight() / 2));
}


