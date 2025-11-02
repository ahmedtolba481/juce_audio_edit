#include "PlayerGUI.h"

// PlaylistRowComponent implementation
PlaylistRowComponent::PlaylistRowComponent(PlayerGUI *parent) : owner(parent)
{
    filenameLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    filenameLabel.setFont(juce::FontOptions(13.0f, juce::Font::plain));
    filenameLabel.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(filenameLabel);

    durationLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    durationLabel.setFont(juce::FontOptions(13.0f, juce::Font::plain));
    durationLabel.setJustificationType(juce::Justification::centred);
    durationLabel.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(durationLabel);

    deleteButton.setButtonText("Delete");
    deleteButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE74C3C));
    deleteButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFFC0392B));
    deleteButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    deleteButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    deleteButton.setColour(juce::ComboBox::outlineColourId, juce::Colour(0xFFFFFFFF).withAlpha(0.3f));
    deleteButton.setConnectedEdges(juce::TextButton::ConnectedOnLeft | juce::TextButton::ConnectedOnRight);
    deleteButton.getProperties().set("fontSize", 11.0f);
    deleteButton.addListener(this);
    addAndMakeVisible(deleteButton);
}

void PlaylistRowComponent::updateRow(int rowIndex, const juce::String &filename, const juce::String &duration, bool isSelected)
{
    currentRow = rowIndex;
    filenameLabel.setText(filename, juce::dontSendNotification);
    durationLabel.setText(duration, juce::dontSendNotification);

    if (isSelected)
        setBackgroundColour(juce::Colour(0xFF3498DB));
    else
        setBackgroundColour(rowIndex % 2 == 0 ? juce::Colour(0xFF2C3E50) : juce::Colour(0xFF34495E));
}

void PlaylistRowComponent::resized()
{
    auto bounds = getLocalBounds();
    filenameLabel.setBounds(10, 0, bounds.getWidth() - 150, bounds.getHeight());
    durationLabel.setBounds(bounds.getWidth() - 140, 0, 70, bounds.getHeight());
    deleteButton.setBounds(bounds.getWidth() - 65, 2, 60, bounds.getHeight() - 4);
}

void PlaylistRowComponent::paint(juce::Graphics &g)
{
    g.fillAll(backgroundColour);
}

void PlaylistRowComponent::buttonClicked(juce::Button *button)
{
    if (button == &deleteButton && owner != nullptr)
    {
        owner->deleteTrack(currentRow);
    }
}

void PlaylistRowComponent::setBackgroundColour(juce::Colour colour)
{
    backgroundColour = colour;
    repaint();
}

void PlaylistRowComponent::mouseDown(const juce::MouseEvent &event)
{
    auto localPos = event.getEventRelativeTo(this).position.toInt();
    auto bounds = getLocalBounds();
    juce::Rectangle<int> deleteButtonBounds(bounds.getWidth() - 65, 2, 60, bounds.getHeight() - 4);

    if (deleteButtonBounds.contains(localPos))
    {
        return;
    }

    Component::mouseDown(event);
}

void PlaylistRowComponent::mouseDoubleClick(const juce::MouseEvent &event)
{
    auto localPos = event.getEventRelativeTo(this).position.toInt();
    auto bounds = getLocalBounds();
    juce::Rectangle<int> deleteButtonBounds(bounds.getWidth() - 65, 2, 60, bounds.getHeight() - 4);

    if (deleteButtonBounds.contains(localPos))
    {
        return;
    }

    if (owner != nullptr && currentRow >= 0 && currentRow < owner->getPlaylistSize())
    {
        owner->selectPlaylistRow(currentRow);
    }
}

void PlaylistRowComponent::mouseDrag(const juce::MouseEvent &event)
{
    auto localPos = event.getEventRelativeTo(this).position.toInt();
    auto bounds = getLocalBounds();
    juce::Rectangle<int> deleteButtonBounds(bounds.getWidth() - 65, 2, 60, bounds.getHeight() - 4);

    if (deleteButtonBounds.contains(localPos))
    {
        return;
    }

    if (currentRow >= 0 && event.mouseWasDraggedSinceMouseDown())
    {
        if (auto *dragContainer = juce::DragAndDropContainer::findParentDragContainerFor(this))
        {
            dragContainer->startDragging(juce::var(currentRow), this);
        }
    }
}

// MarkerRowComponent implementation
MarkerRowComponent::MarkerRowComponent(PlayerGUI* parent) : owner(parent)
{
    markerLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    markerLabel.setFont(juce::FontOptions(13.0f, juce::Font::bold));
    markerLabel.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(markerLabel);
    
    timeLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF3498DB));
    timeLabel.setFont(juce::FontOptions(12.0f, juce::Font::plain));
    timeLabel.setJustificationType(juce::Justification::centredRight);
    timeLabel.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(timeLabel);
    
    deleteButton.setButtonText("X");
    deleteButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE74C3C));
    deleteButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFFC0392B));
    deleteButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    deleteButton.addListener(this);
    addAndMakeVisible(deleteButton);
}

void MarkerRowComponent::updateRow(int rowIndex, const juce::String& label, const juce::String& time)
{
    currentRow = rowIndex;
    markerLabel.setText(label, juce::dontSendNotification);
    timeLabel.setText(time, juce::dontSendNotification);
    backgroundColour = rowIndex % 2 == 0 ? juce::Colour(0xFF34495E) : juce::Colour(0xFF2C3E50);
}

void MarkerRowComponent::resized()
{
    auto bounds = getLocalBounds();
    deleteButton.setBounds(bounds.getWidth() - 30, 2, 25, bounds.getHeight() - 4);
    timeLabel.setBounds(bounds.getWidth() - 100, 0, 65, bounds.getHeight());
    markerLabel.setBounds(10, 0, bounds.getWidth() - 110, bounds.getHeight());
}

void MarkerRowComponent::paint(juce::Graphics& g)
{
    g.fillAll(backgroundColour);
    
    if (isMouseOver())
    {
        g.setColour(juce::Colours::white.withAlpha(0.1f));
        g.fillAll();
    }
}

void MarkerRowComponent::buttonClicked(juce::Button* button)
{
    if (button == &deleteButton && owner != nullptr)
    {
        owner->deleteMarker(currentRow);
    }
}

void MarkerRowComponent::mouseDown(const juce::MouseEvent& event)
{
    auto localPos = event.getEventRelativeTo(this).position.toInt();
    auto bounds = getLocalBounds();
    juce::Rectangle<int> deleteButtonBounds(bounds.getWidth() - 30, 2, 25, bounds.getHeight() - 4);
    
    if (deleteButtonBounds.contains(localPos))
    {
        return;
    }
    
    if (owner != nullptr && currentRow >= 0)
    {
        owner->jumpToMarker(currentRow);
    }
}

void PlayerGUI::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playerAudio.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerGUI::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    playerAudio.getNextAudioBlock(bufferToFill);
}

void PlayerGUI::releaseResources()
{
    playerAudio.releaseResources();
}

void PlayerGUI::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::lightgrey);

    juce::Rectangle<int> headerArea(0, 0, getWidth(), 110);
    juce::ColourGradient gradient(
        juce::Colour(0xFF2C3E50), 0, 0,
        juce::Colour(0xFF34495E), 0, 110.0f, false);
    g.setGradientFill(gradient);
    g.fillRect(headerArea);

    g.setColour(juce::Colour(0xFF1A252F));
    g.drawLine(0, 110, (float)getWidth(), 110, 2.0f);

    drawABLoopMarkers(g);
    drawTrackMarkers(g);
}

