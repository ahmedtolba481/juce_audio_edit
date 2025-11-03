#include "PlayerGUI.h"

// PlaylistRowComponent implementation
PlaylistRowComponent::PlaylistRowComponent(PlayerGUI *parent) : owner(parent)
{
    filenameLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFE8E8E8));
    filenameLabel.setFont(juce::FontOptions(14.0f, juce::Font::plain));
    filenameLabel.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(filenameLabel);

    durationLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFB0B8C4));
    durationLabel.setFont(juce::FontOptions(12.0f, juce::Font::plain));
    durationLabel.setJustificationType(juce::Justification::centred);
    durationLabel.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(durationLabel);

    deleteButton.setButtonText("✕");
    deleteButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE74C3C));
    deleteButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFFFF5555));
    deleteButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    deleteButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    deleteButton.setColour(juce::ComboBox::outlineColourId, juce::Colour(0xFFFFFFFF).withAlpha(0.2f));
    deleteButton.getProperties().set("fontSize", 14.0f);
    deleteButton.setConnectedEdges(0);
    deleteButton.addListener(this);
    addAndMakeVisible(deleteButton);
}

void PlaylistRowComponent::updateRow(int rowIndex, const juce::String &filename, const juce::String &duration, bool isSelected)
{
    currentRow = rowIndex;
    filenameLabel.setText(filename, juce::dontSendNotification);
    durationLabel.setText(duration, juce::dontSendNotification);

    if (isSelected)
    {
        setBackgroundColour(juce::Colour(0xFF4A90E2));
        filenameLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        durationLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFE0E8FF));
    }
    else
    {
        setBackgroundColour(rowIndex % 2 == 0 ? juce::Colour(0xFF2A2F3E) : juce::Colour(0xFF252A3A));
        filenameLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFE8E8E8));
        durationLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFB0B8C4));
    }
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
    auto bounds = getLocalBounds().toFloat();

    // Fill background with rounded corners
    g.setColour(backgroundColour);
    g.fillRoundedRectangle(bounds, 3.0f);

    // Subtle border
    g.setColour(juce::Colour(0x20FFFFFF));
    g.drawRoundedRectangle(bounds.reduced(0.5f), 3.0f, 0.5f);

    // Hover effect
    if (isMouseOver())
    {
        g.setColour(juce::Colours::white.withAlpha(0.08f));
        g.fillRoundedRectangle(bounds, 3.0f);
    }
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

juce::Rectangle<int> PlaylistRowComponent::getDeleteButtonBounds() const
{
    auto bounds = getLocalBounds();
    return juce::Rectangle<int>(bounds.getWidth() - 65, 2, 60, bounds.getHeight() - 4);
}

bool PlaylistRowComponent::isClickOnDeleteButton(const juce::MouseEvent &event)
{
    auto localPos = event.getEventRelativeTo(this).position.toInt();
    return getDeleteButtonBounds().contains(localPos);
}

void PlaylistRowComponent::mouseDown(const juce::MouseEvent &event)
{
    if (isClickOnDeleteButton(event))
        return;

    Component::mouseDown(event);
}

void PlaylistRowComponent::mouseDoubleClick(const juce::MouseEvent &event)
{
    if (isClickOnDeleteButton(event))
        return;

    if (owner != nullptr && currentRow >= 0 && currentRow < owner->getPlaylistSize())
    {
        owner->selectPlaylistRow(currentRow);
    }
}

void PlaylistRowComponent::mouseDrag(const juce::MouseEvent &event)
{
    if (isClickOnDeleteButton(event))
        return;

    if (currentRow >= 0 && event.mouseWasDraggedSinceMouseDown())
    {
        if (auto *dragContainer = juce::DragAndDropContainer::findParentDragContainerFor(this))
        {
            dragContainer->startDragging(juce::var(currentRow), this);
        }
    }
}

// MarkerRowComponent implementation
MarkerRowComponent::MarkerRowComponent(PlayerGUI *parent) : owner(parent)
{
    markerLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFE8E8E8));
    markerLabel.setFont(juce::FontOptions(13.0f, juce::Font::bold));
    markerLabel.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(markerLabel);

    timeLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF9B59B6));
    timeLabel.setFont(juce::FontOptions(12.0f, juce::Font::plain));
    timeLabel.setJustificationType(juce::Justification::centredRight);
    timeLabel.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(timeLabel);

    deleteButton.setButtonText("✕");
    deleteButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE74C3C));
    deleteButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFFFF5555));
    deleteButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    deleteButton.getProperties().set("fontSize", 14.0f);
    deleteButton.addListener(this);
    addAndMakeVisible(deleteButton);
}

