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

    // Draw a decorative header background for metadata section
    juce::Rectangle<int> headerArea(0, 0, getWidth(), 110);
    juce::ColourGradient gradient(
        juce::Colour(0xFF2C3E50), 0, 0,
        juce::Colour(0xFF34495E), 0, 110.0f, false);
    g.setGradientFill(gradient);
    g.fillRect(headerArea);

    // Draw a subtle separator line
    g.setColour(juce::Colour(0xFF1A252F));
    g.drawLine(0, 110, (float)getWidth(), 110, 2.0f);
}

PlayerGUI::PlayerGUI()
{
    juce::PropertiesFile::Options options;
    options.applicationName = "JUCE-AudioPlayer";
    options.filenameSuffix = "settings";
    options.osxLibrarySubFolder = "Application Support";
    options.commonToAllUsers = false;

    auto storageDir = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory)
        .getChildFile(options.applicationName);

    options.folderName = storageDir.getFullPathName();

    propertiesFile = std::make_unique<juce::PropertiesFile>(options);
    
    // Playlist Box
    addAndMakeVisible(addFilesButton);
    addAndMakeVisible(playlistBox);
	addFilesButton.addListener(this);
    
    
    // Last Session
    addAndMakeVisible(loadLast);
    loadLast.addListener(this);

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
    volumeSlider.setRange(0.0, 10.0, 0.1);
    volumeSlider.setValue(1.00);
    volumeSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    // Volume label
    volumeLabel.setText("Volume: 1.00", juce::dontSendNotification);
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

    // Position slider and time labels
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

    // Metadata display labels with improved styling
    metadataTitleLabel.setText("No file loaded", juce::dontSendNotification);
    metadataTitleLabel.setFont(juce::Font(20.0f, juce::Font::bold));
    metadataTitleLabel.setJustificationType(juce::Justification::centred);
    metadataTitleLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    metadataTitleLabel.setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(metadataTitleLabel);

    metadataArtistLabel.setText("", juce::dontSendNotification);
    metadataArtistLabel.setFont(juce::Font(15.0f, juce::Font::plain));
    metadataArtistLabel.setJustificationType(juce::Justification::centred);
    metadataArtistLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFECF0F1));
    metadataArtistLabel.setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(metadataArtistLabel);

    metadataAlbumLabel.setText("", juce::dontSendNotification);
    metadataAlbumLabel.setFont(juce::Font(13.0f, juce::Font::italic));
    metadataAlbumLabel.setJustificationType(juce::Justification::centred);
    metadataAlbumLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFBDC3C7));
    metadataAlbumLabel.setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(metadataAlbumLabel);

    metadataInfoLabel.setText("", juce::dontSendNotification);
    metadataInfoLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    metadataInfoLabel.setJustificationType(juce::Justification::centred);
    metadataInfoLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF95A5A6));
    metadataInfoLabel.setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(metadataInfoLabel);

    // Start timer to update position slider
    startTimer(10);

    // ====== RESTORE LAST SESSION ======
    auto lastFilePath = propertiesFile->getValue("lastFilePath");
    lastPosition = propertiesFile->getDoubleValue("lastPosition", 0.0);
    lastVolume = propertiesFile->getDoubleValue("volume", 1.0);
    lastSpeed = propertiesFile->getDoubleValue("speed", 1.0);
    lastFullTime = propertiesFile->getValue("totalTime", "00:00");
    mutedState = propertiesFile->getBoolValue("mutedState", false);
    lastFile = juce::File(lastFilePath);
}