void PlayerGUI::drawABLoopMarkers(juce::Graphics &g)
{
    if (playerAudio.getLengthInSeconds() <= 0.0)
        return;

    auto sliderBounds = positionSlider.getBounds();
    double totalLength = playerAudio.getLengthInSeconds();

    const int thumbWidth = 20;
    const int sliderPadding = thumbWidth / 2;

    int trackX = sliderBounds.getX() + sliderPadding;
    int trackWidth = sliderBounds.getWidth() - thumbWidth;
    int trackY = sliderBounds.getY();
    int trackHeight = sliderBounds.getHeight();

    if (playerAudio.hasValidABLoop())
    {
        double pointA = playerAudio.getPointA();
        double pointB = playerAudio.getPointB();

        double normA = pointA / totalLength;
        double normB = pointB / totalLength;

        int xA = trackX + static_cast<int>(normA * trackWidth);
        int xB = trackX + static_cast<int>(normB * trackWidth);

        juce::Rectangle<int> loopRegion(xA, trackY - 10,
                                        xB - xA, trackHeight + 20);
        g.setColour(juce::Colour(0x3000FF00));
        g.fillRect(loopRegion);

        g.setColour(juce::Colour(0x8000FF00));
        g.drawRect(loopRegion, 2);
    }

    if (playerAudio.isPositionSetA())
    {
        double pointA = playerAudio.getPointA();
        double normA = pointA / totalLength;
        int xA = trackX + static_cast<int>(normA * trackWidth);

        juce::Path markerA;
        markerA.addTriangle(
            static_cast<float>(xA), static_cast<float>(trackY - 15),
            static_cast<float>(xA - 8), static_cast<float>(trackY - 5),
            static_cast<float>(xA + 8), static_cast<float>(trackY - 5));
        g.setColour(juce::Colour(0xFF3498DB));
        g.fillPath(markerA);

        g.setColour(juce::Colour(0xFF3498DB));
        g.drawLine(static_cast<float>(xA), static_cast<float>(trackY - 5),
                   static_cast<float>(xA), static_cast<float>(trackY + trackHeight + 5), 2.0f);

        g.setColour(juce::Colours::white);
        g.setFont(juce::FontOptions(12.0f, juce::Font::bold));
        g.drawText("A", xA - 10, trackY - 25, 20, 15, juce::Justification::centred);
    }

    if (playerAudio.isPositionSetB())
    {
        double pointB = playerAudio.getPointB();
        double normB = pointB / totalLength;
        int xB = trackX + static_cast<int>(normB * trackWidth);

        juce::Path markerB;
        markerB.addTriangle(
            static_cast<float>(xB), static_cast<float>(trackY - 15),
            static_cast<float>(xB - 8), static_cast<float>(trackY - 5),
            static_cast<float>(xB + 8), static_cast<float>(trackY - 5));
        g.setColour(juce::Colour(0xFFE74C3C));
        g.fillPath(markerB);

        g.setColour(juce::Colour(0xFFE74C3C));
        g.drawLine(static_cast<float>(xB), static_cast<float>(trackY - 5),
                   static_cast<float>(xB), static_cast<float>(trackY + trackHeight + 5), 2.0f);

        g.setColour(juce::Colours::white);
        g.setFont(juce::FontOptions(12.0f, juce::Font::bold));
        g.drawText("B", xB - 10, trackY - 25, 20, 15, juce::Justification::centred);
    }
}