void MarkerRowComponent::updateRow(int rowIndex, const juce::String &label, const juce::String &time)
{
    currentRow = rowIndex;
    markerLabel.setText(label, juce::dontSendNotification);
    timeLabel.setText(time, juce::dontSendNotification);
    backgroundColour = rowIndex % 2 == 0 ? juce::Colour(0xFF2F3445) : juce::Colour(0xFF282D3E);
}

void MarkerRowComponent::resized()
{
    auto bounds = getLocalBounds();
    deleteButton.setBounds(bounds.getWidth() - 30, 2, 25, bounds.getHeight() - 4);
    timeLabel.setBounds(bounds.getWidth() - 100, 0, 65, bounds.getHeight());
    markerLabel.setBounds(10, 0, bounds.getWidth() - 110, bounds.getHeight());
}

void MarkerRowComponent::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds().toFloat();

    // Fill background with rounded corners
    g.setColour(backgroundColour);
    g.fillRoundedRectangle(bounds, 3.0f);

    // Subtle border
    g.setColour(juce::Colour(0x20FFFFFF));
    g.drawRoundedRectangle(bounds.reduced(0.5f), 3.0f, 0.5f);

    // Hover effect
    if (isMouseOver())
    {
        g.setColour(juce::Colour(0xFF9B59B6).withAlpha(0.15f));
        g.fillRoundedRectangle(bounds, 3.0f);
    }
}

void MarkerRowComponent::buttonClicked(juce::Button *button)
{
    if (button == &deleteButton && owner != nullptr)
    {
        owner->deleteMarker(currentRow);
    }
}

juce::Rectangle<int> MarkerRowComponent::getDeleteButtonBounds() const
{
    auto bounds = getLocalBounds();
    return juce::Rectangle<int>(bounds.getWidth() - 30, 2, 25, bounds.getHeight() - 4);
}

bool MarkerRowComponent::isClickOnDeleteButton(const juce::MouseEvent &event)
{
    auto localPos = event.getEventRelativeTo(this).position.toInt();
    return getDeleteButtonBounds().contains(localPos);
}

void MarkerRowComponent::mouseDown(const juce::MouseEvent &event)
{
    if (isClickOnDeleteButton(event))
        return;

    if (owner != nullptr && currentRow >= 0)
    {
        owner->jumpToMarker(currentRow);
    }
}

// MarkersListBoxModel implementation
int MarkersListBoxModel::getNumRows()
{
    if (owner == nullptr)
        return 0;

    juce::String currentFileId = owner->getCurrentFileId();
    int count = 0;

    // Count markers for the current file
    for (const auto &marker : owner->getMarkers())
    {
        if (marker.fileId == currentFileId)
            count++;
    }

    return count;
}

void MarkersListBoxModel::paintListBoxItem(int /*rowNumber*/, juce::Graphics & /*g*/, int /*width*/, int /*height*/, bool /*rowIsSelected*/)
{
    // Custom components handle painting
}

juce::Component *MarkersListBoxModel::refreshComponentForRow(int rowNumber, bool /*isRowSelected*/, juce::Component *existingComponentToUpdate)
{
    if (owner == nullptr)
        return nullptr;

    juce::String currentFileId = owner->getCurrentFileId();
    const auto &markers = owner->getMarkers();
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

    MarkerRowComponent *markerRow = dynamic_cast<MarkerRowComponent *>(existingComponentToUpdate);

    if (markerRow == nullptr)
    {
        markerRow = new MarkerRowComponent(owner);
    }

    const auto &marker = markers[actualMarkerIndex];
    markerRow->updateRow(actualMarkerIndex, marker.label, owner->formatTime(marker.timestamp));

    return markerRow;
}

// WaveformComponent implementation
WaveformComponent::WaveformComponent(PlayerAudio *audio) : playerAudio(audio)
{
}

