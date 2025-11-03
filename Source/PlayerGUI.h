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
    void setOtherPlayer1(PlayerGUI *other) { otherPlayer1 = other; }
    void setOtherPlayer2(PlayerGUI *other) { otherPlayer2 = other; }

private:
    juce::Rectangle<int> getDeleteButtonBounds() const;
    juce::Rectangle<int> getAddToMixer1ButtonBounds() const;
    juce::Rectangle<int> getAddToMixer2ButtonBounds() const;
    bool isClickOnDeleteButton(const juce::MouseEvent &event);
    bool isClickOnAddToMixer1Button(const juce::MouseEvent &event);
    bool isClickOnAddToMixer2Button(const juce::MouseEvent &event);
    PlayerGUI *owner;
    PlayerGUI *otherPlayer1 = nullptr;
    PlayerGUI *otherPlayer2 = nullptr;
    int currentRow = -1;
    juce::Label filenameLabel;
    juce::Label durationLabel;
    juce::TextButton deleteButton;
    juce::TextButton addToMixer1Button;
    juce::TextButton addToMixer2Button;
    juce::Colour backgroundColour = juce::Colour(0xFF2C3E50);
};

// Marker structure to store timestamp and label
struct TrackMarker
{
    double timestamp;    // Position in seconds
    juce::String label;  // Marker label
    juce::String fileId; // Associated file identifier to support multiple tracks

    TrackMarker(double time, const juce::String &markerLabel, const juce::String &file)
        : timestamp(time), label(markerLabel), fileId(file) {}
};

// Custom component for marker list rows
class MarkerRowComponent : public juce::Component,
                           public juce::Button::Listener
{
public:
    MarkerRowComponent(PlayerGUI *parent);
    void updateRow(int rowIndex, const juce::String &markerLabel, const juce::String &time);
    void resized() override;
    void paint(juce::Graphics &g) override;
    void buttonClicked(juce::Button *button) override;
    void mouseDown(const juce::MouseEvent &event) override;

private:
    juce::Rectangle<int> getDeleteButtonBounds() const;
    bool isClickOnDeleteButton(const juce::MouseEvent &event);
    PlayerGUI *owner;
    int currentRow = -1;
    juce::Label markerLabel;
    juce::Label timeLabel;
    juce::TextButton deleteButton;
    juce::Colour backgroundColour = juce::Colour(0xFF34495E);
};

// Forward declaration
class PlayerGUI;

// Waveform visualization component
class WaveformComponent : public juce::Component
{
public:
    WaveformComponent(PlayerAudio *audio);
    void paint(juce::Graphics &g) override;
    void resized() override;

private:
    PlayerAudio *playerAudio;
};

// Model for markers list box
class MarkersListBoxModel : public juce::ListBoxModel
{
public:
    MarkersListBoxModel(PlayerGUI *parent) : owner(parent) {}

    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected) override;
    juce::Component *refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component *existingComponentToUpdate) override;

private:
    PlayerGUI *owner;
};

class PlayerGUI : public juce::Component,
                  public juce::Button::Listener,
                  public juce::Slider::Listener,
                  public juce::Timer,
                  public juce::ListBoxModel,
                  public juce::DragAndDropTarget,
                  public PlayerAudio::WaveformListener
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
    void waveformDataReady() override;
    void rowsDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex);
    void deleteTrack(int index);
    void selectPlaylistRow(int rowIndex);
    int getPlaylistSize() const;
    void reorderPlaylistItems(int sourceIndex, int destinationIndex);

    // Methods for transferring tracks between players
    juce::File getFileAtIndex(int index) const;
    void addFileToPlaylist(const juce::File &file);
    void setOtherPlayer1(PlayerGUI *other);
    void setOtherPlayer2(PlayerGUI *other);

    // Shared playlist support
    void setSharedPlaylistSource(PlayerGUI *source);
    void loadAndPlayFile(const juce::File &file);
    juce::Array<juce::File> *getPlaylistFiles() { return &playlistFiles; }
    juce::StringArray *getTrackTimes() { return &trackTimes; }

    // Method to stop and clear player (for use when clearing playlist)
    void stopAndClearPlayer();

    // Method to get currently loaded file
    juce::File getCurrentLoadedFile() const { return playerAudio.getLastLoadedFile(); }

    // DragAndDropTarget methods
    bool isInterestedInDragSource(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override;
    void itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override;

    // Auto-play next track functionality
    void playNextTrack();
    void playPreviousTrack();

    // Marker functionality
    void addMarker();
    void jumpToMarker(int markerIndex);
    void deleteMarker(int markerIndex);
    int getMarkerCount() const { return static_cast<int>(markers.size()); }
    const TrackMarker &getMarker(int index) const { return markers[index]; }

private:
    PlayerAudio playerAudio;
    bool isMuted = false;
    bool isLooping = false;
    bool isPlaylistLooping = false;
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

    // Marker data
    std::vector<TrackMarker> markers;
    int markerCounter = 0;

    // References to other players for playlist sharing
    PlayerGUI *otherPlayer1 = nullptr;
    PlayerGUI *otherPlayer2 = nullptr;

    // Shared playlist source (if set, use this player's playlist instead of own)
    PlayerGUI *sharedPlaylistSource = nullptr;

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
    juce::ImageButton playlistLoopButton;
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

    // Marker controls
    juce::TextButton addMarkerButton{"Add Marker"};
    juce::TextButton clearMarkersButton{"Clear All Markers"};
    juce::ListBox markersListBox;
    juce::Label markersLabel;
    MarkersListBoxModel markersListBoxModel;

    juce::Slider volumeSlider;
    juce::Slider speedslider;
    juce::Label volumeLabel;
    juce::Label speedLabel;

    juce::Slider positionSlider;
    juce::Label currentTimeLabel;
    juce::Label totalTimeLabel;
    bool isDraggingSlider = false;

    // Waveform visualization
    WaveformComponent waveformComponent;

    juce::Label playlistLabel;

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
    void drawABLoopMarkers(juce::Graphics &g);
    void drawTrackMarkers(juce::Graphics &g);
    std::unique_ptr<juce::PropertiesFile> propertiesFile;

    juce::String getCurrentFileId() const;
    void loadMarkersForCurrentFile();
    void saveMarkers();
    void loadMarkers();

    void updateMetadataDisplay();

    // Helper methods
    int findCurrentFileIndexInPlaylist() const;
    double calculateFileDuration(const juce::File &file) const;
    void setPlayButtonState(bool isPlaying);
    void setMuteButtonState(bool muted);
    void resetUIToEmptyState();
    void savePropertiesFileState();

    // Friend access for MarkersListBoxModel
    friend class MarkersListBoxModel;
    const std::vector<TrackMarker> &getMarkers() const { return markers; }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};