void PlayerGUI::drawTrackMarkers(juce::Graphics& g)
{
    if (playerAudio.getLengthInSeconds() <= 0.0)
        return;

    auto sliderBounds = positionSlider.getBounds();
    double totalLength = playerAudio.getLengthInSeconds();
    juce::String currentFileId = getCurrentFileId();

    const int thumbWidth = 20;
    const int sliderPadding = thumbWidth / 2;

    int trackX = sliderBounds.getX() + sliderPadding;
    int trackWidth = sliderBounds.getWidth() - thumbWidth;
    int trackY = sliderBounds.getY();
    int trackHeight = sliderBounds.getHeight();

    for (const auto& marker : markers)
    {
        if (marker.fileId != currentFileId)
            continue;

        double normPos = marker.timestamp / totalLength;
        int xPos = trackX + static_cast<int>(normPos * trackWidth);

        juce::Path markerPath;
        markerPath.addTriangle(
            static_cast<float>(xPos), static_cast<float>(trackY + trackHeight + 5),
            static_cast<float>(xPos - 6), static_cast<float>(trackY + trackHeight + 15),
            static_cast<float>(xPos + 6), static_cast<float>(trackY + trackHeight + 15));

        g.setColour(juce::Colour(0xFF9B59B6));
        g.fillPath(markerPath);

        g.setColour(juce::Colour(0xFF9B59B6).withAlpha(0.6f));
        g.drawLine(static_cast<float>(xPos), static_cast<float>(trackY),
                   static_cast<float>(xPos), static_cast<float>(trackY + trackHeight), 2.0f);
    }
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

    playlistBox.setRowHeight(28);
    playlistBox.setColour(juce::ListBox::backgroundColourId, juce::Colour(0xFF2C3E50));
    playlistBox.setColour(juce::ListBox::outlineColourId, juce::Colour(0xFF34495E));
    playlistBox.setModel(this);
    addAndMakeVisible(playlistBox);

    addFilesButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF2ECC71));
    addFilesButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    addAndMakeVisible(addFilesButton);
    addFilesButton.addListener(this);

    loadLast.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF9B59B6));
    loadLast.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    addAndMakeVisible(loadLast);
    loadLast.addListener(this);

    loadimage = juce::ImageFileFormat::loadFrom(BinaryData::upload_png, BinaryData::upload_pngSize);
    loadButton.setImages(false, true, true,
                         loadimage, 1.0f, juce::Colours::transparentBlack,
                         loadimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                         loadimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
    addAndMakeVisible(loadButton);
    loadButton.addListener(this);

    playimage = juce::ImageFileFormat::loadFrom(BinaryData::playbuttton_png, BinaryData::playbuttton_pngSize);
    pauseimage = juce::ImageFileFormat::loadFrom(BinaryData::pause_png, BinaryData::pause_pngSize);
    PlayButton.setImages(false, true, true,
                         pauseimage, 1.0f, juce::Colours::transparentBlack,
                         pauseimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                         playimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
    addAndMakeVisible(PlayButton);
    PlayButton.addListener(this);

    restartimage = juce::ImageFileFormat::loadFrom(BinaryData::rotate_png, BinaryData::rotate_pngSize);
    restartButton.setImages(false, true, true,
                            restartimage, 1.0f, juce::Colours::transparentBlack,
                            restartimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                            restartimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
    addAndMakeVisible(restartButton);
    restartButton.addListener(this);

    beginimage = juce::ImageFileFormat::loadFrom(BinaryData::play__Copy_png, BinaryData::play__Copy_pngSize);
    BeginButton.setImages(false, true, true,
                          beginimage, 1.0f, juce::Colours::transparentBlack,
                          beginimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                          beginimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
    addAndMakeVisible(BeginButton);
    BeginButton.addListener(this);

    endimage = juce::ImageFileFormat::loadFrom(BinaryData::play_png, BinaryData::play_pngSize);
    EndButton.setImages(false, true, true,
                        endimage, 1.0f, juce::Colours::transparentBlack,
                        endimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                        endimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
    addAndMakeVisible(EndButton);
    EndButton.addListener(this);

    mutedImage = juce::ImageFileFormat::loadFrom(BinaryData::volumemute_png, BinaryData::volumemute_pngSize);
    unmutedImage = juce::ImageFileFormat::loadFrom(BinaryData::speakerfilledaudiotool_png, BinaryData::speakerfilledaudiotool_pngSize);
    MuteButton.setImages(false, true, true,
                         unmutedImage, 1.0f, juce::Colours::transparentBlack,
                         unmutedImage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                         mutedImage, 1.0f, juce::Colours::white.withAlpha(0.6f));
    addAndMakeVisible(MuteButton);
    MuteButton.addListener(this);

    loopimage = juce::ImageFileFormat::loadFrom(BinaryData::loop_png, BinaryData::loop_pngSize);
    unloopimage = juce::ImageFileFormat::loadFrom(BinaryData::stop_png, BinaryData::stop_pngSize);
    LoopButton.setImages(false, true, true,
                         unloopimage, 1.0f, juce::Colours::transparentBlack,
                         unloopimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                         loopimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
    addAndMakeVisible(LoopButton);
    LoopButton.addListener(this);

    forwardimage = juce::ImageFileFormat::loadFrom(BinaryData::forward_png, BinaryData::forward_pngSize);
    forwardButton.setImages(false, true, true,
                            forwardimage, 1.0f, juce::Colours::transparentBlack,
                            forwardimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                            forwardimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
    addAndMakeVisible(forwardButton);
    forwardButton.addListener(this);

    backwardimage = juce::ImageFileFormat::loadFrom(BinaryData::backward_png, BinaryData::backward_pngSize);
    backwardButton.setImages(false, true, true,
                             backwardimage, 1.0f, juce::Colours::transparentBlack,
                             backwardimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                             backwardimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
    addAndMakeVisible(backwardButton);
    backwardButton.addListener(this);

    volumeSlider.setRange(0.0, 10.0, 0.1);
    volumeSlider.setValue(1.00);
    volumeSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 60, 20);
    volumeSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    volumeSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(0xFF34495E));
    volumeSlider.setColour(juce::Slider::trackColourId, juce::Colour(0xFF3498DB));
    volumeSlider.setColour(juce::Slider::thumbColourId, juce::Colour(0xFF2980B9));
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    volumeLabel.setText("Volume: 1.00", juce::dontSendNotification);
    volumeLabel.setFont(juce::FontOptions(15.0f, juce::Font::bold));
    volumeLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF2C3E50));
    volumeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(volumeLabel);

    speedslider.setRange(0.25, 2.0, 0.25);
    speedslider.setValue(1.0);
    speedslider.setSliderStyle(juce::Slider::LinearHorizontal);
    speedslider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 60, 20);
    speedslider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
    speedslider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(0xFF34495E));
    speedslider.setColour(juce::Slider::trackColourId, juce::Colour(0xFFE67E22));
    speedslider.setColour(juce::Slider::thumbColourId, juce::Colour(0xFFD35400));
    speedslider.addListener(this);
    addAndMakeVisible(speedslider);

    speedLabel.setText("Speed: 1.00x", juce::dontSendNotification);
    speedLabel.setFont(juce::FontOptions(15.0f, juce::Font::bold));
    speedLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF2C3E50));
    speedLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(speedLabel);

    positionSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    positionSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    positionSlider.setRange(0.0, 1.0, 0.001);
    positionSlider.setColour(juce::Slider::trackColourId, juce::Colour(0xFF34495E));
    positionSlider.setColour(juce::Slider::backgroundColourId, juce::Colour(0xFFBDC3C7));
    positionSlider.setColour(juce::Slider::thumbColourId, juce::Colour(0xFF2980B9));
    positionSlider.addListener(this);
    addAndMakeVisible(positionSlider);

    currentTimeLabel.setText("00:00", juce::dontSendNotification);
    currentTimeLabel.setJustificationType(juce::Justification::centredLeft);
    currentTimeLabel.setFont(juce::FontOptions(13.0f, juce::Font::bold));
    currentTimeLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF2C3E50));
    addAndMakeVisible(currentTimeLabel);

    totalTimeLabel.setText("00:00", juce::dontSendNotification);
    totalTimeLabel.setJustificationType(juce::Justification::centredRight);
    totalTimeLabel.setFont(juce::FontOptions(13.0f, juce::Font::bold));
    totalTimeLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF2C3E50));
    addAndMakeVisible(totalTimeLabel);

    metadataTitleLabel.setText("No file loaded", juce::dontSendNotification);
    metadataTitleLabel.setFont(juce::FontOptions(22.0f, juce::Font::bold));
    metadataTitleLabel.setJustificationType(juce::Justification::centred);
    metadataTitleLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    metadataTitleLabel.setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(metadataTitleLabel);

    metadataArtistLabel.setText("", juce::dontSendNotification);
    metadataArtistLabel.setFont(juce::FontOptions(16.0f, juce::Font::plain));
    metadataArtistLabel.setJustificationType(juce::Justification::centred);
    metadataArtistLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFECF0F1));
    metadataArtistLabel.setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(metadataArtistLabel);

    metadataAlbumLabel.setText("", juce::dontSendNotification);
    metadataAlbumLabel.setFont(juce::FontOptions(14.0f, juce::Font::italic));
    metadataAlbumLabel.setJustificationType(juce::Justification::centred);
    metadataAlbumLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFBDC3C7));
    metadataAlbumLabel.setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(metadataAlbumLabel);

    metadataInfoLabel.setText("", juce::dontSendNotification);
    metadataInfoLabel.setFont(juce::FontOptions(12.0f, juce::Font::plain));
    metadataInfoLabel.setJustificationType(juce::Justification::centred);
    metadataInfoLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF95A5A6));
    metadataInfoLabel.setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(metadataInfoLabel);

    startTimer(50);

    auto lastFilePath = propertiesFile->getValue("lastFilePath");
    lastPosition = propertiesFile->getDoubleValue("lastPosition", 0.0);
    lastVolume = propertiesFile->getDoubleValue("volume", 1.0);
    lastSpeed = propertiesFile->getDoubleValue("speed", 1.0);
    lastFullTime = propertiesFile->getValue("totalTime", "00:00");
    mutedState = propertiesFile->getBoolValue("mutedState", false);
    lastFile = juce::File(lastFilePath);

    setPointAButton.addListener(this);
    setPointAButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF3498DB));
    setPointAButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    setPointAButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFF2980B9));
    addAndMakeVisible(setPointAButton);

    setPointBButton.addListener(this);
    setPointBButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE74C3C));
    setPointBButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    setPointBButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFFC0392B));
    addAndMakeVisible(setPointBButton);

    clearABButton.addListener(this);
    clearABButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF95A5A6));
    clearABButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    addAndMakeVisible(clearABButton);

    enableABLoopButton.addListener(this);
    enableABLoopButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF2ECC71));
    enableABLoopButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    enableABLoopButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFF27AE60));
    addAndMakeVisible(enableABLoopButton);

    abLoopInfoLabel.setText("A-B Loop: Not set", juce::dontSendNotification);
    abLoopInfoLabel.setJustificationType(juce::Justification::centred);
    abLoopInfoLabel.setFont(juce::FontOptions(13.0f, juce::Font::bold));
    abLoopInfoLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    abLoopInfoLabel.setColour(juce::Label::backgroundColourId, juce::Colour(0xFF34495E));
    abLoopInfoLabel.setColour(juce::Label::outlineColourId, juce::Colour(0xFF2C3E50));
    addAndMakeVisible(abLoopInfoLabel);

    clearPlaylistButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE74C3C));
    clearPlaylistButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    addAndMakeVisible(clearPlaylistButton);
    clearPlaylistButton.addListener(this);

    unLoadTrack.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFe67e22));
    unLoadTrack.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    addAndMakeVisible(unLoadTrack);
    unLoadTrack.addListener(this);

    addMarkerButton.addListener(this);
    addMarkerButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF9B59B6));
    addMarkerButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    addAndMakeVisible(addMarkerButton);

    clearMarkersButton.addListener(this);
    clearMarkersButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF95A5A6));
    clearMarkersButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    addAndMakeVisible(clearMarkersButton);

    markersLabel.setText("Track Markers", juce::dontSendNotification);
    markersLabel.setFont(juce::FontOptions(14.0f, juce::Font::bold));
    markersLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF2C3E50));
    markersLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(markersLabel);

    markersListBox.setRowHeight(26);
    markersListBox.setColour(juce::ListBox::backgroundColourId, juce::Colour(0xFF34495E));
    markersListBox.setColour(juce::ListBox::outlineColourId, juce::Colour(0xFF2C3E50));
    markersListBox.setModel(this);
    addAndMakeVisible(markersListBox);

    loadMarkers();
}

