#include "MainComponent.h"

MainComponent::MainComponent()
{
	addAndMakeVisible(player1);
	addAndMakeVisible(player2);
	
	// Set up shared playlist - player1 is the master, player2 uses player1's playlist
	player2.setSharedPlaylistSource(&player1);
	
	// Set up cross-references between players for mixer buttons
	player1.setOtherPlayer1(&player1);  // Player1's "Mixer 1" button plays on player1
	player1.setOtherPlayer2(&player2);  // Player1's "Mixer 2" button plays on player2
	player2.setOtherPlayer1(&player1);  // Player2's "Mixer 1" button plays on player1
	player2.setOtherPlayer2(&player2);  // Player2's "Mixer 2" button plays on player2
	
	// Setup mixer controls - Track 1 volume slider
	track1VolumeSlider.setRange(0.0, 1.0, 0.01);
	track1VolumeSlider.setValue(0.5);
	track1VolumeSlider.setSliderStyle(juce::Slider::LinearVertical);
	track1VolumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
	track1VolumeSlider.setColour(juce::Slider::trackColourId, juce::Colour(0xFF4A90E2));
	track1VolumeSlider.setColour(juce::Slider::thumbColourId, juce::Colour(0xFF5A9EF0));
	track1VolumeSlider.addListener(this);
	addAndMakeVisible(track1VolumeSlider);
	
	// Track 2 volume slider
	track2VolumeSlider.setRange(0.0, 1.0, 0.01);
	track2VolumeSlider.setValue(0.5);
	track2VolumeSlider.setSliderStyle(juce::Slider::LinearVertical);
	track2VolumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
	track2VolumeSlider.setColour(juce::Slider::trackColourId, juce::Colour(0xFFE74C3C));
	track2VolumeSlider.setColour(juce::Slider::thumbColourId, juce::Colour(0xFFFF5555));
	track2VolumeSlider.addListener(this);
	addAndMakeVisible(track2VolumeSlider);
	
	// Labels
	track1VolumeLabel.setText("Track 1", juce::dontSendNotification);
	track1VolumeLabel.setJustificationType(juce::Justification::centred);
	track1VolumeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
	addAndMakeVisible(track1VolumeLabel);
	
	track2VolumeLabel.setText("Track 2", juce::dontSendNotification);
	track2VolumeLabel.setJustificationType(juce::Justification::centred);
	track2VolumeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
	addAndMakeVisible(track2VolumeLabel);
	
	mixerTitleLabel.setText("Mixer", juce::dontSendNotification);
	mixerTitleLabel.setFont(juce::FontOptions(16.0f, juce::Font::bold));
	mixerTitleLabel.setJustificationType(juce::Justification::centred);
	mixerTitleLabel.setColour(juce::Label::textColourId, juce::Colours::white);
	addAndMakeVisible(mixerTitleLabel);
	
	// Player labels
	player1Label.setText("Player 1", juce::dontSendNotification);
	player1Label.setFont(juce::FontOptions(18.0f, juce::Font::bold));
	player1Label.setJustificationType(juce::Justification::centred);
	player1Label.setColour(juce::Label::textColourId, juce::Colour(0xFF1565C0));
	addAndMakeVisible(player1Label);
	
	player2Label.setText("Player 2", juce::dontSendNotification);
	player2Label.setFont(juce::FontOptions(18.0f, juce::Font::bold));
	player2Label.setJustificationType(juce::Justification::centred);
	player2Label.setColour(juce::Label::textColourId, juce::Colour(0xFFE74C3C));
	addAndMakeVisible(player2Label);
	
    setSize(1600, 800);  // Increased size to accommodate two players side by side and mixer
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
    auto* buffer = bufferToFill.buffer;
    auto numChannels = buffer->getNumChannels();
    auto numSamples = bufferToFill.numSamples;
    auto startSample = bufferToFill.startSample;
    
    // Clear the output buffer first
    buffer->clear(startSample, numSamples);
    
    // Ensure temp buffer is the right size
    if (tempBuffer.getNumChannels() != numChannels || tempBuffer.getNumSamples() < numSamples)
    {
        tempBuffer.setSize(numChannels, numSamples, false, false, true);
    }
    
    float track1Vol = static_cast<float>(track1VolumeSlider.getValue());
    float track2Vol = static_cast<float>(track2VolumeSlider.getValue());
    
    // Get audio from player 1 and mix it in
    if (track1Vol > 0.0f)
    {
        juce::AudioSourceChannelInfo tempInfo(&tempBuffer, 0, numSamples);
        tempBuffer.clear();
        player1.getNextAudioBlock(tempInfo);
        
        // Mix player 1 into output with its volume
        for (int channel = 0; channel < numChannels; ++channel)
        {
            buffer->addFrom(channel, startSample, tempBuffer, channel, 0, numSamples, track1Vol);
        }
    }
    
    // Get audio from player 2 and mix it in
    if (track2Vol > 0.0f)
    {
        juce::AudioSourceChannelInfo tempInfo(&tempBuffer, 0, numSamples);
        tempBuffer.clear();
        player2.getNextAudioBlock(tempInfo);
        
        // Mix player 2 into output with its volume
        for (int channel = 0; channel < numChannels; ++channel)
        {
            buffer->addFrom(channel, startSample, tempBuffer, channel, 0, numSamples, track2Vol);
        }
    }
}

