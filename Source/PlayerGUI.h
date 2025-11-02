#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"

// Forward declaration for PlaylistRowComponent
class PlayerGUI;

// Custom component for playlist row with delete button
class PlaylistRowComponent : public juce::Component,
                             public juce::Button::Listener
{
public:
    PlaylistRowComponent(PlayerGUI *parent);
    void updateRow(int rowIndex, const juce::String &filename, const juce::String &duration, bool isSelected);
    void resized() override;
    void paint(juce::Graphics &g) override;
    void buttonClicked(juce::Button *button) override;
    void mouseDown(const juce::MouseEvent &event) override;
    void mouseDrag(const juce::MouseEvent &event) override;
    void mouseDoubleClick(const juce::MouseEvent &event) override;
    void setBackgroundColour(juce::Colour colour);

private:
    PlayerGUI *owner;
    int currentRow = -1;
    juce::Label filenameLabel;
    juce::Label durationLabel;
    juce::TextButton deleteButton;
    juce::Colour backgroundColour = juce::Colour(0xFF2C3E50);
};

class PlayerGUI : public juce::Component,
                  public juce::Button::Listener,
                  public juce::Slider::Listener,
                  public juce::Timer,
                  public juce::ListBoxModel,
                  public juce::DragAndDropTarget
{
public:
    PlayerGUI();
    ~PlayerGUI() override;
    void resized() override;
    void paint(juce::Graphics &g) override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill);
    void releaseResources();
    void unloadMetaData();

    void timerCallback() override;
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected) override;
    juce::Component *refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component *existingComponentToUpdate) override;
    void selectedRowsChanged(int lastRowSelected) override;
    juce::var getDragSourceDescription(const juce::SparseSet<int> &selectedRows) override;
    void rowsDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex);
    void deleteTrack(int index);
    void selectPlaylistRow(int rowIndex);
    int getPlaylistSize() const;
    void reorderPlaylistItems(int sourceIndex, int destinationIndex);

    // DragAndDropTarget methods
    bool isInterestedInDragSource(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override;
    void itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override;

    // Auto-play next track functionality
    void playNextTrack();
    void playPreviousTrack();

private:
    PlayerAudio playerAudio;
    bool isMuted = false;
    bool isLooping = false;
    bool isABLoopEnabled = false;
    float previousGain = 0.4f;

    juce::File lastFile;
    double lastPosition = 0.0;
    double lastVolume = 0.5;
    double lastSpeed = 1.0;
    juce::String lastFullTime;
    bool mutedState = false;
    juce::Array<juce::File> playlistFiles;
    juce::StringArray trackTimes;
    int currentPlayingIndex = -1;      // Track the currently playing track index in playlist
    bool isReorderingPlaylist = false; // Flag to prevent auto-play during drag and drop
    // GUI elements
    juce::ListBox playlistBox;
    juce::TextButton addFilesButton{"Add Files"};
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
    juce::TextButton loadLast{"Load Last Session"};
    juce::TextButton clearPlaylistButton{"Clear Playlist"};
    juce::TextButton deleteTrackButton{"Delete Track"};
    juce::TextButton unLoadTrack{"Unload Track"};
    // A-B Loop controls
    juce::TextButton setPointAButton{"Set A"};
    juce::TextButton setPointBButton{"Set B"};
    juce::TextButton clearABButton{"Clear A-B"};
    juce::TextButton enableABLoopButton{"A-B Loop: OFF"};
    juce::Label abLoopInfoLabel;

    juce::Slider volumeSlider;
    juce::Slider speedslider;
    juce::Label volumeLabel;
    juce::Label speedLabel;

    juce::Slider positionSlider;
    juce::Label currentTimeLabel;
    juce::Label totalTimeLabel;
    bool isDraggingSlider = false;

    // Metadata display labels
    juce::Label metadataTitleLabel;
    juce::Label metadataArtistLabel;
    juce::Label metadataAlbumLabel;
    juce::Label metadataInfoLabel;

    std::unique_ptr<juce::FileChooser> fileChooser;

    // Event handlers
    void buttonClicked(juce::Button *button) override;
    void sliderValueChanged(juce::Slider *slider) override;
    juce::String formatTime(double timeInSeconds);
    void updatePositionSlider();
    void updateABLoopDisplay();
    void drawABLoopMarkers(juce::Graphics &g); // New method for drawing markers
    std::unique_ptr<juce::PropertiesFile> propertiesFile;

    void updateMetadataDisplay();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};