void PlayerGUI::resized()
{
    int metadataY = 10;
    metadataTitleLabel.setBounds(20, metadataY, getWidth() - 40, 28);
    metadataArtistLabel.setBounds(20, metadataY + 34, getWidth() - 40, 24);
    metadataAlbumLabel.setBounds(20, metadataY + 60, getWidth() - 40, 22);
    metadataInfoLabel.setBounds(20, metadataY + 84, getWidth() - 40, 20);

    int y = 125;
    int buttonWidth = 70;
    int buttonHeight = 35;
    int spacing = 15;

    int numButtons = 13;
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
    clearPlaylistButton.setBounds(startX + (buttonWidth + spacing) * 11, y, buttonWidth, buttonHeight);
    unLoadTrack.setBounds(startX + (buttonWidth + spacing) * 12, y, buttonWidth, buttonHeight);

    int positionY = 185;
    currentTimeLabel.setBounds(20, positionY, 60, 20);
    totalTimeLabel.setBounds(getWidth() - 80, positionY, 60, 20);
    positionSlider.setBounds(85, positionY, getWidth() - 170, 20);

    volumeLabel.setBounds(20, 220, 80, 25);
    volumeSlider.setBounds(110, 220, getWidth() - 130, 25);

    speedLabel.setBounds(20, 255, 80, 25);
    speedslider.setBounds(110, 255, getWidth() - 130, 25);

    int abLoopY = 290;
    int abLoopButtonWidth = 100;
    int abLoopButtonHeight = 32;
    int abLoopSpacing = 10;

    int totalABWidth = 4 * abLoopButtonWidth + 3 * abLoopSpacing;
    int abStartX = (getWidth() - totalABWidth) / 2;

    setPointAButton.setBounds(abStartX, abLoopY, abLoopButtonWidth, abLoopButtonHeight);
    setPointBButton.setBounds(abStartX + abLoopButtonWidth + abLoopSpacing, abLoopY, abLoopButtonWidth, abLoopButtonHeight);
    clearABButton.setBounds(abStartX + 2 * (abLoopButtonWidth + abLoopSpacing), abLoopY, abLoopButtonWidth, abLoopButtonHeight);
    enableABLoopButton.setBounds(abStartX + 3 * (abLoopButtonWidth + abLoopSpacing), abLoopY, abLoopButtonWidth, abLoopButtonHeight);

    abLoopInfoLabel.setBounds(20, abLoopY + abLoopButtonHeight + 8, getWidth() - 40, 26);

    int markerY = abLoopY + abLoopButtonHeight + 42;
    markersLabel.setBounds(20, markerY, 150, 25);
    addMarkerButton.setBounds(180, markerY, 100, 25);
    clearMarkersButton.setBounds(290, markerY, 130, 25);

    int remainingHeight = getHeight() - (markerY + 35);
    int playlistHeight = static_cast<int>(remainingHeight * 0.6);
    int markersHeight = remainingHeight - playlistHeight - 10;

    playlistBox.setBounds(20, markerY + 35, getWidth() - 40, playlistHeight);
    markersListBox.setBounds(20, markerY + 35 + playlistHeight + 10, getWidth() - 40, markersHeight);
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
        propertiesFile->setValue("currentPlayingIndex", currentPlayingIndex);

        juce::StringArray playlistPaths;
        for (auto &file : playlistFiles)
        {
            playlistPaths.add(file.getFullPathName());
        }
        propertiesFile->setValue("playlistFiles", playlistPaths.joinIntoString("\n"));

        propertiesFile->setValue("trackTimes", trackTimes.joinIntoString("\n"));

        if (playerAudio.isPositionSetA())
        {
            propertiesFile->setValue("abLoopPointA", playerAudio.getPointA());
        }
        else
        {
            propertiesFile->removeValue("abLoopPointA");
        }

        if (playerAudio.isPositionSetB())
        {
            propertiesFile->setValue("abLoopPointB", playerAudio.getPointB());
        }
        else
        {
            propertiesFile->removeValue("abLoopPointB");
        }

        propertiesFile->setValue("abLoopEnabled", playerAudio.isABLoopEnabled());

        saveMarkers();

        propertiesFile->saveIfNeeded();
    }
}

