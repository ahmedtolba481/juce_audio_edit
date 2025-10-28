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
        loadimage, 1.0f, juce::Colours::transparentBlack,     // normal
        loadimage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
        loadimage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
    );
    addAndMakeVisible(loadButton);
    loadButton.addListener(this);
	// play button
    playimage= juce::ImageFileFormat::loadFrom(BinaryData::playbuttton_png, BinaryData::playbuttton_pngSize);
   pauseimage = juce::ImageFileFormat::loadFrom(BinaryData::pause_png, BinaryData::pause_pngSize);

   PlayButton.setImages(false, true, true,
       pauseimage, 1.0f, juce::Colours::transparentBlack,     // normal
       pauseimage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
       playimage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
   );

    addAndMakeVisible(PlayButton);
    PlayButton.addListener(this);
   
    //restart button 
     restartimage= juce::ImageFileFormat::loadFrom(BinaryData::rotate_png, BinaryData::rotate_pngSize);

    restartButton.setImages(false, true, true,
        restartimage, 1.0f, juce::Colours::transparentBlack,     // normal
        restartimage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
        restartimage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
    );

    addAndMakeVisible(restartButton);
    restartButton.addListener(this);

	// Begin button
    beginimage = juce::ImageFileFormat::loadFrom(BinaryData::play__Copy_png, BinaryData::play__Copy_pngSize);

    BeginButton.setImages(false, true, true,
        beginimage, 1.0f, juce::Colours::transparentBlack,     // normal
        beginimage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
        beginimage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
    );

    addAndMakeVisible(BeginButton);
    BeginButton.addListener(this);

	// End button
    endimage = juce::ImageFileFormat::loadFrom(BinaryData::play_png, BinaryData::play_pngSize);

    EndButton.setImages(false, true, true,
        endimage, 1.0f, juce::Colours::transparentBlack,     // normal
        endimage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
        endimage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
    );

    addAndMakeVisible(EndButton);
    EndButton.addListener(this);

	// Mute button
    mutedImage = juce::ImageFileFormat::loadFrom(BinaryData::volumemute_png, BinaryData::volumemute_pngSize);
    unmutedImage = juce::ImageFileFormat::loadFrom(BinaryData::speakerfilledaudiotool_png, BinaryData::speakerfilledaudiotool_pngSize);

    MuteButton.setImages(false, true, true,
        unmutedImage, 1.0f, juce::Colours::transparentBlack,     // normal
        unmutedImage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
        mutedImage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
    );

    addAndMakeVisible(MuteButton);
    MuteButton.addListener(this);

    //loop button
    loopimage = juce::ImageFileFormat::loadFrom(BinaryData::loop_png, BinaryData::loop_pngSize);
    unloopimage = juce::ImageFileFormat::loadFrom(BinaryData::stop_png, BinaryData::stop_pngSize);

    LoopButton.setImages(false, true, true,
        unloopimage, 1.0f, juce::Colours::transparentBlack,     // normal
        unloopimage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
        loopimage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
    );

    addAndMakeVisible(LoopButton);
    LoopButton.addListener(this);

	// forward button
	forwardimage = juce::ImageFileFormat::loadFrom(BinaryData::forward_png, BinaryData::forward_pngSize);
    forwardButton.setImages(false, true, true,
        forwardimage, 1.0f, juce::Colours::transparentBlack,     // normal
        forwardimage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
        forwardimage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
	);
	addAndMakeVisible(forwardButton);
	forwardButton.addListener(this);
	// backward button
	backwardimage = juce::ImageFileFormat::loadFrom(BinaryData::backward_png, BinaryData::backward_pngSize);
    backwardButton.setImages(false, true, true,
        backwardimage, 1.0f, juce::Colours::transparentBlack,     // normal
        backwardimage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
        backwardimage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
	);
	addAndMakeVisible(backwardButton);
	backwardButton.addListener(this);
    // Volume slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.4);
    volumeSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);


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

    volumeSlider.setBounds(20, 100, getWidth() - 40, 30);
}

PlayerGUI::~PlayerGUI()
{
}
void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        juce::FileChooser chooser("Select audio files...",
            juce::File{},
            "*.wav;*.mp3");

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
                }
            });
    }

    if (button == &restartButton)
    {
        playerAudio.setPosition(0.0);
        PlayButton.setImages(false, true, true,
            pauseimage, 1.0f, juce::Colours::transparentBlack,     // normal
            pauseimage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
            playimage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
        );
        playerAudio.start();
    }

    if (button == &BeginButton)
    {
        playerAudio.setPosition(0.0);
        playerAudio.stop();

        PlayButton.setImages(false, true, true,
            playimage, 1.0f, juce::Colours::transparentBlack,     // normal
            playimage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
            pauseimage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
        );
    }

    if (button == &EndButton)
    {
        if (isLooping)
        {
            playerAudio.setPosition(0.0);
            playerAudio.start();
            PlayButton.setImages(false, true, true,
                pauseimage, 1.0f, juce::Colours::transparentBlack,     // normal
                pauseimage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
                playimage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
            );
        }
        else
        {
            playerAudio.setPosition(playerAudio.getLength() - 0.05);
            playerAudio.stop();

            PlayButton.setImages(false, true, true,
                playimage, 1.0f, juce::Colours::transparentBlack,     // normal
                playimage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
                pauseimage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
            );
        }
    }

    if (button == &PlayButton)
    {
        if (playerAudio.isPlaying())
        {
            playerAudio.stop();

            PlayButton.setImages(false, true, true,
                playimage, 1.0f, juce::Colours::transparentBlack,     // normal
                playimage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
                pauseimage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
            );
        }
        else
        {
            playerAudio.start();

            PlayButton.setImages(false, true, true,
                pauseimage, 1.0f, juce::Colours::transparentBlack,     // normal
                pauseimage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
                playimage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
            );
        }
    }

    if (button == &MuteButton) {
        if (isMuted) {
            playerAudio.setGain(previousGain);
            volumeSlider.setValue(previousGain);
            isMuted = false;
            MuteButton.setImages(false, true, true,
                unmutedImage, 1.0f, juce::Colours::transparentBlack,     // normal
                unmutedImage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
                mutedImage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
            );
        }
        else {
            previousGain = (float)volumeSlider.getValue();
            playerAudio.setGain(0.0f);
            volumeSlider.setValue(0.0);
            isMuted = true;
            MuteButton.setImages(false, true, true,
                mutedImage, 1.0f, juce::Colours::transparentBlack,     // normal
                mutedImage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
                unmutedImage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
            );

        }
    }

    if (button == &LoopButton) {
        if (isLooping) {
            playerAudio.setLooping(false);
            isLooping = false;
            LoopButton.setImages(false, true, true,
                unloopimage, 1.0f, juce::Colours::transparentBlack,     // normal
                unloopimage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
                loopimage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
            );
        }
        else {
            playerAudio.setLooping(true);
            isLooping = true;
            LoopButton.setImages(false, true, true,
                loopimage, 1.0f, juce::Colours::transparentBlack,     // normal
                loopimage, 0.5f, juce::Colours::white.withAlpha(0.3f), // hover
                unloopimage, 1.0f, juce::Colours::white.withAlpha(0.6f) // pressed
            );
        }
    }
    if (button == &forwardButton) {
        playerAudio.setPosition(playerAudio.getPosition() + 10.0);
    }
    if(button == &backwardButton) {
        playerAudio.setPosition(playerAudio.getPosition() - 10.0);
	}
}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        playerAudio.setGain((float)slider->getValue());
}