void WaveformComponent::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds();

    // Modern background with gradient
    juce::ColourGradient bgGradient(
        juce::Colour(0xFF1E2332), 0, 0,
        juce::Colour(0xFF252A3A), 0, (float)bounds.getHeight(), false);
    g.setGradientFill(bgGradient);
    g.fillRoundedRectangle(bounds.toFloat(), 6.0f);

    // Subtle border
    g.setColour(juce::Colour(0x40FFFFFF));
    g.drawRoundedRectangle(bounds.toFloat().reduced(0.5f), 6.0f, 1.0f);

    // Draw waveform
    if (playerAudio == nullptr)
        return;

    const auto &waveformData = playerAudio->getWaveformData();
    if (waveformData.empty())
    {
        // Draw placeholder text
        g.setColour(juce::Colour(0xFF8A8F9E));
        g.setFont(juce::FontOptions(14.0f, juce::Font::italic));
        g.drawText("No waveform data available", bounds, juce::Justification::centred);
        return;
    }

    const int width = bounds.getWidth();
    const int height = bounds.getHeight();
    const int centerY = height / 2;

    // Draw waveform
    juce::Path waveformPath;
    bool firstPoint = true;

    for (int i = 0; i < width; ++i)
    {
        float normalizedIndex = (float)i / (float)width;
        int dataIndex = static_cast<int>(normalizedIndex * waveformData.size());
        dataIndex = juce::jlimit(0, static_cast<int>(waveformData.size() - 1), dataIndex);

        float amplitude = waveformData[dataIndex];
        float normalizedAmplitude = juce::jlimit(0.0f, 1.0f, amplitude);

        // Scale amplitude to fit height (with some padding)
        float yPos = centerY - (normalizedAmplitude * centerY * 0.8f);

        if (firstPoint)
        {
            waveformPath.startNewSubPath(static_cast<float>(i), yPos);
            firstPoint = false;
        }
        else
        {
            waveformPath.lineTo(static_cast<float>(i), yPos);
        }
    }

    // Draw mirrored bottom half
    for (int i = width - 1; i >= 0; --i)
    {
        float normalizedIndex = (float)i / (float)width;
        int dataIndex = static_cast<int>(normalizedIndex * waveformData.size());
        dataIndex = juce::jlimit(0, static_cast<int>(waveformData.size() - 1), dataIndex);

        float amplitude = waveformData[dataIndex];
        float normalizedAmplitude = juce::jlimit(0.0f, 1.0f, amplitude);

        float yPos = centerY + (normalizedAmplitude * centerY * 0.8f);
        waveformPath.lineTo(static_cast<float>(i), yPos);
    }

    waveformPath.closeSubPath();

    // Modern waveform fill with gradient
    juce::ColourGradient waveformGradient(
        juce::Colour(0xFF5A9EF0), 0, centerY - 10,
        juce::Colour(0xFF4A90E2), 0, centerY + 10, false);
    g.setGradientFill(waveformGradient);
    g.fillPath(waveformPath);

    // Subtle waveform outline
    g.setColour(juce::Colour(0xFF6A9EF0).withAlpha(0.6f));
    g.strokePath(waveformPath, juce::PathStrokeType(1.5f));

    // Draw playback position indicator
    if (playerAudio != nullptr && playerAudio->getLengthInSeconds() > 0.0)
    {
        double currentPos = playerAudio->getPosition();
        double totalLength = playerAudio->getLengthInSeconds();

        if (totalLength > 0.0)
        {
            float normalizedPos = static_cast<float>(currentPos / totalLength);

            int playheadX = static_cast<int>(normalizedPos * width);
            playheadX = juce::jlimit(0, width - 1, playheadX);

            // Draw playhead line with shadow
            g.setColour(juce::Colour(0x40000000));
            g.drawLine(static_cast<float>(playheadX + 1), 0.0f,
                       static_cast<float>(playheadX + 1), static_cast<float>(height), 2.5f);

            g.setColour(juce::Colours::white);
            g.drawLine(static_cast<float>(playheadX), 0.0f,
                       static_cast<float>(playheadX), static_cast<float>(height), 2.0f);

            // Draw playhead indicator circle with glow
            g.setColour(juce::Colour(0x404A90E2));
            g.fillEllipse(static_cast<float>(playheadX - 7), static_cast<float>(height / 2 - 7),
                          14.0f, 14.0f);
            g.setColour(juce::Colour(0xFF4A90E2));
            g.fillEllipse(static_cast<float>(playheadX - 6), static_cast<float>(height / 2 - 6),
                          12.0f, 12.0f);
            g.setColour(juce::Colours::white);
            g.fillEllipse(static_cast<float>(playheadX - 4), static_cast<float>(height / 2 - 4),
                          8.0f, 8.0f);
        }
    }

    // Draw A-B loop markers if applicable
    if (playerAudio != nullptr && playerAudio->hasValidABLoop())
    {
        double pointA = playerAudio->getPointA();
        double pointB = playerAudio->getPointB();
        double totalLength = playerAudio->getLengthInSeconds();

        if (totalLength > 0.0)
        {
            int xA = static_cast<int>((pointA / totalLength) * width);
            int xB = static_cast<int>((pointB / totalLength) * width);

            // Draw point A marker
            g.setColour(juce::Colour(0xFF4A90E2));
            g.fillRect(xA - 3, 0, 6, height);

            // Draw point B marker
            g.setColour(juce::Colour(0xFFE74C3C));
            g.fillRect(xB - 3, 0, 6, height);
        }
    }
}