void PlayerGUI::buttonClicked(juce::Button *button)
{
    if (button == &loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select an audio file...",
            juce::File{},
            "*.wav;*.mp3;*.flac;*.ogg;*.aac;*.m4a");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser &fc)
            {
                auto file = fc.getResult();
                if (file.existsAsFile())
                {
                    currentPlayingIndex = -1;

                    if (playerAudio.loadFile(file))
                    {
                        double totalLength = playerAudio.getLengthInSeconds();
                        totalTimeLabel.setText(formatTime(totalLength), juce::dontSendNotification);
                        currentTimeLabel.setText("00:00", juce::dontSendNotification);
                        positionSlider.setValue(0.0, juce::dontSendNotification);

                        updateMetadataDisplay();
                        markersListBox.updateContent();
                        markersListBox.repaint();
                    }
                    else
                    {
                        metadataTitleLabel.setText("Error loading file", juce::dontSendNotification);
                        metadataArtistLabel.setText("", juce::dontSendNotification);
                        metadataAlbumLabel.setText("", juce::dontSendNotification);
                        metadataInfoLabel.setText("", juce::dontSendNotification);
                    }
                }
                repaint();
            });
    }
    else if (button == &restartButton)
    {
        auto currentFile = playerAudio.getLastLoadedFile();
        if (currentFile.existsAsFile() && playlistFiles.size() > 0)
        {
            bool found = false;
            if (currentPlayingIndex >= 0 && currentPlayingIndex < playlistFiles.size())
            {
                if (playlistFiles[currentPlayingIndex] == currentFile)
                {
                    found = true;
                }
            }

            if (!found)
            {
                for (int i = 0; i < playlistFiles.size(); i++)
                {
                    if (playlistFiles[i] == currentFile)
                    {
                        currentPlayingIndex = i;
                        break;
                    }
                }
            }
        }

        double currentPos = playerAudio.getPosition();

        if (currentPos <= 0.02 && currentPlayingIndex > 0 && playlistFiles.size() > 1)
        {
            playPreviousTrack();
        }
        else
        {
            playerAudio.setPosition(0.0);
            PlayButton.setImages(false, true, true,
                                 pauseimage, 1.0f, juce::Colours::transparentBlack,
                                 pauseimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                                 playimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
            playerAudio.start();
        }
    }
    else if (button == &addFilesButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select Audio Files",
            juce::File{},
            "*.mp3;*.wav;*.aiff");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles | juce::FileBrowserComponent::canSelectMultipleItems,
            [this](const juce::FileChooser &fc)
            {
                auto files = fc.getResults();
                double duration = 0.0;
                for (auto &f : files)
                {
                    playlistFiles.addIfNotAlreadyThere(f);
                    juce::AudioFormatManager formatManager;
                    formatManager.registerBasicFormats();
                    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(f));
                    if (reader != nullptr)
                        duration = reader->lengthInSamples / reader->sampleRate;
                    trackTimes.addIfNotAlreadyThere(formatTime(duration));
                }

                playlistBox.updateContent();
                playlistBox.repaint();
            });
    }
    else if (button == &BeginButton)
    {
        auto currentFile = playerAudio.getLastLoadedFile();
        if (currentFile.existsAsFile() && playlistFiles.size() > 0)
        {
            bool found = false;
            if (currentPlayingIndex >= 0 && currentPlayingIndex < playlistFiles.size())
            {
                if (playlistFiles[currentPlayingIndex] == currentFile)
                {
                    found = true;
                }
            }

            if (!found)
            {
                for (int i = 0; i < playlistFiles.size(); i++)
                {
                    if (playlistFiles[i] == currentFile)
                    {
                        currentPlayingIndex = i;
                        break;
                    }
                }
            }
        }

        double currentPos = playerAudio.getPosition();

        if (currentPos <= 0.02 && currentPlayingIndex > 0 && playlistFiles.size() > 1)
        {
            playPreviousTrack();
        }
        else
        {
            playerAudio.setPosition(0.0);
            playerAudio.stop();

            PlayButton.setImages(false, true, true,
                                 playimage, 1.0f, juce::Colours::transparentBlack,
                                 playimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                                 pauseimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
        }
    }
    else if (button == &EndButton)
    {
        if (isLooping)
        {
            playerAudio.setPosition(0.0);
            playerAudio.start();
            PlayButton.setImages(false, true, true,
                                 pauseimage, 1.0f, juce::Colours::transparentBlack,
                                 pauseimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                                 playimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
        }
        else
        {
            playerAudio.setPosition(playerAudio.getLength() - 0.05);
            playerAudio.stop();

            PlayButton.setImages(false, true, true,
                                 playimage, 1.0f, juce::Colours::transparentBlack,
                                 playimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                                 pauseimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
        }
    }
    else if (button == &loadLast)
    {
        auto savedPlaylist = propertiesFile->getValue("playlistFiles");
        if (!savedPlaylist.isEmpty())
        {
            playlistFiles.clear();
            trackTimes.clear();

            juce::StringArray playlistPaths;
            playlistPaths.addTokens(savedPlaylist, "\n", "");

            for (auto &path : playlistPaths)
            {
                if (path.isNotEmpty())
                {
                    juce::File file(path);
                    if (file.existsAsFile())
                    {
                        playlistFiles.add(file);

                        juce::AudioFormatManager formatManager;
                        formatManager.registerBasicFormats();
                        std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));
                        double duration = 0.0;
                        if (reader != nullptr)
                            duration = reader->lengthInSamples / reader->sampleRate;
                        trackTimes.add(formatTime(duration));
                    }
                }
            }

            playlistBox.updateContent();
            playlistBox.repaint();
        }

        auto savedTrackTimes = propertiesFile->getValue("trackTimes");
        if (!savedTrackTimes.isEmpty() && playlistFiles.size() > 0 && trackTimes.size() < playlistFiles.size())
        {
            trackTimes.clear();
            juce::StringArray times;
            times.addTokens(savedTrackTimes, "\n", "");
            for (auto &time : times)
            {
                if (time.isNotEmpty())
                    trackTimes.add(time);
            }

            while (trackTimes.size() < playlistFiles.size())
            {
                int index = trackTimes.size();
                juce::File file = playlistFiles[index];
                juce::AudioFormatManager formatManager;
                formatManager.registerBasicFormats();
                std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));
                double duration = 0.0;
                if (reader != nullptr)
                    duration = reader->lengthInSamples / reader->sampleRate;
                trackTimes.add(formatTime(duration));
            }
        }

        auto savedIndex = propertiesFile->getIntValue("currentPlayingIndex", -1);
        auto lastPath = propertiesFile->getValue("lastFilePath");

        if (!lastPath.isEmpty())
        {
            lastFile = juce::File(lastPath);

            if (lastFile.existsAsFile())
            {
                currentPlayingIndex = -1;
                if (savedIndex >= 0 && savedIndex < playlistFiles.size() && playlistFiles[savedIndex] == lastFile)
                {
                    currentPlayingIndex = savedIndex;
                }
                else
                {
                    for (int i = 0; i < playlistFiles.size(); i++)
                    {
                        if (playlistFiles[i] == lastFile)
                        {
                            currentPlayingIndex = i;
                            break;
                        }
                    }
                }

                if (currentPlayingIndex >= 0)
                {
                    playlistBox.selectRow(currentPlayingIndex);
                }

                playerAudio.loadFile(lastFile);

                juce::Timer::callAfterDelay(300, [this]()
                {
                    playerAudio.setSpeed(static_cast<float>(lastSpeed));
                    playerAudio.setPosition(lastPosition);

                    isMuted = mutedState;
                    
                    if (mutedState)
                    {
                        previousGain = (float)lastVolume;
                        playerAudio.setGain(0.0f);
                        volumeSlider.setValue(0.0, juce::dontSendNotification);
                        volumeLabel.setText("Volume: 0.00", juce::dontSendNotification);
                        MuteButton.setImages(false, true, true,
                            mutedImage, 1.0f, juce::Colours::transparentBlack,
                            mutedImage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                            unmutedImage, 1.0f, juce::Colours::white.withAlpha(0.6f));
                    }
                    else
                    {
                        playerAudio.setGain((float)lastVolume);
                        volumeSlider.setValue(lastVolume, juce::dontSendNotification);
                        previousGain = (float)lastVolume;
                        volumeLabel.setText("Volume: " + juce::String(lastVolume, 2), juce::dontSendNotification);
                        MuteButton.setImages(false, true, true,
                            unmutedImage, 1.0f, juce::Colours::transparentBlack,
                            unmutedImage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                            mutedImage, 1.0f, juce::Colours::white.withAlpha(0.6f));
                    }

                    speedslider.setValue(lastSpeed, juce::dontSendNotification);
                    speedLabel.setText("Speed: " + juce::String(lastSpeed, 2) + "x", juce::dontSendNotification);
                    
                    totalTimeLabel.setText(lastFullTime, juce::dontSendNotification);
                    currentTimeLabel.setText(formatTime(lastPosition), juce::dontSendNotification);
                    if (auto totalLength = playerAudio.getLengthInSeconds(); totalLength > 0.0)
                        positionSlider.setValue(lastPosition / totalLength, juce::dontSendNotification);

                    double savedPointA = propertiesFile->getDoubleValue("abLoopPointA", -1.0);
                    double savedPointB = propertiesFile->getDoubleValue("abLoopPointB", -1.0);
                    bool savedABLoopEnabled = propertiesFile->getBoolValue("abLoopEnabled", false);
                    
                    if (savedPointA >= 0.0)
                    {
                        playerAudio.setPointA(savedPointA);
                    }
                    
                    if (savedPointB >= 0.0)
                    {
                        playerAudio.setPointB(savedPointB);
                    }
                    
                    isABLoopEnabled = savedABLoopEnabled;
                    playerAudio.setABLoopEnabled(savedABLoopEnabled);
                    enableABLoopButton.setToggleState(savedABLoopEnabled, juce::dontSendNotification);
                    
                    if (playerAudio.isPositionSetA())
                    {
                        setPointAButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF2980B9));
                    }
                    else
                    {
                        setPointAButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF3498DB));
                    }
                    
                    if (playerAudio.isPositionSetB())
                    {
                        setPointBButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0392B));
                    }
                    else
                    {
                        setPointBButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE74C3C));
                    }
                    
                    updateABLoopDisplay();
                    markersListBox.updateContent();
                    markersListBox.repaint();
                    repaint();

                    updateMetadataDisplay();
                });
            }
        }
    }
    else if (button == &PlayButton)
    {
        if (playerAudio.isPlaying())
        {
            playerAudio.stop();

            PlayButton.setImages(false, true, true,
                                 playimage, 1.0f, juce::Colours::transparentBlack,
                                 playimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                                 pauseimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
        }
        else
        {
            playerAudio.start();

            PlayButton.setImages(false, true, true,
                                 pauseimage, 1.0f, juce::Colours::transparentBlack,
                                 pauseimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                                 playimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
        }
    }
    else if (button == &MuteButton)
    {
        if (isMuted)
        {
            playerAudio.setGain(previousGain);
            volumeSlider.setValue(previousGain, juce::dontSendNotification);
            volumeLabel.setText("Volume: " + juce::String((double)previousGain, 2), juce::dontSendNotification);
            isMuted = false;
            MuteButton.setImages(false, true, true,
                                 unmutedImage, 1.0f, juce::Colours::transparentBlack,
                                 unmutedImage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                                 mutedImage, 1.0f, juce::Colours::white.withAlpha(0.6f));
        }
        else
        {
            previousGain = (float)volumeSlider.getValue();
            playerAudio.setGain(0.0f);
            volumeSlider.setValue(0.0, juce::dontSendNotification);
            volumeLabel.setText("Volume: 0.00", juce::dontSendNotification);
            isMuted = true;
            MuteButton.setImages(false, true, true,
                                 mutedImage, 1.0f, juce::Colours::transparentBlack,
                                 mutedImage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                                 unmutedImage, 1.0f, juce::Colours::white.withAlpha(0.6f));
        }
    }
    else if (button == &LoopButton)
    {
        if (isLooping)
        {
            playerAudio.setLooping(false);
            isLooping = false;
            LoopButton.setImages(false, true, true,
                                 unloopimage, 1.0f, juce::Colours::transparentBlack,
                                 unloopimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                                 loopimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
        }
        else
        {
            playerAudio.setLooping(true);
            isLooping = true;
            LoopButton.setImages(false, true, true,
                                 loopimage, 1.0f, juce::Colours::transparentBlack,
                                 loopimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                                 unloopimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
        }
    }
    else if (button == &forwardButton)
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
    else if (button == &setPointAButton)
    {
        if (playerAudio.isPositionSetA())
        {
            playerAudio.clearPositionA();
            setPointAButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF3498DB));
        }
        else
        {
            playerAudio.setPointA(playerAudio.getPosition());
            setPointAButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF2980B9));
        }
        updateABLoopDisplay();
        repaint();
    }
    else if (button == &setPointBButton)
    {
        if (playerAudio.isPositionSetB())
        {
            playerAudio.clearPositionB();
            setPointBButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE74C3C));
        }
        else
        {
            playerAudio.setPointB(playerAudio.getPosition());
            setPointBButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFC0392B));
        }
        updateABLoopDisplay();
        repaint();
    }
    else if (button == &clearABButton)
    {
        playerAudio.clearPositionA();
        playerAudio.clearPositionB();
        setPointAButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF3498DB));
        setPointBButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE74C3C));
        updateABLoopDisplay();
        repaint();
    }
    else if (button == &enableABLoopButton)
    {
        isABLoopEnabled = !isABLoopEnabled;
        playerAudio.setABLoopEnabled(isABLoopEnabled);
        enableABLoopButton.setToggleState(isABLoopEnabled, juce::dontSendNotification);
        updateABLoopDisplay();
        repaint();
    }
    else if (button == &clearPlaylistButton)
    {
        playlistFiles.clear();
        trackTimes.clear();
        currentPlayingIndex = -1;
        playlistBox.updateContent();
        playlistBox.repaint();
        playerAudio.setPosition(0.0);
        PlayButton.setImages(false, true, true,
                             playimage, 1.0f, juce::Colours::transparentBlack,
                             playimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                             pauseimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
        playerAudio.unloadFile();
        unloadMetaData();
        positionSlider.setValue(0.0, juce::dontSendNotification);
        currentTimeLabel.setText("00:00", juce::dontSendNotification);
        totalTimeLabel.setText("00:00", juce::dontSendNotification);
    }
    else if (button == &unLoadTrack)
    {
        currentPlayingIndex = -1;
        playerAudio.setPosition(0.0);
        PlayButton.setImages(false, true, true,
                             playimage, 1.0f, juce::Colours::transparentBlack,
                             playimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                             pauseimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
        playerAudio.unloadFile();
        unloadMetaData();
        positionSlider.setValue(0.0, juce::dontSendNotification);
        currentTimeLabel.setText("00:00", juce::dontSendNotification);
        totalTimeLabel.setText("00:00", juce::dontSendNotification);
    }
    else if (button == &addMarkerButton)
    {
        addMarker();
    }
    else if (button == &clearMarkersButton)
    {
        if (!markers.empty())
        {
            markers.clear();
            markerCounter = 0;
            markersListBox.updateContent();
            markersListBox.repaint();
            saveMarkers();
            repaint();
        }
    }
}

void PlayerGUI::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &volumeSlider)
    {
        float v = (float)slider->getValue();
        playerAudio.setGain(v);
        volumeLabel.setText("Volume: " + juce::String(v, 2), juce::dontSendNotification);

        if (!isMuted)
        {
            previousGain = v;
        }
    }
    else if (slider == &speedslider)
    {
        float s = (float)speedslider.getValue();
        playerAudio.setSpeed(s);
        speedLabel.setText("Speed: " + juce::String(s, 2) + "x", juce::dontSendNotification);
    }
    else if (slider == &positionSlider)
    {
        isDraggingSlider = true;
        double totalLength = playerAudio.getLengthInSeconds();
        double newPosition = slider->getValue() * totalLength;
        playerAudio.setPosition(newPosition);
        currentTimeLabel.setText(formatTime(newPosition), juce::dontSendNotification);

        juce::Timer::callAfterDelay(100, [this]()
                                    { isDraggingSlider = false; });
    }
}

