#include "PlayerGUI.h"

void PlayerGUI::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playerAudio.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerGUI::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    playerAudio.getNextAudioBlock(bufferToFill);
}

void PlayerGUI::releaseResources()
{
    playerAudio.releaseResources();
}

void PlayerGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey);
}

PlayerGUI::PlayerGUI()
{
    //load button
    loadimage = juce::ImageFileFormat::loadFrom(BinaryData::upload_png, BinaryData::upload_pngSize);
    loadButton.setImages(false, true, true,
        loadimage, 1.0f, juce::Colours::transparentBlack,
        loadimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
        loadimage, 1.0f, juce::Colours::white.withAlpha(0.6f)
    );
    addAndMakeVisible(loadButton);
    loadButton.addListener(this);

    // play button
    playimage = juce::ImageFileFormat::loadFrom(BinaryData::playbuttton_png, BinaryData::playbuttton_pngSize);
    pauseimage = juce::ImageFileFormat::loadFrom(BinaryData::pause_png, BinaryData::pause_pngSize);
    PlayButton.setImages(false, true, true,
        pauseimage, 1.0f, juce::Colours::transparentBlack,
        pauseimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
        playimage, 1.0f, juce::Colours::white.withAlpha(0.6f)
    );
    addAndMakeVisible(PlayButton);
    PlayButton.addListener(this);

    //restart button 
    restartimage = juce::ImageFileFormat::loadFrom(BinaryData::rotate_png, BinaryData::rotate_pngSize);
    restartButton.setImages(false, true, true,
        restartimage, 1.0f, juce::Colours::transparentBlack,
        restartimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
        restartimage, 1.0f, juce::Colours::white.withAlpha(0.6f)
    );
    addAndMakeVisible(restartButton);
    restartButton.addListener(this);

    // Begin button
    beginimage = juce::ImageFileFormat::loadFrom(BinaryData::play__Copy_png, BinaryData::play__Copy_pngSize);
    BeginButton.setImages(false, true, true,
        beginimage, 1.0f, juce::Colours::transparentBlack,
        beginimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
        beginimage, 1.0f, juce::Colours::white.withAlpha(0.6f)
    );
    addAndMakeVisible(BeginButton);
    BeginButton.addListener(this);

    // End button
    endimage = juce::ImageFileFormat::loadFrom(BinaryData::play_png, BinaryData::play_pngSize);
    EndButton.setImages(false, true, true,
        endimage, 1.0f, juce::Colours::transparentBlack,
        endimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
        endimage, 1.0f, juce::Colours::white.withAlpha(0.6f)
    );
    addAndMakeVisible(EndButton);
    EndButton.addListener(this);

    // Mute button
    mutedImage = juce::ImageFileFormat::loadFrom(BinaryData::volumemute_png, BinaryData::volumemute_pngSize);
    unmutedImage = juce::ImageFileFormat::loadFrom(BinaryData::speakerfilledaudiotool_png, BinaryData::speakerfilledaudiotool_pngSize);
    MuteButton.setImages(false, true, true,
        unmutedImage, 1.0f, juce::Colours::transparentBlack,
        unmutedImage, 0.5f, juce::Colours::white.withAlpha(0.3f),
        mutedImage, 1.0f, juce::Colours::white.withAlpha(0.6f)
    );
    addAndMakeVisible(MuteButton);
    MuteButton.addListener(this);

    //loop button
    loopimage = juce::ImageFileFormat::loadFrom(BinaryData::loop_png, BinaryData::loop_pngSize);
    unloopimage = juce::ImageFileFormat::loadFrom(BinaryData::stop_png, BinaryData::stop_pngSize);
    LoopButton.setImages(false, true, true,
        unloopimage, 1.0f, juce::Colours::transparentBlack,
        unloopimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
        loopimage, 1.0f, juce::Colours::white.withAlpha(0.6f)
    );
    addAndMakeVisible(LoopButton);
    LoopButton.addListener(this);

    // forward button
    forwardimage = juce::ImageFileFormat::loadFrom(BinaryData::forward_png, BinaryData::forward_pngSize);
    forwardButton.setImages(false, true, true,
        forwardimage, 1.0f, juce::Colours::transparentBlack,
        forwardimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
        forwardimage, 1.0f, juce::Colours::white.withAlpha(0.6f)
    );
    addAndMakeVisible(forwardButton);
    forwardButton.addListener(this);

    // backward button
    backwardimage = juce::ImageFileFormat::loadFrom(BinaryData::backward_png, BinaryData::backward_pngSize);
    backwardButton.setImages(false, true, true,
        backwardimage, 1.0f, juce::Colours::transparentBlack,
        backwardimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
        backwardimage, 1.0f, juce::Colours::white.withAlpha(0.6f)
    );
    addAndMakeVisible(backwardButton);
    backwardButton.addListener(this);

    // Volume slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.4);
    volumeSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    // Volume label
    volumeLabel.setText("Volume: 0.40", juce::dontSendNotification);
    volumeLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(volumeLabel);

    // Speed slider
    speedslider.setRange(0.25, 4.0, 0.01);
    speedslider.setValue(1.0);
    speedslider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    speedslider.addListener(this);
    addAndMakeVisible(speedslider);

    // Speed label
    speedLabel.setText("Speed: 1.00x", juce::dontSendNotification);
    speedLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(speedLabel);

    // POSITION SLIDER AND TIME LABEL
    positionSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    positionSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    positionSlider.setRange(0.0, 1.0, 0.001);
    positionSlider.setColour(juce::Slider::trackColourId, juce::Colours::blue);
    positionSlider.setColour(juce::Slider::thumbColourId, juce::Colours::darkblue);
    positionSlider.addListener(this);
    addAndMakeVisible(positionSlider);

    currentTimeLabel.setText("00:00", juce::dontSendNotification);
    currentTimeLabel.setJustificationType(juce::Justification::centredLeft);
    currentTimeLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(currentTimeLabel);

    totalTimeLabel.setText("00:00", juce::dontSendNotification);
    totalTimeLabel.setJustificationType(juce::Justification::centredRight);
    totalTimeLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(totalTimeLabel);

    // Start timer to update position slider
    startTimer(10);
}