void PlayerGUI::resized()
{
    // Metadata section at the top (0-110)
    int metadataY = 10;
    metadataTitleLabel.setBounds(20, metadataY, getWidth() - 40, 26);
    metadataArtistLabel.setBounds(20, metadataY + 32, getWidth() - 40, 22);
    metadataAlbumLabel.setBounds(20, metadataY + 56, getWidth() - 40, 20);
    metadataInfoLabel.setBounds(20, metadataY + 78, getWidth() - 40, 18);

    // Control buttons below metadata (starting at 125)
    int y = 125;
    int buttonWidth = 70;
    int buttonHeight = 35;
    int spacing = 15;

    int numButtons = 11;
    int totalWidth = numButtons * buttonWidth + (numButtons - 1) * spacing;
    int startX = (getWidth() - totalWidth) / 2;

    loadButton.setBounds(startX + (buttonWidth + spacing) * 0, y, buttonWidth, buttonHeight);
    restartButton.setBounds(startX + (buttonWidth + spacing) * 1, y, buttonWidth, buttonHeight);
    BeginButton.setBounds(startX + (buttonWidth + spacing) * 2, y, buttonWidth, buttonHeight);
    PlayButton.setBounds(startX + (buttonWidth + spacing) * 3, y, buttonWidth, buttonHeight);
    EndButton.setBounds(startX + (buttonWidth + spacing) * 4, y, buttonWidth, buttonHeight);
    LoopButton.setBounds(startX + (buttonWidth + spacing) * 5, y, buttonWidth, buttonHeight);
    MuteButton.setBounds(startX + (buttonWidth + spacing) * 6, y, buttonWidth, buttonHeight);
    backwardButton.setBounds(startX + (buttonWidth + spacing) * 7, y, buttonWidth, buttonHeight);
    forwardButton.setBounds(startX + (buttonWidth + spacing) * 8, y, buttonWidth, buttonHeight);
	loadLast.setBounds(startX + (buttonWidth + spacing) * 9, y, buttonWidth, buttonHeight);
    addFilesButton.setBounds(startX + (buttonWidth + spacing) * 10, y, buttonWidth, buttonHeight);
    playlistBox.setRowHeight(24);
    playlistBox.setModel(this);
    playlistBox.setBounds(20, 350, getWidth() - 40, getHeight() - 370);


    // Position slider layout (below buttons)
    int positionY = 175;
    currentTimeLabel.setBounds(20, positionY, 60, 20);
    totalTimeLabel.setBounds(getWidth() - 80, positionY, 60, 20);
    positionSlider.setBounds(85, positionY, getWidth() - 170, 20);

    // Volume controls
    volumeLabel.setBounds(20, 210, 200, 20);
    volumeSlider.setBounds(20, 235, getWidth() - 40, 30);

    // Speed controls
    speedLabel.setBounds(20, 275, 200, 20);
    speedslider.setBounds(20, 300, getWidth() - 40, 30);
}