void MainComponent::releaseResources()
{
    player1.releaseResources();
	player2.releaseResources();
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds();
    
    // Mixer at the bottom
    auto mixerHeight = 120;
    auto mixerArea = bounds.removeFromBottom(mixerHeight);
    
    // Title at top of mixer
    mixerTitleLabel.setBounds(mixerArea.removeFromTop(25).reduced(5, 0));
    
    // Volume controls side by side in mixer
    auto volumeArea = mixerArea.reduced(20, 10);
    auto track1Area = volumeArea.removeFromLeft(volumeArea.getWidth() / 2);
    auto track2Area = volumeArea;
    
    // Track 1 controls
    track1VolumeLabel.setBounds(track1Area.removeFromTop(20));
    auto slider1Area = track1Area.reduced(30, 0);
    track1VolumeSlider.setBounds(slider1Area);
    
    // Track 2 controls
    track2VolumeLabel.setBounds(track2Area.removeFromTop(20));
    auto slider2Area = track2Area.reduced(30, 0);
    track2VolumeSlider.setBounds(slider2Area);
    
    // Two players side by side in remaining space
    auto playerWidth = bounds.getWidth() / 2;
    auto player1Bounds = bounds.removeFromLeft(playerWidth);
    auto player2Bounds = bounds;
    
    // Player labels at the top of each player area
    player1Label.setBounds(player1Bounds.removeFromTop(30).reduced(5, 5));
    player2Label.setBounds(player2Bounds.removeFromTop(30).reduced(5, 5));
    
    // Set player bounds
    player1.setBounds(player1Bounds);
    player2.setBounds(player2Bounds);
}

void MainComponent::paint(juce::Graphics& g)
{
    // Paint mixer background
    auto mixerArea = getLocalBounds().removeFromBottom(120);
    auto mixerBounds = mixerArea.toFloat();
    
    // Background with rounded corners
    g.setColour(juce::Colour(0xFF2C3E50));
    g.fillRoundedRectangle(mixerBounds, 5.0f);
    
    // Border
    g.setColour(juce::Colour(0x40FFFFFF));
    g.drawRoundedRectangle(mixerBounds.reduced(0.5f), 5.0f, 1.0f);
    
    // Draw separator line between players (more visible)
    auto bounds = getLocalBounds();
    bounds.removeFromBottom(120); // Remove mixer area
    auto separatorX = bounds.getWidth() / 2;
    g.setColour(juce::Colour(0x80FFFFFF)); // More visible (50% opacity instead of 25%)
    g.drawLine(separatorX, bounds.getY(), separatorX, bounds.getBottom(), 2.5f);
}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    // Mixer volume sliders - volume is applied during mixing in getNextAudioBlock
    // No additional action needed here
}