void PlayerGUI::resized()
{
    int y = 20;
    int buttonWidth = 70;
    int buttonHeight = 35;
    int spacing = 15;

    int numButtons = 9;
    int totalWidth = numButtons * buttonWidth + (numButtons - 1) * spacing;
    int startX = (getWidth() - totalWidth) / 2;

    loadButton.setBounds(startX + (buttonWidth + spacing) * 0, y, buttonWidth, buttonHeight);
    restartButton.setBounds(startX + (buttonWidth + spacing) * 1, y, buttonWidth, buttonHeight);
    BeginButton.setBounds(startX + (buttonWidth + spacing) * 2, y, buttonWidth, buttonHeight);
    PlayButton.setBounds(startX + (buttonWidth + spacing) * 3, y, buttonWidth, buttonHeight);
    EndButton.setBounds(startX + (buttonWidth + spacing) * 4, y, buttonWidth, buttonHeight);
    LoopButton.setBounds(startX + (buttonWidth + spacing) * 5, y, buttonWidth, buttonHeight);
    MuteButton.setBounds(startX + (buttonWidth + spacing) * 6, y, buttonWidth, buttonHeight);
    forwardButton.setBounds(startX + (buttonWidth + spacing) * 7, y, buttonWidth, buttonHeight);
    backwardButton.setBounds(startX + (buttonWidth + spacing) * 8, y, buttonWidth, buttonHeight);

    // ===== NEW: POSITION SLIDER LAYOUT =====
    int positionY = 70;
    currentTimeLabel.setBounds(20, positionY, 60, 20);
    totalTimeLabel.setBounds(getWidth() - 80, positionY, 60, 20);
    positionSlider.setBounds(85, positionY, getWidth() - 170, 20);

    volumeLabel.setBounds(20, 105, 200, 20);
    volumeSlider.setBounds(20, 130, getWidth() - 40, 30);

    speedLabel.setBounds(20, 170, 200, 20);
    speedslider.setBounds(20, 195, getWidth() - 40, 30);
}