void WaveformComponent::resized()
{
    // Empty - layout handled by parent
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
    // Modern dark background with subtle gradient
    juce::ColourGradient backgroundGradient(
        juce::Colour(0xFF1A1F2E), 0, 0,
        juce::Colour(0xFF252A3A), 0, (float)getHeight(), false);
    g.setGradientFill(backgroundGradient);
    g.fillAll();

    // Header section with elegant gradient
    juce::Rectangle<int> headerArea(0, 0, getWidth(), 120);
    juce::ColourGradient headerGradient(
        juce::Colour(0xFF2A2F40), 0, 0,
        juce::Colour(0xFF1E2332), 0, 120.0f, false);
    g.setGradientFill(headerGradient);
    g.fillRoundedRectangle(headerArea.toFloat(), 0.0f);

    // Subtle shadow effect for header
    g.setColour(juce::Colour(0x40000000));
    g.fillRoundedRectangle(headerArea.toFloat().withTrimmedBottom(1.0f), 0.0f);

    // Elegant divider line
    g.setColour(juce::Colour(0xFF3A3F50).withAlpha(0.6f));
    g.drawLine(0, 120.5f, (float)getWidth(), 120.5f, 1.0f);

    // Subtle highlight above divider
    g.setColour(juce::Colour(0x50FFFFFF));
    g.drawLine(0, 119.5f, (float)getWidth(), 119.5f, 0.5f);

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
        g.setColour(juce::Colour(0x4027AE60));
        g.fillRect(loopRegion);

        g.setColour(juce::Colour(0x902ECC71));
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
        g.setColour(juce::Colour(0xFF4A90E2));
        g.fillPath(markerA);

        g.setColour(juce::Colour(0xFF4A90E2));
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

void PlayerGUI::drawTrackMarkers(juce::Graphics &g)
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

    for (const auto &marker : markers)
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

PlayerGUI::PlayerGUI() : markersListBoxModel(this), waveformComponent(&playerAudio)
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

    // Set waveform listener for async waveform updates
    playerAudio.setWaveformListener(this);

    playlistBox.setRowHeight(30);
    playlistBox.setColour(juce::ListBox::backgroundColourId, juce::Colour(0xFF1A1F2E));
    playlistBox.setColour(juce::ListBox::outlineColourId, juce::Colour(0xFF3A3F50));
    playlistBox.setModel(this);
    addAndMakeVisible(playlistBox);

    addFilesButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF27AE60));
    addFilesButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFF2ECC71));
    addFilesButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    addFilesButton.getProperties().set("fontSize", 12.0f);
    addAndMakeVisible(addFilesButton);
    addFilesButton.addListener(this);

    loadLast.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF8E44AD));
    loadLast.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFF9B59B6));
    loadLast.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    loadLast.getProperties().set("fontSize", 12.0f);
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
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 60, 22);
    volumeSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFE8E8E8));
    volumeSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(0xFF2A2F3E));
    volumeSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colour(0xFF3A3F50));
    volumeSlider.setColour(juce::Slider::trackColourId, juce::Colour(0xFF4A90E2));
    volumeSlider.setColour(juce::Slider::thumbColourId, juce::Colour(0xFF5A9EF0));
    volumeSlider.setColour(juce::Slider::backgroundColourId, juce::Colour(0xFF2A2F3E));
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    volumeLabel.setText("Volume: 1.00", juce::dontSendNotification);
    volumeLabel.setFont(juce::FontOptions(14.0f, juce::Font::bold));
    volumeLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFE8E8E8));
    volumeLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(volumeLabel);

    speedslider.setRange(0.25, 2.0, 0.25);
    speedslider.setValue(1.0);
    speedslider.setSliderStyle(juce::Slider::LinearHorizontal);
    speedslider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 60, 22);
    speedslider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFE8E8E8));
    speedslider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(0xFF2A2F3E));
    speedslider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colour(0xFF3A3F50));
    speedslider.setColour(juce::Slider::trackColourId, juce::Colour(0xFFE67E22));
    speedslider.setColour(juce::Slider::thumbColourId, juce::Colour(0xFFF39C12));
    speedslider.setColour(juce::Slider::backgroundColourId, juce::Colour(0xFF2A2F3E));
    speedslider.addListener(this);
    addAndMakeVisible(speedslider);

    speedLabel.setText("Speed: 1.00x", juce::dontSendNotification);
    speedLabel.setFont(juce::FontOptions(14.0f, juce::Font::bold));
    speedLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFE8E8E8));
    speedLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(speedLabel);

    positionSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    positionSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    positionSlider.setRange(0.0, 1.0, 0.001);
    positionSlider.setColour(juce::Slider::trackColourId, juce::Colour(0xFF4A90E2));
    positionSlider.setColour(juce::Slider::backgroundColourId, juce::Colour(0xFF2A2F3E));
    positionSlider.setColour(juce::Slider::thumbColourId, juce::Colour(0xFF5A9EF0));
    positionSlider.addListener(this);
    addAndMakeVisible(positionSlider);

    currentTimeLabel.setText("00:00", juce::dontSendNotification);
    currentTimeLabel.setJustificationType(juce::Justification::centredLeft);
    currentTimeLabel.setFont(juce::FontOptions(13.0f, juce::Font::bold));
    currentTimeLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFE8E8E8));
    addAndMakeVisible(currentTimeLabel);

    totalTimeLabel.setText("00:00", juce::dontSendNotification);
    totalTimeLabel.setJustificationType(juce::Justification::centredRight);
    totalTimeLabel.setFont(juce::FontOptions(13.0f, juce::Font::bold));
    totalTimeLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFE8E8E8));
    addAndMakeVisible(totalTimeLabel);

    metadataTitleLabel.setText("No file loaded", juce::dontSendNotification);
    metadataTitleLabel.setFont(juce::FontOptions(24.0f, juce::Font::bold));
    metadataTitleLabel.setJustificationType(juce::Justification::centred);
    metadataTitleLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFF5F5F5));
    metadataTitleLabel.setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(metadataTitleLabel);

    metadataArtistLabel.setText("", juce::dontSendNotification);
    metadataArtistLabel.setFont(juce::FontOptions(17.0f, juce::Font::plain));
    metadataArtistLabel.setJustificationType(juce::Justification::centred);
    metadataArtistLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFD8D8E8));
    metadataArtistLabel.setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(metadataArtistLabel);

    metadataAlbumLabel.setText("", juce::dontSendNotification);
    metadataAlbumLabel.setFont(juce::FontOptions(15.0f, juce::Font::italic));
    metadataAlbumLabel.setJustificationType(juce::Justification::centred);
    metadataAlbumLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFB8C0D0));
    metadataAlbumLabel.setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(metadataAlbumLabel);

    metadataInfoLabel.setText("", juce::dontSendNotification);
    metadataInfoLabel.setFont(juce::FontOptions(12.0f, juce::Font::plain));
    metadataInfoLabel.setJustificationType(juce::Justification::centred);
    metadataInfoLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF9A9FAE));
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
    setPointAButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF4A90E2));
    setPointAButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    setPointAButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFF5A9EF0));
    setPointAButton.getProperties().set("fontSize", 12.0f);
    addAndMakeVisible(setPointAButton);

    setPointBButton.addListener(this);
    setPointBButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE74C3C));
    setPointBButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    setPointBButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFFFF5555));
    setPointBButton.getProperties().set("fontSize", 12.0f);
    addAndMakeVisible(setPointBButton);

    clearABButton.addListener(this);
    clearABButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF7F8C8D));
    clearABButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    clearABButton.getProperties().set("fontSize", 12.0f);
    addAndMakeVisible(clearABButton);

    enableABLoopButton.addListener(this);
    enableABLoopButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF27AE60));
    enableABLoopButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    enableABLoopButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFF2ECC71));
    enableABLoopButton.getProperties().set("fontSize", 12.0f);
    addAndMakeVisible(enableABLoopButton);

    abLoopInfoLabel.setText("A-B Loop: Not set", juce::dontSendNotification);
    abLoopInfoLabel.setJustificationType(juce::Justification::centred);
    abLoopInfoLabel.setFont(juce::FontOptions(13.0f, juce::Font::bold));
    abLoopInfoLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFE8E8E8));
    abLoopInfoLabel.setColour(juce::Label::backgroundColourId, juce::Colour(0xFF2A2F3E));
    abLoopInfoLabel.setColour(juce::Label::outlineColourId, juce::Colour(0xFF3A3F50));
    addAndMakeVisible(abLoopInfoLabel);

    clearPlaylistButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE74C3C));
    clearPlaylistButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFFFF5555));
    clearPlaylistButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    clearPlaylistButton.getProperties().set("fontSize", 12.0f);
    addAndMakeVisible(clearPlaylistButton);
    clearPlaylistButton.addListener(this);

    unLoadTrack.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE67E22));
    unLoadTrack.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFFF39C12));
    unLoadTrack.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    unLoadTrack.getProperties().set("fontSize", 12.0f);
    addAndMakeVisible(unLoadTrack);
    unLoadTrack.addListener(this);

    addMarkerButton.addListener(this);
    addMarkerButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF9B59B6));
    addMarkerButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFF8E44AD));
    addMarkerButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    addMarkerButton.getProperties().set("fontSize", 12.0f);
    addAndMakeVisible(addMarkerButton);

    clearMarkersButton.addListener(this);
    clearMarkersButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF7F8C8D));
    clearMarkersButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    clearMarkersButton.getProperties().set("fontSize", 12.0f);
    addAndMakeVisible(clearMarkersButton);

    markersLabel.setText("Track Markers", juce::dontSendNotification);
    markersLabel.setFont(juce::FontOptions(15.0f, juce::Font::bold));
    markersLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFE8E8E8));
    markersLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(markersLabel);

    markersListBox.setRowHeight(28);
    markersListBox.setColour(juce::ListBox::backgroundColourId, juce::Colour(0xFF1A1F2E));
    markersListBox.setColour(juce::ListBox::outlineColourId, juce::Colour(0xFF3A3F50));
    markersListBox.setModel(&markersListBoxModel);
    addAndMakeVisible(markersListBox);

    // Reset marker counter for new session (markers will be loaded when restoring last session)
    markerCounter = 0;
    markers.clear();

    playlistLabel.setText("Playlist", juce::dontSendNotification);
    playlistLabel.setFont(juce::FontOptions(15.0f, juce::Font::bold));
    playlistLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFE8E8E8));
    playlistLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(playlistLabel);

    // Add waveform component
    addAndMakeVisible(waveformComponent);
}