PlayerGUI::~PlayerGUI()
{
    stopTimer();
    if (propertiesFile)
    {
        propertiesFile->setValue("lastFilePath", playerAudio.getLastLoadedFile().getFullPathName());
        propertiesFile->setValue("lastPosition", playerAudio.getPosition());
        propertiesFile->setValue("volume", isMuted ? previousGain : volumeSlider.getValue());
        propertiesFile->setValue("speed", speedslider.getValue());
        propertiesFile->setValue("totalTime", totalTimeLabel.getText());
        propertiesFile->setValue("mutedState", isMuted);
        propertiesFile->saveIfNeeded();
    }
}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select an audio file...",
            juce::File{},
            "*.wav;*.mp3;*.flac;*.ogg;*.aac;*.m4a");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file.existsAsFile())
                {
                    if (playerAudio.loadFile(file))
                    {
                        // Update total time label
                        double totalLength = playerAudio.getLengthInSeconds();
                        totalTimeLabel.setText(formatTime(totalLength), juce::dontSendNotification);
                        currentTimeLabel.setText("00:00", juce::dontSendNotification);
                        positionSlider.setValue(0.0, juce::dontSendNotification);

                        // Update metadata display
                        updateMetadataDisplay();
                    }
                    else
                    {
                        // Handle load error
                        metadataTitleLabel.setText("Error loading file", juce::dontSendNotification);
                        metadataArtistLabel.setText("", juce::dontSendNotification);
                        metadataAlbumLabel.setText("", juce::dontSendNotification);
                        metadataInfoLabel.setText("", juce::dontSendNotification);
                    }
                }
                playerAudio.loadFile(file);
                // Update total time label
                double totalLength = playerAudio.getLengthInSeconds();
                totalTimeLabel.setText(formatTime(totalLength), juce::dontSendNotification);
                currentTimeLabel.setText("00:00", juce::dontSendNotification);
                positionSlider.setValue(0.0, juce::dontSendNotification);

                updateMetadataDisplay();
            }
    );
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
    if (button == &addFilesButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select Audio Files",
            juce::File{},
            "*.mp3;*.wav;*.aiff"
        );

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode
            | juce::FileBrowserComponent::canSelectFiles
            | juce::FileBrowserComponent::canSelectMultipleItems,
            [this](const juce::FileChooser& fc)
            {
                auto files = fc.getResults();
                for (auto& f : files)
                    playlistFiles.addIfNotAlreadyThere(f);

                playlistBox.updateContent();
                playlistBox.repaint();
            }
        );
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

    if (button == &loadLast)
    {
        auto lastPath = propertiesFile->getValue("lastFilePath");
        if (lastPath.isEmpty())
            return;

        lastFile = juce::File(lastPath);

        if (lastFile.existsAsFile())
        {
            playerAudio.loadFile(lastFile);
        

            juce::Timer::callAfterDelay(300, [this]()
                {
                    playerAudio.setSpeed(lastSpeed);
                    playerAudio.setPosition(lastPosition);

                    // ✅ FIXED: Set isMuted state and previousGain properly
                    isMuted = mutedState;
                    
                    if (mutedState)
                    {
                        // Store the actual volume as previousGain
                        previousGain = (float)lastVolume;
                        // Set audio to muted
                        playerAudio.setGain(0.0f);
                        // Show slider at 0
                        volumeSlider.setValue(0.0, juce::dontSendNotification);
                        volumeLabel.setText("Volume: 0.00", juce::dontSendNotification);
                        // Update mute button icon to show muted state
                        MuteButton.setImages(false, true, true,
                            mutedImage, 1.0f, juce::Colours::transparentBlack,
                            mutedImage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                            unmutedImage, 1.0f, juce::Colours::white.withAlpha(0.6f)
                        );
                    }
                    else
                    {
                        // Not muted - set volume normally
                        playerAudio.setGain((float)lastVolume);
                        volumeSlider.setValue(lastVolume, juce::dontSendNotification);
                        volumeLabel.setText("Volume: " + juce::String(lastVolume, 2), juce::dontSendNotification);
                        // ✅ FIXED: Initialize previousGain even when not muted
                        previousGain = (float)lastVolume;
                        // Update mute button icon to show unmuted state
                        MuteButton.setImages(false, true, true,
                            unmutedImage, 1.0f, juce::Colours::transparentBlack,
                            unmutedImage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                            mutedImage, 1.0f, juce::Colours::white.withAlpha(0.6f)
                        );
                    }

                    speedslider.setValue(lastSpeed, juce::dontSendNotification);
                    speedLabel.setText("Speed: " + juce::String(lastSpeed, 2) + "x", juce::dontSendNotification);
                    totalTimeLabel.setText(lastFullTime, juce::dontSendNotification);
                    currentTimeLabel.setText(formatTime(lastPosition), juce::dontSendNotification);
                    if (auto totalLength = playerAudio.getLengthInSeconds(); totalLength > 0.0)
                        positionSlider.setValue(lastPosition / totalLength, juce::dontSendNotification);

                    updateMetadataDisplay();
                });
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
            // Unmuting - restore previous gain
            playerAudio.setGain(previousGain);
            volumeSlider.setValue(previousGain, juce::dontSendNotification);
            volumeLabel.setText("Volume: " + juce::String((double)previousGain, 2), juce::dontSendNotification);
            isMuted = false;
            MuteButton.setImages(false, true, true,
                unmutedImage, 1.0f, juce::Colours::transparentBlack,
                unmutedImage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                mutedImage, 1.0f, juce::Colours::white.withAlpha(0.6f)
            );
        }
        else
        {
            // Muting - save current gain
            previousGain = (float)volumeSlider.getValue();
            playerAudio.setGain(0.0f);
            volumeSlider.setValue(0.0, juce::dontSendNotification);
            volumeLabel.setText("Volume: 0.00", juce::dontSendNotification);
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

        // ✅ FIXED: Update previousGain when user manually changes volume (and not muted)
        if (!isMuted)
        {
            previousGain = v;
        }
    }
    else if (slider == &speedslider)
    {
        float s = (float)speedslider.getValue();
        playerAudio.setSpeed(s);
        speedLabel.setText("Speed: " + juce::String((double)s, 2) + "x", juce::dontSendNotification);
    }
    else if (slider == &positionSlider)
    {
        isDraggingSlider = true;
        double totalLength = playerAudio.getLengthInSeconds();
        double newPosition = slider->getValue() * totalLength;
        playerAudio.setPosition(newPosition);
        currentTimeLabel.setText(formatTime(newPosition), juce::dontSendNotification);

        juce::Timer::callAfterDelay(100, [this]() { isDraggingSlider = false; });
    }
}