PlayerGUI::~PlayerGUI()
{
    stopTimer();
}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select an audio file...",
            juce::File{},
            "*.wav;*.mp3");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file.existsAsFile())
                {
                    playerAudio.loadFile(file);
                    // Update total time label
                    double totalLength = playerAudio.getLengthInSeconds();
                    totalTimeLabel.setText(formatTime(totalLength), juce::dontSendNotification);
                    currentTimeLabel.setText("00:00", juce::dontSendNotification);
                    positionSlider.setValue(0.0, juce::dontSendNotification);
                }
            });
    }

    if (button == &restartButton)
    {
        playerAudio.setPosition(0.0);
        PlayButton.setImages(false, true, true,
            pauseimage, 1.0f, juce::Colours::transparentBlack,
            pauseimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
            playimage, 1.0f, juce::Colours::white.withAlpha(0.6f)
        );
        playerAudio.start();
    }

    if (button == &BeginButton)
    {
        playerAudio.setPosition(0.0);
        playerAudio.stop();

        PlayButton.setImages(false, true, true,
            playimage, 1.0f, juce::Colours::transparentBlack,
            playimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
            pauseimage, 1.0f, juce::Colours::white.withAlpha(0.6f)
        );
    }

    if (button == &EndButton)
    {
        if (isLooping)
        {
            playerAudio.setPosition(0.0);
            playerAudio.start();
            PlayButton.setImages(false, true, true,
                pauseimage, 1.0f, juce::Colours::transparentBlack,
                pauseimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                playimage, 1.0f, juce::Colours::white.withAlpha(0.6f)
            );
        }
        else
        {
            playerAudio.setPosition(playerAudio.getLength() - 0.05);
            playerAudio.stop();

            PlayButton.setImages(false, true, true,
                playimage, 1.0f, juce::Colours::transparentBlack,
                playimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                pauseimage, 1.0f, juce::Colours::white.withAlpha(0.6f)
            );
        }
    }

    if (button == &PlayButton)
    {
        if (playerAudio.isPlaying())
        {
            playerAudio.stop();

            PlayButton.setImages(false, true, true,
                playimage, 1.0f, juce::Colours::transparentBlack,
                playimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                pauseimage, 1.0f, juce::Colours::white.withAlpha(0.6f)
            );
        }
        else
        {
            playerAudio.start();

            PlayButton.setImages(false, true, true,
                pauseimage, 1.0f, juce::Colours::transparentBlack,
                pauseimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                playimage, 1.0f, juce::Colours::white.withAlpha(0.6f)
            );
        }
    }

    if (button == &MuteButton)
    {
        if (isMuted)
        {
            playerAudio.setGain(previousGain);
            volumeSlider.setValue(previousGain);
            isMuted = false;
            MuteButton.setImages(false, true, true,
                unmutedImage, 1.0f, juce::Colours::transparentBlack,
                unmutedImage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                mutedImage, 1.0f, juce::Colours::white.withAlpha(0.6f)
            );
        }
        else
        {
            previousGain = (float)volumeSlider.getValue();
            playerAudio.setGain(0.0f);
            volumeSlider.setValue(0.0);
            isMuted = true;
            MuteButton.setImages(false, true, true,
                mutedImage, 1.0f, juce::Colours::transparentBlack,
                mutedImage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                unmutedImage, 1.0f, juce::Colours::white.withAlpha(0.6f)
            );
        }
    }

    if (button == &LoopButton)
    {
        if (isLooping)
        {
            playerAudio.setLooping(false);
            isLooping = false;
            LoopButton.setImages(false, true, true,
                unloopimage, 1.0f, juce::Colours::transparentBlack,
                unloopimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                loopimage, 1.0f, juce::Colours::white.withAlpha(0.6f)
            );
        }
        else
        {
            playerAudio.setLooping(true);
            isLooping = true;
            LoopButton.setImages(false, true, true,
                loopimage, 1.0f, juce::Colours::transparentBlack,
                loopimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                unloopimage, 1.0f, juce::Colours::white.withAlpha(0.6f)
            );
        }
    }

    if (button == &forwardButton)
    {
        double newPos = playerAudio.getPosition() + 10.0;
        double trackLength = playerAudio.getLengthInSeconds();
        if (newPos > trackLength)
            newPos = trackLength;

        playerAudio.setPosition(newPos);
    }
    else if (button == &backwardButton)
    {
        double newPos = playerAudio.getPosition() - 10.0;
        if (newPos < 0.0)
            newPos = 0.0;

        playerAudio.setPosition(newPos);
    }
}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
    {
        float v = (float)slider->getValue();
        playerAudio.setGain(v);
        volumeLabel.setText("Volume: " + juce::String((double)v, 2), juce::dontSendNotification);
    }
    else if (slider == &speedslider)
    {
        float s = (float)speedslider.getValue();
        playerAudio.setSpeed(s);
        speedLabel.setText("Speed: " + juce::String((double)s, 2) + "x", juce::dontSendNotification);
    }
    // ===== NEW: POSITION SLIDER HANDLING =====
    else if (slider == &positionSlider)
    {
        isDraggingSlider = true;
        double totalLength = playerAudio.getLengthInSeconds();
        double newPosition = slider->getValue() * totalLength;
        playerAudio.setPosition(newPosition);
        currentTimeLabel.setText(formatTime(newPosition), juce::dontSendNotification);

        // Reset flag after a delay
        juce::Timer::callAfterDelay(100, [this]() { isDraggingSlider = false; });
    }
}

// ===== NEW: TIMER CALLBACK TO UPDATE POSITION =====
void PlayerGUI::timerCallback()
{
    if (!isDraggingSlider)
    {
        updatePositionSlider();
    }
}

// ===== NEW: UPDATE POSITION SLIDER =====
void PlayerGUI::updatePositionSlider()
{
    double totalLength = playerAudio.getLengthInSeconds();
    if (totalLength > 0.0)
    {
        double currentPos = playerAudio.getPosition();
        double normalizedPos = currentPos / totalLength;
        positionSlider.setValue(normalizedPos, juce::dontSendNotification);
        currentTimeLabel.setText(formatTime(currentPos), juce::dontSendNotification);
    }
}

// ===== NEW: FORMAT TIME AS MM:SS =====
juce::String PlayerGUI::formatTime(double timeInSeconds)
{
    int minutes = static_cast<int>(timeInSeconds) / 60;
    int seconds = static_cast<int>(timeInSeconds) % 60;
    return juce::String::formatted("%02d:%02d", minutes, seconds);
}