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

    deleteButton.setButtonText("Delete");
    deleteButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE74C3C));
    deleteButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFFFF5555));
    deleteButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    deleteButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    deleteButton.setColour(juce::ComboBox::outlineColourId, juce::Colour(0xFFFFFFFF).withAlpha(0.2f));
    deleteButton.getProperties().set("fontSize", 12.0f);
    deleteButton.setConnectedEdges(0);
    deleteButton.addListener(this);
    addAndMakeVisible(deleteButton);

    addToMixer1Button.setButtonText("Mixer 1");
    addToMixer1Button.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF4A90E2));
    addToMixer1Button.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFF5A9EF0));
    addToMixer1Button.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    addToMixer1Button.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    addToMixer1Button.setColour(juce::ComboBox::outlineColourId, juce::Colour(0xFFFFFFFF).withAlpha(0.2f));
    addToMixer1Button.getProperties().set("fontSize", 12.0f);
    addToMixer1Button.setConnectedEdges(0);
    addToMixer1Button.addListener(this);
    addAndMakeVisible(addToMixer1Button);

    addToMixer2Button.setButtonText("Mixer 2");
    addToMixer2Button.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFFE74C3C));
    addToMixer2Button.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFFFF5555));
    addToMixer2Button.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    addToMixer2Button.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    addToMixer2Button.setColour(juce::ComboBox::outlineColourId, juce::Colour(0xFFFFFFFF).withAlpha(0.2f));
    addToMixer2Button.getProperties().set("fontSize", 12.0f);
    addToMixer2Button.setConnectedEdges(0);
    addToMixer2Button.addListener(this);
    addAndMakeVisible(addToMixer2Button);
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
    int buttonWidth = 65;
    int spacing = 5;
    int totalButtonsWidth = buttonWidth * 3 + spacing * 2;

    filenameLabel.setBounds(10, 0, bounds.getWidth() - totalButtonsWidth - 80, bounds.getHeight());
    durationLabel.setBounds(bounds.getWidth() - totalButtonsWidth - 70, 0, 60, bounds.getHeight());

    int startX = bounds.getWidth() - totalButtonsWidth;
    addToMixer1Button.setBounds(startX, 2, buttonWidth, bounds.getHeight() - 4);
    addToMixer2Button.setBounds(startX + buttonWidth + spacing, 2, buttonWidth, bounds.getHeight() - 4);
    deleteButton.setBounds(startX + (buttonWidth + spacing) * 2, 2, buttonWidth, bounds.getHeight() - 4);
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
    else if (button == &addToMixer1Button && owner != nullptr && otherPlayer1 != nullptr)
    {
        juce::File file = owner->getFileAtIndex(currentRow);
        if (file.existsAsFile())
        {
            // Load and play the file on mixer 1 (player1)
            otherPlayer1->loadAndPlayFile(file);
        }
    }
    else if (button == &addToMixer2Button && owner != nullptr && otherPlayer2 != nullptr)
    {
        juce::File file = owner->getFileAtIndex(currentRow);
        if (file.existsAsFile())
        {
            // Load and play the file on mixer 2 (player2)
            otherPlayer2->loadAndPlayFile(file);
        }
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
    int buttonWidth = 65;
    int spacing = 5;
    int totalButtonsWidth = buttonWidth * 3 + spacing * 2;
    int startX = bounds.getWidth() - totalButtonsWidth;
    return juce::Rectangle<int>(startX + (buttonWidth + spacing) * 2, 2, buttonWidth, bounds.getHeight() - 4);
}

juce::Rectangle<int> PlaylistRowComponent::getAddToMixer1ButtonBounds() const
{
    auto bounds = getLocalBounds();
    int buttonWidth = 65;
    int spacing = 5;
    int totalButtonsWidth = buttonWidth * 3 + spacing * 2;
    int startX = bounds.getWidth() - totalButtonsWidth;
    return juce::Rectangle<int>(startX, 2, buttonWidth, bounds.getHeight() - 4);
}