void PlayerGUI::resized()
{
    int metadataY = 12;
    metadataTitleLabel.setBounds(20, metadataY, getWidth() - 40, 30);
    metadataArtistLabel.setBounds(20, metadataY + 35, getWidth() - 40, 26);
    metadataAlbumLabel.setBounds(20, metadataY + 63, getWidth() - 40, 22);
    metadataInfoLabel.setBounds(20, metadataY + 87, getWidth() - 40, 20);

    int y = 135;
    int buttonWidth = 70;
    int buttonHeight = 35;
    int spacing = 15;

    int numButtons = 10;
    int totalWidth = numButtons * buttonWidth + (numButtons - 1) * spacing;
    int startX = (getWidth() - totalWidth) / 2;

    loadButton.setBounds(startX + (buttonWidth + spacing) * 0, y, buttonWidth, buttonHeight);
    backwardButton.setBounds(startX + (buttonWidth + spacing) * 1, y, buttonWidth, buttonHeight);
    BeginButton.setBounds(startX + (buttonWidth + spacing) * 2, y, buttonWidth, buttonHeight);
    PlayButton.setBounds(startX + (buttonWidth + spacing) * 3, y, buttonWidth, buttonHeight);
    EndButton.setBounds(startX + (buttonWidth + spacing) * 4, y, buttonWidth, buttonHeight);
    forwardButton.setBounds(startX + (buttonWidth + spacing) * 5, y, buttonWidth, buttonHeight);
    LoopButton.setBounds(startX + (buttonWidth + spacing) * 6, y, buttonWidth, buttonHeight);
    restartButton.setBounds(startX + (buttonWidth + spacing) * 7, y, buttonWidth, buttonHeight);
    loadLast.setBounds(startX + (buttonWidth + spacing) * 8, y, buttonWidth, buttonHeight);
    unLoadTrack.setBounds(startX + (buttonWidth + spacing) * 9, y, buttonWidth, buttonHeight);

    int positionY = 195;
    currentTimeLabel.setBounds(20, positionY, 65, 22);
    totalTimeLabel.setBounds(getWidth() - 85, positionY, 65, 22);
    positionSlider.setBounds(90, positionY, getWidth() - 180, 22);

    // Position waveform directly under the progress bar
    int waveformY = positionY + 30;
    int waveformHeight = 70;
    waveformComponent.setBounds(90, waveformY, getWidth() - 180, waveformHeight);

    volumeSlider.setBounds(110, waveformY + waveformHeight + 15, getWidth() -250, 26);
    MuteButton.setBounds(50, waveformY + waveformHeight+9 , buttonWidth, buttonHeight);


    speedLabel.setBounds(20, waveformY + waveformHeight + 50, 85, 26);
    speedslider.setBounds(110, waveformY + waveformHeight + 50, getWidth() - 135, 26);

    int abLoopY = waveformY + waveformHeight + 85;
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
    playlistLabel.setBounds(625, markerY, 150, 25);
    addFilesButton.setBounds(700, markerY, 100,25 );
    clearPlaylistButton.setBounds(810, markerY,100 ,25 );
    int remainingHeight = getHeight() - (markerY + 35);
    int playlistandMarkerListHeight = static_cast<int>(remainingHeight * 0.6);

    playlistBox.setBounds(625, markerY + 35, 550, playlistandMarkerListHeight);
    markersListBox.setBounds(25, markerY + 35, 550, playlistandMarkerListHeight);
}