void PlayerGUI::timerCallback()
{
    if (!isDraggingSlider)
    {
        updatePositionSlider();
    }
    static int counter = 0;
    if (++counter >= 500)
    {
        if (propertiesFile)
        {
            propertiesFile->setValue("lastFilePath", playerAudio.getLastLoadedFile().getFullPathName());
            propertiesFile->setValue("lastPosition", playerAudio.getPosition());
            // ✅ FIXED: Save the actual volume (previousGain) when muted
            propertiesFile->setValue("volume", isMuted ? previousGain : volumeSlider.getValue());
            propertiesFile->setValue("speed", speedslider.getValue());
            propertiesFile->setValue("totalTime", totalTimeLabel.getText());
            propertiesFile->setValue("mutedState", isMuted);
            propertiesFile->saveIfNeeded();
        }
        counter = 0;
    }
}

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

juce::String PlayerGUI::formatTime(double timeInSeconds)
{
    int minutes = static_cast<int>(timeInSeconds) / 60;
    int seconds = static_cast<int>(timeInSeconds) % 60;
    return juce::String::formatted("%02d:%02d", minutes, seconds);
}

void PlayerGUI::updateMetadataDisplay()
{
    const AudioMetadata& metadata = playerAudio.getMetadata();

    // Display title (or filename if no metadata)
    if (metadata.hasMetadata && !metadata.title.isEmpty())
        metadataTitleLabel.setText(metadata.title, juce::dontSendNotification);
    else
        metadataTitleLabel.setText(metadata.filename, juce::dontSendNotification);

    // Display artist
    if (metadata.hasMetadata && !metadata.artist.isEmpty())
        metadataArtistLabel.setText(metadata.artist, juce::dontSendNotification);
    else
        metadataArtistLabel.setText("Unknown Artist", juce::dontSendNotification);

    // Display album
    if (metadata.hasMetadata && !metadata.album.isEmpty())
        metadataAlbumLabel.setText("Album: " + metadata.album, juce::dontSendNotification);
    else
        metadataAlbumLabel.setText("", juce::dontSendNotification);

    // Display additional info (bitrate, sample rate, channels, genre)
    juce::String info;
    if (metadata.bitrate > 0)
        info << metadata.bitrate << " kbps";
    if (metadata.sampleRate > 0)
    {
        if (!info.isEmpty()) info << " • ";
        info << (metadata.sampleRate / 1000.0) << " kHz";
    }
    if (metadata.channels > 0)
    {
        if (!info.isEmpty()) info << " • ";
        info << metadata.channels << (metadata.channels == 1 ? " channel" : " channels");
    }
    if (metadata.hasMetadata && !metadata.genre.isEmpty())
    {
        if (!info.isEmpty()) info << " • ";
        info << metadata.genre;
    }

    metadataInfoLabel.setText(info, juce::dontSendNotification);
}



int PlayerGUI::getNumRows()
{
    return playlistFiles.size();
}

void PlayerGUI::paintListBoxItem(int rowNumber, juce::Graphics& g,
    int width, int height, bool rowIsSelected)
{
    if (rowNumber < playlistFiles.size())
    {
        auto filename = playlistFiles[rowNumber].getFileName();

        if (rowIsSelected)
            g.fillAll(juce::Colours::lightblue);
        else
            g.fillAll(juce::Colours::transparentBlack);

        g.setColour(juce::Colours::white);
        g.drawText(filename, 10, 0, width - 10, height, juce::Justification::centredLeft);
    }
}

void PlayerGUI::selectedRowsChanged(int lastRowSelected)
{
    if (lastRowSelected >= 0 && lastRowSelected < playlistFiles.size())
    {
        auto file = playlistFiles[lastRowSelected];
        playerAudio.loadFile(file);
        playerAudio.start();
    }
}