juce::Rectangle<int> PlaylistRowComponent::getAddToMixer2ButtonBounds() const
{
    auto bounds = getLocalBounds();
    int buttonWidth = 65;
    int spacing = 5;
    int totalButtonsWidth = buttonWidth * 3 + spacing * 2;
    int startX = bounds.getWidth() - totalButtonsWidth;
    return juce::Rectangle<int>(startX + buttonWidth + spacing, 2, buttonWidth, bounds.getHeight() - 4);
}

bool PlaylistRowComponent::isClickOnDeleteButton(const juce::MouseEvent &event)
{
    auto localPos = event.getEventRelativeTo(this).position.toInt();
    return getDeleteButtonBounds().contains(localPos);
}

bool PlaylistRowComponent::isClickOnAddToMixer1Button(const juce::MouseEvent &event)
{
    auto localPos = event.getEventRelativeTo(this).position.toInt();
    return getAddToMixer1ButtonBounds().contains(localPos);
}

bool PlaylistRowComponent::isClickOnAddToMixer2Button(const juce::MouseEvent &event)
{
    auto localPos = event.getEventRelativeTo(this).position.toInt();
    return getAddToMixer2ButtonBounds().contains(localPos);
}

void PlaylistRowComponent::mouseDown(const juce::MouseEvent &event)
{
    if (isClickOnDeleteButton(event) || isClickOnAddToMixer1Button(event) || isClickOnAddToMixer2Button(event))
        return;

    Component::mouseDown(event);
}

void PlaylistRowComponent::mouseDoubleClick(const juce::MouseEvent &event)
{
    if (isClickOnDeleteButton(event) || isClickOnAddToMixer1Button(event) || isClickOnAddToMixer2Button(event))
        return;

    if (owner != nullptr && currentRow >= 0 && currentRow < owner->getPlaylistSize())
    {
        owner->selectPlaylistRow(currentRow);
    }
}