PlayerGUI::~PlayerGUI()
{
    stopTimer();
    savePropertiesFileState();

    // Clear waveform listener
    playerAudio.setWaveformListener(nullptr);
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
                        waveformComponent.repaint(); // Refresh waveform display
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
        currentPlayingIndex = findCurrentFileIndexInPlaylist();
        double currentPos = playerAudio.getPosition();

        if (currentPos <= 0.02 && currentPlayingIndex > 0 && playlistFiles.size() > 1)
        {
            playPreviousTrack();
        }
        else
        {
            playerAudio.setPosition(0.0);
            setPlayButtonState(true);
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
                for (auto &f : files)
                {
                    playlistFiles.addIfNotAlreadyThere(f);
                    double duration = calculateFileDuration(f);
                    trackTimes.addIfNotAlreadyThere(formatTime(duration));
                }

                playlistBox.updateContent();
                playlistBox.repaint();
            });
    }
    else if (button == &BeginButton)
    {
        currentPlayingIndex = findCurrentFileIndexInPlaylist();
        double currentPos = playerAudio.getPosition();

        if (currentPos <= 0.02 && currentPlayingIndex > 0 && playlistFiles.size() > 1)
        {
            playPreviousTrack();
        }
        else
        {
            playerAudio.setPosition(0.0);
            playerAudio.stop();
            setPlayButtonState(false);
        }
    }
    else if (button == &EndButton)
    {
        if (isLooping)
        {
            playerAudio.setPosition(0.0);
            playerAudio.start();
            setPlayButtonState(true);
        }
        else
        {
            playerAudio.setPosition(playerAudio.getLength() - 0.05);
            playerAudio.stop();
            setPlayButtonState(false);
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
                        double duration = calculateFileDuration(file);
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
                double duration = calculateFileDuration(file);
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
                    }
                    else
                    {
                        playerAudio.setGain((float)lastVolume);
                        volumeSlider.setValue(lastVolume, juce::dontSendNotification);
                        previousGain = (float)lastVolume;
                        volumeLabel.setText("Volume: " + juce::String(lastVolume, 2), juce::dontSendNotification);
                    }
                    setMuteButtonState(mutedState);

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
                        setPointAButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF5A9EF0));
                    }
                    else
                    {
                        setPointAButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF4A90E2));
                    }
                    
                    if (playerAudio.isPositionSetB())
                    {
                        setPointBButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFFF5555));
                    }
                    else
                    {
                        setPointBButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE74C3C));
                    }
                    
                    updateABLoopDisplay();
                    waveformComponent.repaint();
                    
                    // Load markers when restoring last session
                    loadMarkers();
                    
                    repaint();

                    updateMetadataDisplay(); });
            }
        }
    }
    else if (button == &PlayButton)
    {
        if (playerAudio.isPlaying())
        {
            playerAudio.stop();
            setPlayButtonState(false);
        }
        else
        {
            playerAudio.start();
            setPlayButtonState(true);
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
        }
        else
        {
            previousGain = (float)volumeSlider.getValue();
            playerAudio.setGain(0.0f);
            volumeSlider.setValue(0.0, juce::dontSendNotification);
            volumeLabel.setText("Volume: 0.00", juce::dontSendNotification);
            isMuted = true;
        }
        setMuteButtonState(isMuted);
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
            setPointAButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF4A90E2));
        }
        else
        {
            playerAudio.setPointA(playerAudio.getPosition());
            setPointAButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF5A9EF0));
        }
        updateABLoopDisplay();
        waveformComponent.repaint();
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
            setPointBButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFFF5555));
        }
        updateABLoopDisplay();
        waveformComponent.repaint();
        repaint();
    }
    else if (button == &clearABButton)
    {
        playerAudio.clearPositionA();
        playerAudio.clearPositionB();
        setPointAButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF4A90E2));
        setPointBButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE74C3C));
        updateABLoopDisplay();
        waveformComponent.repaint();
        repaint();
    }
    else if (button == &enableABLoopButton)
    {
        isABLoopEnabled = !isABLoopEnabled;
        playerAudio.setABLoopEnabled(isABLoopEnabled);
        enableABLoopButton.setToggleState(isABLoopEnabled, juce::dontSendNotification);
        updateABLoopDisplay();
        waveformComponent.repaint();
        repaint();
    }
    else if (button == &clearPlaylistButton)
    {
        playlistFiles.clear();
        trackTimes.clear();
        currentPlayingIndex = -1;
        playlistBox.updateContent();
        playlistBox.repaint();
        resetUIToEmptyState();
    }
    else if (button == &unLoadTrack)
    {
        currentPlayingIndex = -1;
        resetUIToEmptyState();
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
        if (v <= 0.001f)
        {
            isMuted = true;
            setMuteButtonState(true);
        }
        else
        {
            isMuted = false;
            setMuteButtonState(false);
		}
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

    // Repaint waveform to update playhead position
    waveformComponent.repaint();

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
        savePropertiesFileState();
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

void PlayerGUI::paintListBoxItem(int /*rowNumber*/, juce::Graphics & /*g*/,
                                 int /*width*/, int /*height*/, bool /*rowIsSelected*/)
{
    // This function is still called for fallback, but refreshComponentForRow will handle the rendering
    // with the custom component that includes the delete button
}

juce::Component *PlayerGUI::refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component *existingComponentToUpdate)
{
    // Handle playlist only (markers are handled by MarkersListBoxModel)
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
            setPlayButtonState(true);

            totalTimeLabel.setText(formatTime(playerAudio.getLengthInSeconds()), juce::dontSendNotification);
            currentTimeLabel.setText("00:00", juce::dontSendNotification);
            positionSlider.setValue(0.0, juce::dontSendNotification);
            updateMetadataDisplay();
            markersListBox.updateContent();
            markersListBox.repaint();
            waveformComponent.repaint(); // Refresh waveform when track changes
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
            enableABLoopButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF2ECC71));
        }
        else
        {
            enableABLoopButton.setButtonText("A-B Loop: OFF");
            enableABLoopButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF27AE60));
        }
    }
    else
    {
        abLoopInfoLabel.setText("A-B Loop: Not set", juce::dontSendNotification);
        enableABLoopButton.setButtonText("A-B Loop: OFF");
        enableABLoopButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF27AE60));
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
        setPlayButtonState(false);
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
                setPlayButtonState(false);
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
              [](const TrackMarker &a, const TrackMarker &b)
              {
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
        const auto &marker = markers[markerIndex];

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
            setPlayButtonState(true);
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
    for (const auto &marker : markers)
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

        for (const auto &line : markerLines)
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

//==============================================================================//
//                      Helper Method Implementations                           //
//==============================================================================//

int PlayerGUI::findCurrentFileIndexInPlaylist() const
{
    auto currentFile = playerAudio.getLastLoadedFile();
    if (!currentFile.existsAsFile() || playlistFiles.isEmpty())
        return -1;

    if (currentPlayingIndex >= 0 && currentPlayingIndex < playlistFiles.size())
    {
        if (playlistFiles[currentPlayingIndex] == currentFile)
            return currentPlayingIndex;
    }

    for (int i = 0; i < playlistFiles.size(); i++)
    {
        if (playlistFiles[i] == currentFile)
            return i;
    }

    return -1;
}

double PlayerGUI::calculateFileDuration(const juce::File &file) const
{
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));

    if (reader != nullptr)
        return reader->lengthInSamples / reader->sampleRate;

    return 0.0;
}