void PlayerGUI::timerCallback()
{
    if (!isDraggingSlider)
    {
        updatePositionSlider();
    }

    if (playerAudio.isPlaying() && !isLooping && !playerAudio.isABLoopEnabled())
    {
        double currentPos = playerAudio.getPosition();
        double totalLength = playerAudio.getLengthInSeconds();

        if (totalLength > 0.0 && currentPos >= totalLength - 0.1)
        {
            playNextTrack();
        }
    }
    else if (!playerAudio.isPlaying() && currentPlayingIndex >= 0 && !isLooping && !playerAudio.isABLoopEnabled())
    {
        double currentPos = playerAudio.getPosition();
        double totalLength = playerAudio.getLengthInSeconds();

        if (totalLength > 0.0 && currentPos >= totalLength - 0.1)
        {
            playNextTrack();
        }
    }

    repaint();

    static int counter = 0;
    if (++counter >= 100)
    {
        if (propertiesFile)
        {
            propertiesFile->setValue("lastFilePath", playerAudio.getLastLoadedFile().getFullPathName());
            propertiesFile->setValue("lastPosition", playerAudio.getPosition());
            propertiesFile->setValue("volume", isMuted ? previousGain : volumeSlider.getValue());
            propertiesFile->setValue("speed", speedslider.getValue());
            propertiesFile->setValue("totalTime", totalTimeLabel.getText());
            propertiesFile->setValue("mutedState", isMuted);
            propertiesFile->setValue("currentPlayingIndex", currentPlayingIndex);

            juce::StringArray playlistPaths;
            for (auto &file : playlistFiles)
            {
                playlistPaths.add(file.getFullPathName());
            }
            propertiesFile->setValue("playlistFiles", playlistPaths.joinIntoString("\n"));
            propertiesFile->setValue("trackTimes", trackTimes.joinIntoString("\n"));

            if (playerAudio.isPositionSetA())
            {
                propertiesFile->setValue("abLoopPointA", playerAudio.getPointA());
            }
            else
            {
                propertiesFile->removeValue("abLoopPointA");
            }

            if (playerAudio.isPositionSetB())
            {
                propertiesFile->setValue("abLoopPointB", playerAudio.getPointB());
            }
            else
            {
                propertiesFile->removeValue("abLoopPointB");
            }

            propertiesFile->setValue("abLoopEnabled", playerAudio.isABLoopEnabled());
            saveMarkers();

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
    const AudioMetadata &metadata = playerAudio.getMetadata();

    if (metadata.hasMetadata && !metadata.title.isEmpty())
        metadataTitleLabel.setText(metadata.title, juce::dontSendNotification);
    else
        metadataTitleLabel.setText(metadata.filename, juce::dontSendNotification);

    if (metadata.hasMetadata && !metadata.artist.isEmpty())
        metadataArtistLabel.setText(metadata.artist, juce::dontSendNotification);
    else
        metadataArtistLabel.setText("Unknown Artist", juce::dontSendNotification);

    if (metadata.hasMetadata && !metadata.album.isEmpty())
        metadataAlbumLabel.setText("Album: " + metadata.album, juce::dontSendNotification);
    else
        metadataAlbumLabel.setText("", juce::dontSendNotification);

    juce::String info;
    if (metadata.bitrate > 0)
        info << metadata.bitrate << " kbps";
    if (metadata.sampleRate > 0)
    {
        if (!info.isEmpty())
            info << " • ";
        info << (metadata.sampleRate / 1000.0) << " kHz";
    }
    if (metadata.channels > 0)
    {
        if (!info.isEmpty())
            info << " • ";
        info << metadata.channels << (metadata.channels == 1 ? " channel" : " channels");
    }
    if (metadata.hasMetadata && !metadata.genre.isEmpty())
    {
        if (!info.isEmpty())
            info << " • ";
        info << metadata.genre;
    }

    metadataInfoLabel.setText(info, juce::dontSendNotification);
}

int PlayerGUI::getNumRows()
{
    return playlistFiles.size();
}

void PlayerGUI::paintListBoxItem(int rowNumber, juce::Graphics &g,
                                 int width, int height, bool rowIsSelected)
{
    // This function is still called for fallback, but refreshComponentForRow will handle the rendering
    // with the custom component that includes the delete button
}

juce::Component *PlayerGUI::refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component *existingComponentToUpdate)
{
    // Determine which ListBox is requesting this
    auto* parent = existingComponentToUpdate != nullptr ? existingComponentToUpdate->getParentComponent() : nullptr;
    
    // Check if this is for the markers list
    if (parent == &markersListBox || (!existingComponentToUpdate && rowNumber < static_cast<int>(markers.size())))
    {
        juce::String currentFileId = getCurrentFileId();
        std::vector<int> currentFileMarkerIndices;
        
        // Get indices of markers for current file
        for (int i = 0; i < static_cast<int>(markers.size()); i++)
        {
            if (markers[i].fileId == currentFileId)
                currentFileMarkerIndices.push_back(i);
        }
        
        if (rowNumber >= static_cast<int>(currentFileMarkerIndices.size()))
            return nullptr;
            
        int actualMarkerIndex = currentFileMarkerIndices[rowNumber];
        
        MarkerRowComponent* markerRow = dynamic_cast<MarkerRowComponent*>(existingComponentToUpdate);
        
        if (markerRow == nullptr)
        {
            markerRow = new MarkerRowComponent(this);
        }
        
        const auto& marker = markers[actualMarkerIndex];
        markerRow->updateRow(actualMarkerIndex, marker.label, formatTime(marker.timestamp));
        
        return markerRow;
    }
    
    // Handle playlist
    if (rowNumber >= playlistFiles.size())
        return nullptr;

    PlaylistRowComponent *rowComponent = dynamic_cast<PlaylistRowComponent *>(existingComponentToUpdate);

    if (rowComponent == nullptr)
    {
        rowComponent = new PlaylistRowComponent(this);
        rowComponent->setInterceptsMouseClicks(true, true);
    }

    auto filename = playlistFiles[rowNumber].getFileNameWithoutExtension();
    auto fileDuration = trackTimes[rowNumber];
    rowComponent->updateRow(rowNumber, filename, fileDuration, isRowSelected);

    return rowComponent;
}

int PlayerGUI::getPlaylistSize() const
{
    return playlistFiles.size();
}

juce::var PlayerGUI::getDragSourceDescription(const juce::SparseSet<int> &selectedRows)
{
    if (selectedRows.size() > 0)
    {
        return juce::var(selectedRows[0]);
    }
    return juce::var();
}

bool PlayerGUI::isInterestedInDragSource(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails)
{
    return dragSourceDetails.description.isInt() || dragSourceDetails.description.toString().containsOnly("0123456789");
}

void PlayerGUI::itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails)
{
    int sourceIndex = dragSourceDetails.description.toString().getIntValue();

    if (sourceIndex < 0 || sourceIndex >= playlistFiles.size())
        return;

    auto mousePos = getMouseXYRelative();
    auto listBoxBounds = playlistBox.getBounds();

    if (!listBoxBounds.contains(mousePos))
        return;

    int rowHeight = playlistBox.getRowHeight();
    int relativeY = mousePos.y - listBoxBounds.getY();
    int targetRow = relativeY / rowHeight;

    rowsDropped(dragSourceDetails, targetRow);
}