void PlaylistRowComponent::mouseDrag(const juce::MouseEvent &event)
{
    if (isClickOnDeleteButton(event) || isClickOnAddToMixer1Button(event) || isClickOnAddToMixer2Button(event))
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

    deleteButton.setButtonText("X");
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
    // Check if this is player2 (has shared playlist source)
    bool isPlayer2 = (sharedPlaylistSource != nullptr);

    // Modern dark background with subtle gradient
    // Player2 uses brighter colors
    juce::ColourGradient backgroundGradient(
        isPlayer2 ? juce::Colour(0xFF2A2F3E) : juce::Colour(0xFF1A1F2E), 0, 0,
        isPlayer2 ? juce::Colour(0xFF353A4A) : juce::Colour(0xFF252A3A), 0, (float)getHeight(), false);
    g.setGradientFill(backgroundGradient);
    g.fillAll();

    // Header section with elegant gradient
    // Player2 uses brighter header colors
    juce::Rectangle<int> headerArea(0, 0, getWidth(), 120);
    juce::ColourGradient headerGradient(
        isPlayer2 ? juce::Colour(0xFF3A3F50) : juce::Colour(0xFF2A2F40), 0, 0,
        isPlayer2 ? juce::Colour(0xFF2E3342) : juce::Colour(0xFF1E2332), 0, 120.0f, false);
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

    playlistLoopButton.setClickingTogglesState(true);
    playlistLoopButton.setImages(false, true, true,
                                 unloopimage, 1.0f, juce::Colours::transparentBlack,
                                 unloopimage, 0.5f, juce::Colours::white.withAlpha(0.3f),
                                 loopimage, 1.0f, juce::Colours::white.withAlpha(0.6f));

    addAndMakeVisible(playlistLoopButton);
    playlistLoopButton.addListener(this);

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
    isPlaylistLooping = propertiesFile->getBoolValue("playlistLooping", false);
    playlistLoopButton.setToggleState(isPlaylistLooping, juce::dontSendNotification);
    lastFile = juce::File(lastFilePath);

    // Load reverb and delay settings on startup
    bool savedReverbEnabled = propertiesFile->getBoolValue("reverbEnabled", false);
    double savedReverbWetLevel = propertiesFile->getDoubleValue("reverbWetLevel", 0.3);
    double savedReverbRoomSize = propertiesFile->getDoubleValue("reverbRoomSize", 0.5);

    reverbButton.setToggleState(savedReverbEnabled, juce::dontSendNotification);
    reverbSlider.setValue(savedReverbWetLevel, juce::dontSendNotification);
    reverbSlider.setEnabled(savedReverbEnabled);
    playerAudio.setReverbEnabled(savedReverbEnabled);
    playerAudio.setReverbWetLevel(static_cast<float>(savedReverbWetLevel));
    playerAudio.setReverbRoomSize(static_cast<float>(savedReverbRoomSize));

    bool savedDelayEnabled = propertiesFile->getBoolValue("delayEnabled", false);
    double savedDelayTime = propertiesFile->getDoubleValue("delayTime", 200.0);
    double savedDelayFeedback = propertiesFile->getDoubleValue("delayFeedback", 0.3);

    delayButton.setToggleState(savedDelayEnabled, juce::dontSendNotification);
    delaySlider.setValue(savedDelayTime, juce::dontSendNotification);
    delaySlider.setEnabled(savedDelayEnabled);
    playerAudio.setDelayEnabled(savedDelayEnabled);
    playerAudio.setDelayTime(static_cast<float>(savedDelayTime));
    playerAudio.setDelayFeedback(static_cast<float>(savedDelayFeedback));

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

    // Initialize Advanced Audio Processing - Effects Controls
    reverbButton.addListener(this);
    reverbButton.setClickingTogglesState(true);
    reverbButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF34495E));
    reverbButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFF9B59B6));
    reverbButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    reverbButton.getProperties().set("fontSize", 11.0f);
    addAndMakeVisible(reverbButton);

    reverbSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    reverbSlider.setRange(0.0, 1.0, 0.01);
    reverbSlider.setValue(0.3);
    reverbSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);
    reverbSlider.setColour(juce::Slider::trackColourId, juce::Colour(0xFF9B59B6));
    reverbSlider.setEnabled(false);
    reverbSlider.addListener(this);
    addAndMakeVisible(reverbSlider);

    delayButton.addListener(this);
    delayButton.setClickingTogglesState(true);
    delayButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xFF34495E));
    delayButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xFFF39C12));
    delayButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    delayButton.getProperties().set("fontSize", 11.0f);
    addAndMakeVisible(delayButton);

    delaySlider.setSliderStyle(juce::Slider::LinearHorizontal);
    delaySlider.setRange(0.0, 1000.0, 10.0);
    delaySlider.setValue(200.0);
    delaySlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 60, 20);
    delaySlider.setColour(juce::Slider::trackColourId, juce::Colour(0xFFF39C12));
    delaySlider.setEnabled(false);
    delaySlider.addListener(this);
    addAndMakeVisible(delaySlider);

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

    volumeSlider.setBounds(110, waveformY + waveformHeight + 15, getWidth() - 250, 26);
    MuteButton.setBounds(50, waveformY + waveformHeight + 9, buttonWidth, buttonHeight);

    speedLabel.setBounds(20, waveformY + waveformHeight + 50, 85, 26);
    speedslider.setBounds(110, waveformY + waveformHeight + 50, getWidth() - 135, 26);

    // Advanced Audio Processing - Effects Controls (below speed slider)
    int effectsY = waveformY + waveformHeight + 85;
    int effectsButtonWidth = 45;
    int effectsButtonHeight = 25;
    int effectsSliderWidth = 120;

    // Reverb
    reverbButton.setBounds(20, effectsY, effectsButtonWidth, effectsButtonHeight);
    reverbSlider.setBounds(20 + effectsButtonWidth + 5, effectsY, effectsSliderWidth, effectsButtonHeight);

    // Delay
    delayButton.setBounds(20 + effectsButtonWidth + effectsSliderWidth + 15, effectsY, effectsButtonWidth, effectsButtonHeight);
    delaySlider.setBounds(20 + effectsButtonWidth * 2 + effectsSliderWidth + 20, effectsY, effectsSliderWidth, effectsButtonHeight);

    int abLoopY = effectsY + effectsButtonHeight + 15;
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

    // Check if this player should show the playlist (only player1, not player2 with shared playlist)
    bool showPlaylist = (sharedPlaylistSource == nullptr);

    if (showPlaylist)
    {
        // Player1 layout: Playlist on left, Markers on right
        // Calculate spacing dynamically based on available width
        int totalWidth = getWidth();
        int playlistWidth = static_cast<int>(totalWidth * 0.55); // 55% for playlist
        int markersWidth = totalWidth - playlistWidth - 40;      // Remaining space minus margins
        int markersX = playlistWidth + 30;                       // Start after playlist with spacing

        // Ensure markers controls fit within available space
        int markersControlsWidth = markersWidth - 10; // Leave some margin

        // Playlist controls
        playlistLabel.setBounds(20, markerY, 75, 25);
        addFilesButton.setBounds(105, markerY, 90, 25);
        clearPlaylistButton.setBounds(200, markerY, 100, 25);
        playlistLoopButton.setBounds(305, markerY - 5, 120, 35);

        // Markers controls - positioned above markers box, ensure they fit
        int markerButtonWidth = juce::jmin(85, (markersControlsWidth - 130) / 2); // Distribute space evenly
        markersLabel.setBounds(markersX, markerY, 110, 25);
        addMarkerButton.setBounds(markersX + 115, markerY, markerButtonWidth, 25);
        clearMarkersButton.setBounds(markersX + 115 + markerButtonWidth + 5, markerY, markersControlsWidth - 115 - markerButtonWidth - 5, 25);

        // Show playlist elements
        playlistLabel.setVisible(true);
        addFilesButton.setVisible(true);
        clearPlaylistButton.setVisible(true);
        playlistLoopButton.setVisible(true);
        playlistBox.setVisible(true);

        int remainingHeight = getHeight() - (markerY + 35);
        int playlistandMarkerListHeight = static_cast<int>(remainingHeight * 0.6);

        // Position boxes with proper spacing
        playlistBox.setBounds(25, markerY + 35, playlistWidth - 30, playlistandMarkerListHeight);
        markersListBox.setBounds(markersX, markerY + 35, markersWidth, playlistandMarkerListHeight);
    }
    else
    {
        // Player2 layout: Only markers, centered and expanded
        // Space out label and buttons properly to avoid conflicts
        int spacing = 10;
        int labelWidth = 120;
        int buttonWidth = 100;

        markersLabel.setBounds(20, markerY, labelWidth, 25);
        addMarkerButton.setBounds(20 + labelWidth + spacing, markerY, buttonWidth, 25);
        clearMarkersButton.setBounds(20 + labelWidth + spacing + buttonWidth + spacing, markerY, 130, 25);

        // Hide playlist elements
        playlistLabel.setVisible(false);
        addFilesButton.setVisible(false);
        clearPlaylistButton.setVisible(false);
        playlistLoopButton.setVisible(false);
        playlistBox.setVisible(false);

        int remainingHeight = getHeight() - (markerY + 35);
        int markerListHeight = static_cast<int>(remainingHeight * 0.6);

        // Expand markers list to fill available space
        markersListBox.setBounds(20, markerY + 35, getWidth() - 40, markerListHeight);
    }
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
        juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &playlistFiles;

        if (currentPos <= 0.02 && currentPlayingIndex > 0 && files->size() > 1)
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
                juce::Array<juce::File> *playlistFiles = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &this->playlistFiles;
                juce::StringArray *trackTimes = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getTrackTimes() : &this->trackTimes;

                for (auto &f : files)
                {
                    playlistFiles->addIfNotAlreadyThere(f);
                    double duration = calculateFileDuration(f);
                    trackTimes->addIfNotAlreadyThere(formatTime(duration));
                }

                playlistBox.updateContent();
                playlistBox.repaint();

                // Update the other player's playlist box if it's also using the shared playlist
                if (sharedPlaylistSource != nullptr)
                {
                    if (otherPlayer1 != nullptr && otherPlayer1->sharedPlaylistSource == sharedPlaylistSource)
                    {
                        otherPlayer1->playlistBox.updateContent();
                        otherPlayer1->playlistBox.repaint();
                    }
                    if (otherPlayer2 != nullptr && otherPlayer2->sharedPlaylistSource == sharedPlaylistSource)
                    {
                        otherPlayer2->playlistBox.updateContent();
                        otherPlayer2->playlistBox.repaint();
                    }
                }
            });
    }
    else if (button == &BeginButton)
    {
        currentPlayingIndex = findCurrentFileIndexInPlaylist();
        double currentPos = playerAudio.getPosition();
        juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &playlistFiles;

        if (currentPos <= 0.02 && currentPlayingIndex > 0 && files->size() > 1)
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
            juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &playlistFiles;
            juce::StringArray *times = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getTrackTimes() : &trackTimes;

            files->clear();
            times->clear();

            juce::StringArray playlistPaths;
            playlistPaths.addTokens(savedPlaylist, "\n", "");

            for (auto &path : playlistPaths)
            {
                if (path.isNotEmpty())
                {
                    juce::File file(path);
                    if (file.existsAsFile())
                    {
                        files->add(file);
                        double duration = calculateFileDuration(file);
                        times->add(formatTime(duration));
                    }
                }
            }

            playlistBox.updateContent();
            playlistBox.repaint();

            // Update the other player's playlist box if it's also using the shared playlist
            if (sharedPlaylistSource != nullptr)
            {
                if (otherPlayer1 != nullptr && otherPlayer1->sharedPlaylistSource == sharedPlaylistSource)
                {
                    otherPlayer1->playlistBox.updateContent();
                    otherPlayer1->playlistBox.repaint();
                }
                if (otherPlayer2 != nullptr && otherPlayer2->sharedPlaylistSource == sharedPlaylistSource)
                {
                    otherPlayer2->playlistBox.updateContent();
                    otherPlayer2->playlistBox.repaint();
                }
            }
        }

        juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &playlistFiles;
        juce::StringArray *times = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getTrackTimes() : &trackTimes;

        auto savedTrackTimes = propertiesFile->getValue("trackTimes");
        if (!savedTrackTimes.isEmpty() && files->size() > 0 && times->size() < files->size())
        {
            times->clear();
            juce::StringArray timeStrings;
            timeStrings.addTokens(savedTrackTimes, "\n", "");
            for (auto &time : timeStrings)
            {
                if (time.isNotEmpty())
                    times->add(time);
            }

            while (times->size() < files->size())
            {
                int index = times->size();
                juce::File file = (*files)[index];
                double duration = calculateFileDuration(file);
                times->add(formatTime(duration));
            }
        }

        auto savedIndex = propertiesFile->getIntValue("currentPlayingIndex", -1);
        auto lastPath = propertiesFile->getValue("lastFilePath");

        if (!lastPath.isEmpty())
        {
            lastFile = juce::File(lastPath);

            if (lastFile.existsAsFile())
            {
                if (savedIndex >= 0 && savedIndex < files->size() && (*files)[savedIndex] == lastFile)
                {
                    currentPlayingIndex = savedIndex;
                }
                else
                {
                    for (int i = 0; i < files->size(); i++)
                    {
                        if ((*files)[i] == lastFile)
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
                    
                    // Restore reverb settings
                    bool savedReverbEnabled = propertiesFile->getBoolValue("reverbEnabled", false);
                    double savedReverbWetLevel = propertiesFile->getDoubleValue("reverbWetLevel", 0.3);
                    double savedReverbRoomSize = propertiesFile->getDoubleValue("reverbRoomSize", 0.5);
                    
                    reverbButton.setToggleState(savedReverbEnabled, juce::dontSendNotification);
                    reverbSlider.setValue(savedReverbWetLevel, juce::dontSendNotification);
                    reverbSlider.setEnabled(savedReverbEnabled);
                    playerAudio.setReverbEnabled(savedReverbEnabled);
                    playerAudio.setReverbWetLevel(static_cast<float>(savedReverbWetLevel));
                    playerAudio.setReverbRoomSize(static_cast<float>(savedReverbRoomSize));
                    
                    // Restore delay settings
                    bool savedDelayEnabled = propertiesFile->getBoolValue("delayEnabled", false);
                    double savedDelayTime = propertiesFile->getDoubleValue("delayTime", 200.0);
                    double savedDelayFeedback = propertiesFile->getDoubleValue("delayFeedback", 0.3);
                    
                    delayButton.setToggleState(savedDelayEnabled, juce::dontSendNotification);
                    delaySlider.setValue(savedDelayTime, juce::dontSendNotification);
                    delaySlider.setEnabled(savedDelayEnabled);
                    playerAudio.setDelayEnabled(savedDelayEnabled);
                    playerAudio.setDelayTime(static_cast<float>(savedDelayTime));
                    playerAudio.setDelayFeedback(static_cast<float>(savedDelayFeedback));
                    
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
    else if (button == &playlistLoopButton)
    {
        isPlaylistLooping = playlistLoopButton.getToggleState();
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
        juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &playlistFiles;
        juce::StringArray *times = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getTrackTimes() : &trackTimes;

        files->clear();
        times->clear();
        currentPlayingIndex = -1;

        // Stop and clear track from this player
        resetUIToEmptyState();

        // Stop and clear tracks from both other players
        if (otherPlayer1 != nullptr)
        {
            otherPlayer1->stopAndClearPlayer();
        }
        if (otherPlayer2 != nullptr)
        {
            otherPlayer2->stopAndClearPlayer();
        }

        playlistBox.updateContent();
        playlistBox.repaint();

        // Update the other player's playlist box if it's also using the shared playlist
        if (sharedPlaylistSource != nullptr)
        {
            if (otherPlayer1 != nullptr && otherPlayer1->sharedPlaylistSource == sharedPlaylistSource)
            {
                otherPlayer1->playlistBox.updateContent();
                otherPlayer1->playlistBox.repaint();
            }
            if (otherPlayer2 != nullptr && otherPlayer2->sharedPlaylistSource == sharedPlaylistSource)
            {
                otherPlayer2->playlistBox.updateContent();
                otherPlayer2->playlistBox.repaint();
            }
        }
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
    else if (button == &reverbButton)
    {
        bool enabled = reverbButton.getToggleState();
        playerAudio.setReverbEnabled(enabled);
        reverbSlider.setEnabled(enabled);
    }
    else if (button == &delayButton)
    {
        bool enabled = delayButton.getToggleState();
        playerAudio.setDelayEnabled(enabled);
        delaySlider.setEnabled(enabled);
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
    else if (slider == &reverbSlider)
    {
        float wetLevel = (float)slider->getValue();
        playerAudio.setReverbWetLevel(wetLevel);
        playerAudio.setReverbRoomSize(0.5f + wetLevel * 0.5f); // Room size based on wet level
    }
    else if (slider == &delaySlider)
    {
        float delayMs = (float)slider->getValue();
        playerAudio.setDelayTime(delayMs);
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
    if (sharedPlaylistSource != nullptr)
    {
        return sharedPlaylistSource->getPlaylistFiles()->size();
    }
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
    juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &playlistFiles;
    juce::StringArray *times = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getTrackTimes() : &trackTimes;

    if (rowNumber >= files->size())
        return nullptr;

    PlaylistRowComponent *rowComponent = dynamic_cast<PlaylistRowComponent *>(existingComponentToUpdate);

    if (rowComponent == nullptr)
    {
        rowComponent = new PlaylistRowComponent(this);
        rowComponent->setInterceptsMouseClicks(true, true);
    }

    // Set other players if available
    if (otherPlayer1 != nullptr)
        rowComponent->setOtherPlayer1(otherPlayer1);
    if (otherPlayer2 != nullptr)
        rowComponent->setOtherPlayer2(otherPlayer2);

    auto filename = (*files)[rowNumber].getFileNameWithoutExtension();
    auto fileDuration = (*times)[rowNumber];
    rowComponent->updateRow(rowNumber, filename, fileDuration, isRowSelected);

    return rowComponent;
}

int PlayerGUI::getPlaylistSize() const
{
    if (sharedPlaylistSource != nullptr)
    {
        return sharedPlaylistSource->getPlaylistFiles()->size();
    }
    return playlistFiles.size();
}

juce::File PlayerGUI::getFileAtIndex(int index) const
{
    juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : const_cast<juce::Array<juce::File> *>(&playlistFiles);
    if (index >= 0 && index < files->size())
    {
        return (*files)[index];
    }
    return juce::File();
}

void PlayerGUI::addFileToPlaylist(const juce::File &file)
{
    if (file.existsAsFile())
    {
        // Add to shared playlist if available, otherwise to own playlist
        juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &playlistFiles;
        juce::StringArray *times = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getTrackTimes() : &trackTimes;

        files->addIfNotAlreadyThere(file);
        double duration = calculateFileDuration(file);
        times->addIfNotAlreadyThere(formatTime(duration));

        playlistBox.updateContent();
        playlistBox.repaint();

        // Update the other player's playlist box if it's also using the shared playlist
        if (sharedPlaylistSource != nullptr && otherPlayer1 != nullptr && otherPlayer1->sharedPlaylistSource == sharedPlaylistSource)
        {
            otherPlayer1->playlistBox.updateContent();
            otherPlayer1->playlistBox.repaint();
        }
        if (sharedPlaylistSource != nullptr && otherPlayer2 != nullptr && otherPlayer2->sharedPlaylistSource == sharedPlaylistSource)
        {
            otherPlayer2->playlistBox.updateContent();
            otherPlayer2->playlistBox.repaint();
        }
    }
}

void PlayerGUI::setOtherPlayer1(PlayerGUI *other)
{
    otherPlayer1 = other;
    // Update all playlist row components to have the new reference
    playlistBox.updateContent();
}

void PlayerGUI::setOtherPlayer2(PlayerGUI *other)
{
    otherPlayer2 = other;
    // Update all playlist row components to have the new reference
    playlistBox.updateContent();
}

void PlayerGUI::setSharedPlaylistSource(PlayerGUI *source)
{
    sharedPlaylistSource = source;
    // Update playlist display when shared source changes
    playlistBox.updateContent();
    playlistBox.repaint();

    // Trigger layout update to show/hide playlist elements
    resized();
}

void PlayerGUI::loadAndPlayFile(const juce::File &file)
{
    if (!file.existsAsFile())
        return;

    // Stop current playback
    if (playerAudio.isPlaying())
    {
        playerAudio.stop();
    }

    // Load and play the file
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
        waveformComponent.repaint();

        // Update current playing index
        juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &playlistFiles;
        for (int i = 0; i < files->size(); i++)
        {
            if ((*files)[i] == file)
            {
                currentPlayingIndex = i;
                break;
            }
        }
    }
}

void PlayerGUI::stopAndClearPlayer()
{
    playerAudio.stop();
    playerAudio.unloadFile();
    setPlayButtonState(false);
    currentPlayingIndex = -1;
    resetUIToEmptyState();
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
    juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &playlistFiles;

    if (sourceIndex < 0 || sourceIndex >= files->size())
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
    juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &playlistFiles;

    if (sourceIndex < 0 || sourceIndex >= files->size() || insertIndex < 0)
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
    if (destinationIndex > files->size())
        destinationIndex = files->size();

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
    juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &playlistFiles;
    juce::StringArray *times = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getTrackTimes() : &trackTimes;

    if (sourceIndex < 0 || sourceIndex >= files->size() ||
        destinationIndex < 0 || destinationIndex > files->size())
        return;

    if (sourceIndex == destinationIndex)
        return;

    juce::File movedFile = (*files)[sourceIndex];
    juce::String movedTime = (*times)[sourceIndex];

    files->remove(sourceIndex);
    times->remove(sourceIndex);

    int adjustedDestination = juce::jlimit(0, files->size(), destinationIndex);

    files->insert(adjustedDestination, movedFile);
    times->insert(adjustedDestination, movedTime);

    // Update both players' playlist boxes if using shared playlist
    playlistBox.updateContent();
    playlistBox.repaint();
    if (sharedPlaylistSource != nullptr)
    {
        if (otherPlayer1 != nullptr && otherPlayer1->sharedPlaylistSource == sharedPlaylistSource)
        {
            otherPlayer1->playlistBox.updateContent();
            otherPlayer1->playlistBox.repaint();
        }
        if (otherPlayer2 != nullptr && otherPlayer2->sharedPlaylistSource == sharedPlaylistSource)
        {
            otherPlayer2->playlistBox.updateContent();
            otherPlayer2->playlistBox.repaint();
        }
    }
}

void PlayerGUI::selectPlaylistRow(int rowIndex)
{
    juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &playlistFiles;
    if (rowIndex >= 0 && rowIndex < files->size())
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

    juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &playlistFiles;

    if (lastRowSelected >= 0 && lastRowSelected < files->size())
    {
        auto file = (*files)[lastRowSelected];

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
    juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &playlistFiles;

    if (currentPlayingIndex < 0 || files->size() == 0)
        return;

    int nextIndex = currentPlayingIndex + 1;

    if (nextIndex < files->size())
    {
        selectPlaylistRow(nextIndex);
    }
    else
    {
        if (isPlaylistLooping && files->size() > 0)
        {
            // Loop back to the beginning of the playlist
            selectPlaylistRow(0);
        }
        else
        {
            playerAudio.stop();
            setPlayButtonState(false);
            currentPlayingIndex = -1;
        }
    }
}

void PlayerGUI::playPreviousTrack()
{
    juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &playlistFiles;

    if (currentPlayingIndex <= 0 || files->size() == 0)
        return;

    int previousIndex = currentPlayingIndex - 1;

    if (previousIndex >= 0)
    {
        selectPlaylistRow(previousIndex);
    }
}

void PlayerGUI::deleteTrack(int index)
{
    juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : &playlistFiles;
    juce::StringArray *times = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getTrackTimes() : &trackTimes;

    if (index >= 0 && index < files->size())
    {
        auto fileToDelete = (*files)[index];
        bool wasCurrentlyPlaying = (currentPlayingIndex == index);

        files->remove(index);
        times->remove(index);

        // Update both players' playlist boxes if using shared playlist
        playlistBox.updateContent();
        playlistBox.repaint();
        if (sharedPlaylistSource != nullptr)
        {
            if (otherPlayer1 != nullptr && otherPlayer1->sharedPlaylistSource == sharedPlaylistSource)
            {
                otherPlayer1->playlistBox.updateContent();
                otherPlayer1->playlistBox.repaint();
            }
            if (otherPlayer2 != nullptr && otherPlayer2->sharedPlaylistSource == sharedPlaylistSource)
            {
                otherPlayer2->playlistBox.updateContent();
                otherPlayer2->playlistBox.repaint();
            }
        }

        // Check if the deleted file is currently playing in other players and unload it
        if (otherPlayer1 != nullptr)
        {
            auto player1CurrentFile = otherPlayer1->getCurrentLoadedFile();
            if (player1CurrentFile == fileToDelete)
            {
                otherPlayer1->stopAndClearPlayer();
            }
        }

        if (otherPlayer2 != nullptr)
        {
            auto player2CurrentFile = otherPlayer2->getCurrentLoadedFile();
            if (player2CurrentFile == fileToDelete)
            {
                otherPlayer2->stopAndClearPlayer();
            }
        }

        if (wasCurrentlyPlaying)
        {
            if (index < currentPlayingIndex)
            {
                currentPlayingIndex--;
            }

            playerAudio.setPosition(0.0);
            playerAudio.stop();
            playerAudio.unloadFile();

            if (files->size() > 0)
            {
                if (index < files->size())
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
    juce::Array<juce::File> *files = sharedPlaylistSource != nullptr ? sharedPlaylistSource->getPlaylistFiles() : const_cast<juce::Array<juce::File> *>(&playlistFiles);

    if (!currentFile.existsAsFile() || files->isEmpty())
        return -1;

    if (currentPlayingIndex >= 0 && currentPlayingIndex < files->size())
    {
        if ((*files)[currentPlayingIndex] == currentFile)
            return currentPlayingIndex;
    }

    for (int i = 0; i < files->size(); i++)
    {
        if ((*files)[i] == currentFile)
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
    propertiesFile->setValue("playlistLooping", isPlaylistLooping);

    // Save reverb settings
    propertiesFile->setValue("reverbEnabled", reverbButton.getToggleState());
    propertiesFile->setValue("reverbWetLevel", reverbSlider.getValue());
    propertiesFile->setValue("reverbRoomSize", playerAudio.getReverbRoomSize());

    // Save delay settings
    propertiesFile->setValue("delayEnabled", delayButton.getToggleState());
    propertiesFile->setValue("delayTime", delaySlider.getValue());
    propertiesFile->setValue("delayFeedback", playerAudio.getDelayFeedback());

    saveMarkers();
    propertiesFile->saveIfNeeded();
}

void PlayerGUI::waveformDataReady()
{
    // Repaint waveform component when waveform data is ready
    waveformComponent.repaint();
}