void PlayerGUI::setPlayButtonState(bool isPlaying)
{
    if (isPlaying)
    {
        PlayButton.setImages(false, true, true,
                             pauseimage, 1.0f, juce::Colours::transparentBlack,
                             pauseimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                             playimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
    }
    else
    {
        PlayButton.setImages(false, true, true,
                             playimage, 1.0f, juce::Colours::transparentBlack,
                             playimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                             pauseimage, 1.0f, juce::Colours::white.withAlpha(0.6f));
    }
}

void PlayerGUI::setMuteButtonState(bool muted)
{
    if (muted)
    {
        MuteButton.setImages(false, true, true,
                             mutedImage, 1.0f, juce::Colours::transparentBlack,
                             mutedImage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                             unmutedImage, 1.0f, juce::Colours::white.withAlpha(0.6f));
    }
    else
    {
        MuteButton.setImages(false, true, true,
                             unmutedImage, 1.0f, juce::Colours::transparentBlack,
                             unmutedImage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                             mutedImage, 1.0f, juce::Colours::white.withAlpha(0.6f));
    }
}

void PlayerGUI::resetUIToEmptyState()
{
    playerAudio.setPosition(0.0);
    playerAudio.stop();
    playerAudio.unloadFile();
    setPlayButtonState(false);
    unloadMetaData();
    positionSlider.setValue(0.0, juce::dontSendNotification);
    currentTimeLabel.setText("00:00", juce::dontSendNotification);
    totalTimeLabel.setText("00:00", juce::dontSendNotification);
}

void PlayerGUI::savePropertiesFileState()
{
    if (!propertiesFile)
        return;

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
        propertiesFile->setValue("abLoopPointA", playerAudio.getPointA());
    else
        propertiesFile->removeValue("abLoopPointA");

    if (playerAudio.isPositionSetB())
        propertiesFile->setValue("abLoopPointB", playerAudio.getPointB());
    else
        propertiesFile->removeValue("abLoopPointB");

    propertiesFile->setValue("abLoopEnabled", playerAudio.isABLoopEnabled());
    saveMarkers();
    propertiesFile->saveIfNeeded();
}

void PlayerGUI::waveformDataReady()
{
    // Repaint waveform component when waveform data is ready
    waveformComponent.repaint();
}