void PlayerGUI::rowsDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex)
{
    int sourceIndex = dragSourceDetails.description.toString().getIntValue();

    if (sourceIndex < 0 || sourceIndex >= playlistFiles.size() || insertIndex < 0)
        return;

    int destinationIndex = insertIndex;

    if (insertIndex > sourceIndex)
    {
        destinationIndex = insertIndex - 1;
    }

    if (destinationIndex == sourceIndex)
        return;

    if (destinationIndex < 0)
        destinationIndex = 0;
    if (destinationIndex > playlistFiles.size())
        destinationIndex = playlistFiles.size();

    isReorderingPlaylist = true;

    bool wasCurrentlyPlaying = (currentPlayingIndex == sourceIndex);

    reorderPlaylistItems(sourceIndex, destinationIndex);

    if (wasCurrentlyPlaying)
    {
        currentPlayingIndex = destinationIndex;
    }
    else if (sourceIndex < currentPlayingIndex && destinationIndex >= currentPlayingIndex)
    {
        currentPlayingIndex--;
    }
    else if (sourceIndex > currentPlayingIndex && destinationIndex <= currentPlayingIndex)
    {
        currentPlayingIndex++;
    }

    playlistBox.updateContent();
    playlistBox.repaint();
    playlistBox.selectRow(destinationIndex);

    juce::Timer::callAfterDelay(50, [this]()
                                { isReorderingPlaylist = false; });
}

void PlayerGUI::reorderPlaylistItems(int sourceIndex, int destinationIndex)
{
    if (sourceIndex < 0 || sourceIndex >= playlistFiles.size() ||
        destinationIndex < 0 || destinationIndex > playlistFiles.size())
        return;

    if (sourceIndex == destinationIndex)
        return;

    juce::File movedFile = playlistFiles[sourceIndex];
    juce::String movedTime = trackTimes[sourceIndex];

    playlistFiles.remove(sourceIndex);
    trackTimes.remove(sourceIndex);

    int adjustedDestination = juce::jlimit(0, playlistFiles.size(), destinationIndex);

    playlistFiles.insert(adjustedDestination, movedFile);
    trackTimes.insert(adjustedDestination, movedTime);
}

void PlayerGUI::selectPlaylistRow(int rowIndex)
{
    if (rowIndex >= 0 && rowIndex < playlistFiles.size())
    {
        playlistBox.selectRow(rowIndex);
        selectedRowsChanged(rowIndex);
    }
}

void PlayerGUI::selectedRowsChanged(int lastRowSelected)
{
    if (isReorderingPlaylist)
    {
        return;
    }

    if (lastRowSelected >= 0 && lastRowSelected < playlistFiles.size())
    {
        auto file = playlistFiles[lastRowSelected];

        currentPlayingIndex = lastRowSelected;

        if (playerAudio.isPlaying())
        {
            playerAudio.stop();
        }

        if (playerAudio.loadFile(file))
        {
            playerAudio.start();

            PlayButton.setImages(false, true, true,
                                 pauseimage, 1.0f, juce::Colours::transparentBlack,
                                 pauseimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                                 playimage, 1.0f, juce::Colours::white.withAlpha(0.6f));

            totalTimeLabel.setText(formatTime(playerAudio.getLengthInSeconds()), juce::dontSendNotification);
            currentTimeLabel.setText("00:00", juce::dontSendNotification);
            positionSlider.setValue(0.0, juce::dontSendNotification);
            updateMetadataDisplay();
            markersListBox.updateContent();
            markersListBox.repaint();
        }
    }
}

void PlayerGUI::updateABLoopDisplay()
{
    if (playerAudio.hasValidABLoop())
    {
        double pointA = playerAudio.getPointA();
        double pointB = playerAudio.getPointB();

        juce::String info = "A: " + formatTime(pointA) + "  :  B: " + formatTime(pointB);
        abLoopInfoLabel.setText(info, juce::dontSendNotification);

        if (playerAudio.isABLoopEnabled())
        {
            enableABLoopButton.setButtonText("A-B Loop: ON");
            enableABLoopButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF27AE60));
        }
        else
        {
            enableABLoopButton.setButtonText("A-B Loop: OFF");
            enableABLoopButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF2ECC71));
        }
    }
    else
    {
        abLoopInfoLabel.setText("A-B Loop: Not set", juce::dontSendNotification);
        enableABLoopButton.setButtonText("A-B Loop: OFF");
        enableABLoopButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF2ECC71));
    }
}

void PlayerGUI::unloadMetaData()
{
    metadataTitleLabel.setText("No file loaded", juce::dontSendNotification);
    metadataArtistLabel.setText("", juce::dontSendNotification);
    metadataAlbumLabel.setText("", juce::dontSendNotification);
    metadataInfoLabel.setText("", juce::dontSendNotification);
}

void PlayerGUI::playNextTrack()
{
    if (currentPlayingIndex < 0 || playlistFiles.size() == 0)
        return;

    int nextIndex = currentPlayingIndex + 1;

    if (nextIndex < playlistFiles.size())
    {
        selectPlaylistRow(nextIndex);
    }
    else
    {
        playerAudio.stop();
        PlayButton.setImages(false, true, true,
                             playimage, 1.0f, juce::Colours::transparentBlack,
                             playimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                             pauseimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
        currentPlayingIndex = -1;
    }
}

void PlayerGUI::playPreviousTrack()
{
    if (currentPlayingIndex <= 0 || playlistFiles.size() == 0)
        return;

    int previousIndex = currentPlayingIndex - 1;

    if (previousIndex >= 0)
    {
        selectPlaylistRow(previousIndex);
    }
}

void PlayerGUI::deleteTrack(int index)
{
    if (index >= 0 && index < playlistFiles.size())
    {
        auto fileToDelete = playlistFiles[index];
        bool wasCurrentlyPlaying = (currentPlayingIndex == index);

        playlistFiles.remove(index);
        trackTimes.remove(index);
        playlistBox.updateContent();
        playlistBox.repaint();

        if (wasCurrentlyPlaying)
        {
            if (index < currentPlayingIndex)
            {
                currentPlayingIndex--;
            }

            playerAudio.setPosition(0.0);
            playerAudio.stop();
            playerAudio.unloadFile();

            if (playlistFiles.size() > 0)
            {
                if (index < playlistFiles.size())
                {
                    currentPlayingIndex = index;
                }
                else if (index > 0)
                {
                    currentPlayingIndex = index - 1;
                }
                else
                {
                    currentPlayingIndex = 0;
                }

                selectPlaylistRow(currentPlayingIndex);
            }
            else
            {
                currentPlayingIndex = -1;
                PlayButton.setImages(false, true, true,
                                     playimage, 1.0f, juce::Colours::transparentBlack,
                                     playimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                                     pauseimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
                unloadMetaData();
                positionSlider.setValue(0.0, juce::dontSendNotification);
                currentTimeLabel.setText("00:00", juce::dontSendNotification);
                totalTimeLabel.setText("00:00", juce::dontSendNotification);
            }
        }
        else if (index < currentPlayingIndex)
        {
            currentPlayingIndex--;
        }
    }
}

void PlayerGUI::addMarker()
{
    double currentTime = playerAudio.getPosition();

    if (playerAudio.getLengthInSeconds() <= 0.0)
    {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "No File Loaded",
            "Please load an audio file before adding markers.",
            "OK");
        return;
    }

    markerCounter++;
    juce::String markerLabel = "Marker " + juce::String(markerCounter) + " (" + formatTime(currentTime) + ")";
    juce::String fileId = getCurrentFileId();

    markers.emplace_back(currentTime, markerLabel, fileId);

    std::sort(markers.begin(), markers.end(),
              [](const TrackMarker& a, const TrackMarker& b) {
                  return a.timestamp < b.timestamp;
              });

    markersListBox.updateContent();
    markersListBox.repaint();

    saveMarkers();
    repaint();
}

void PlayerGUI::jumpToMarker(int markerIndex)
{
    if (markerIndex >= 0 && markerIndex < static_cast<int>(markers.size()))
    {
        const auto& marker = markers[markerIndex];

        if (marker.fileId != getCurrentFileId())
        {
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::InfoIcon,
                "Different Track",
                "This marker belongs to a different audio file.",
                "OK");
            return;
        }

        playerAudio.setPosition(marker.timestamp);

        if (!playerAudio.isPlaying())
        {
            playerAudio.start();
            PlayButton.setImages(false, true, true,
                                pauseimage, 1.0f, juce::Colours::transparentBlack,
                                pauseimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                                playimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
        }

        updatePositionSlider();
        repaint();
    }
}

void PlayerGUI::deleteMarker(int markerIndex)
{
    if (markerIndex >= 0 && markerIndex < static_cast<int>(markers.size()))
    {
        markers.erase(markers.begin() + markerIndex);
        markersListBox.updateContent();
        markersListBox.repaint();
        saveMarkers();
        repaint();
    }
}

juce::String PlayerGUI::getCurrentFileId() const
{
    auto currentFile = playerAudio.getLastLoadedFile();
    if (currentFile.existsAsFile())
    {
        return currentFile.getFullPathName();
    }
    return juce::String();
}

void PlayerGUI::loadMarkersForCurrentFile()
{
}

void PlayerGUI::saveMarkers()
{
    if (!propertiesFile)
        return;

    juce::StringArray markerData;
    for (const auto& marker : markers)
    {
        juce::String data = juce::String(marker.timestamp) + "|" +
                           marker.label + "|" +
                           marker.fileId;
        markerData.add(data);
    }

    propertiesFile->setValue("trackMarkers", markerData.joinIntoString("\n"));
    propertiesFile->setValue("markerCounter", markerCounter);
    propertiesFile->saveIfNeeded();
}

void PlayerGUI::loadMarkers()
{
    if (!propertiesFile)
        return;

    markers.clear();
    auto savedMarkers = propertiesFile->getValue("trackMarkers");
    markerCounter = propertiesFile->getIntValue("markerCounter", 0);

    if (!savedMarkers.isEmpty())
    {
        juce::StringArray markerLines;
        markerLines.addTokens(savedMarkers, "\n", "");

        for (const auto& line : markerLines)
        {
            if (line.isEmpty())
                continue;

            juce::StringArray parts;
            parts.addTokens(line, "|", "");

            if (parts.size() >= 3)
            {
                double timestamp = parts[0].getDoubleValue();
                juce::String label = parts[1];
                juce::String fileId = parts[2];

                markers.emplace_back(timestamp, label, fileId);
            }
        }
    }

    markersListBox.updateContent();
    markersListBox.repaint();
}