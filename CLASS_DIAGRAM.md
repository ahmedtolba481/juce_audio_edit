# Class Diagram - JUCE Audio Player

## UML Class Diagram

```mermaid
classDiagram
    class MainComponent {
        -PlayerGUI player1
        -PlayerGUI player2
        -Slider track1VolumeSlider
        -Slider track2VolumeSlider
        -Label track1VolumeLabel
        -Label track2VolumeLabel
        -Label mixerTitleLabel
        -Label player1Label
        -Label player2Label
        -AudioBuffer tempBuffer
        +MainComponent()
        +~MainComponent()
        +prepareToPlay(int, double)
        +getNextAudioBlock(AudioSourceChannelInfo)
        +releaseResources()
        +resized()
        +paint(Graphics)
        +sliderValueChanged(Slider*)
    }

    class PlayerGUI {
        -PlayerAudio playerAudio
        -bool isMuted
        -bool isLooping
        -bool isPlaylistLooping
        -bool isABLoopEnabled
        -float previousGain
        -File lastFile
        -double lastPosition
        -double lastVolume
        -double lastSpeed
        -String lastFullTime
        -bool mutedState
        -Array~File~ playlistFiles
        -StringArray trackTimes
        -int currentPlayingIndex
        -bool isReorderingPlaylist
        -vector~TrackMarker~ markers
        -int markerCounter
        -PlayerGUI* otherPlayer1
        -PlayerGUI* otherPlayer2
        -PlayerGUI* sharedPlaylistSource
        -ListBox playlistBox
        -TextButton addFilesButton
        -ImageButton loadButton
        -ImageButton PlayButton
        -ImageButton restartButton
        -ImageButton BeginButton
        -ImageButton EndButton
        -ImageButton MuteButton
        -ImageButton LoopButton
        -ImageButton playlistLoopButton
        -ImageButton forwardButton
        -ImageButton backwardButton
        -TextButton loadLast
        -TextButton clearPlaylistButton
        -TextButton setPointAButton
        -TextButton setPointBButton
        -TextButton clearABButton
        -TextButton enableABLoopButton
        -TextButton addMarkerButton
        -TextButton clearMarkersButton
        -TextButton reverbButton
        -TextButton delayButton
        -ListBox markersListBox
        -Slider volumeSlider
        -Slider speedslider
        -Slider positionSlider
        -Slider reverbSlider
        -Slider delaySlider
        -WaveformComponent waveformComponent
        -unique_ptr~PropertiesFile~ propertiesFile
        +PlayerGUI(String playerName)
        +~PlayerGUI()
        +prepareToPlay(int, double)
        +getNextAudioBlock(AudioSourceChannelInfo)
        +releaseResources()
        +resized()
        +paint(Graphics)
        +timerCallback()
        +getNumRows() int
        +paintListBoxItem(int, Graphics, int, int, bool)
        +refreshComponentForRow(int, bool, Component*) Component*
        +selectedRowsChanged(int)
        +getDragSourceDescription(SparseSet) var
        +waveformDataReady()
        +rowsDropped(DragAndDropTarget::SourceDetails, int)
        +deleteTrack(int)
        +selectPlaylistRow(int)
        +getPlaylistSize() int
        +reorderPlaylistItems(int, int)
        +getFileAtIndex(int) File
        +addFileToPlaylist(File)
        +setOtherPlayer1(PlayerGUI*)
        +setOtherPlayer2(PlayerGUI*)
        +setSharedPlaylistSource(PlayerGUI*)
        +loadAndPlayFile(File)
        +getPlaylistFiles() Array~File~*
        +getTrackTimes() StringArray*
        +stopAndClearPlayer()
        +getCurrentLoadedFile() File
        +isInterestedInDragSource(DragAndDropTarget::SourceDetails) bool
        +itemDropped(DragAndDropTarget::SourceDetails)
        +playNextTrack()
        +playPreviousTrack()
        +addMarker()
        +jumpToMarker(int)
        +deleteMarker(int)
        +getMarkerCount() int
        +getMarker(int) TrackMarker
        +buttonClicked(Button*)
        +sliderValueChanged(Slider*)
        -formatTime(double) String
        -updatePositionSlider()
        -updateABLoopDisplay()
        -drawABLoopMarkers(Graphics)
        -drawTrackMarkers(Graphics)
        -getCurrentFileId() String
        -loadMarkersForCurrentFile()
        -saveMarkers()
        -loadMarkers()
        -updateMetadataDisplay()
        -findCurrentFileIndexInPlaylist() int
        -calculateFileDuration(File) double
        -setPlayButtonState(bool)
        -setMuteButtonState(bool)
        -resetUIToEmptyState()
        -savePropertiesFileState()
        -getMarkers() vector~TrackMarker~*
    }

    class PlayerAudio {
        -AudioFormatManager formatManager
        -unique_ptr~AudioFormatReaderSource~ readerSource
        -ResamplingAudioSource resampler
        -AudioTransportSource transportSource
        -bool isLooping
        -bool abLoopEnabled
        -double pointA
        -double pointB
        -File lastLoadedFile
        -float lastVolume
        -float lastSpeed
        -AudioMetadata metadata
        -vector~float~ waveformData
        -unique_ptr~WaveformGeneratorThread~ waveformThread
        -CriticalSection waveformDataLock
        -WaveformListener* waveformListener
        -dsp::Reverb reverb
        -dsp::Reverb::Parameters reverbParams
        -bool reverbEnabled
        -float reverbRoomSize
        -float reverbWetLevel
        -bool delayEnabled
        -float delayTimeMs
        -float delayFeedback
        -AudioBuffer delayBuffer
        -int delayBufferSize
        -int delayWritePosition
        -double currentSampleRate
        +PlayerAudio()
        +~PlayerAudio()
        +prepareToPlay(int, double)
        +getNextAudioBlock(AudioSourceChannelInfo)
        +releaseResources()
        +loadFile(File) bool
        +start()
        +stop()
        +setGain(float)
        +setPosition(double)
        +getPosition() double
        +getLength() double
        +isPlaying() bool
        +setLooping(bool)
        +getLengthInSeconds() double
        +setSpeed(float)
        +formatTime(double) String
        +updatePositionSlider()
        +getMetadata() AudioMetadata
        +getLastLoadedFile() File
        +setABLoopEnabled(bool)
        +isABLoopEnabled() bool
        +setPointA(double)
        +setPointB(double)
        +clearABLoop()
        +getPointA() double
        +getPointB() double
        +hasValidABLoop() bool
        +isPositionSetA() bool
        +isPositionSetB() bool
        +clearPositionA()
        +clearPositionB()
        +unloadFile()
        +getWaveformData() vector~float~
        +generateWaveform(File)
        +setWaveformListener(WaveformListener*)
        +generateWaveformAsync(File)
        +isWaveformGenerating() bool
        +setReverbEnabled(bool)
        +setReverbRoomSize(float)
        +setReverbWetLevel(float)
        +getReverbRoomSize() float
        +setDelayEnabled(bool)
        +setDelayTime(float)
        +setDelayFeedback(float)
        +getDelayFeedback() float
        -checkABLoop()
        -extractMetadata(File)
        -convertTagLibString(TagLib::String) String
        -processEffects(AudioBuffer)
        -setWaveformData(vector~float~)
        -stopWaveformGeneration()
    }

    class AudioMetadata {
        +String title
        +String artist
        +String album
        +String year
        +String genre
        +int duration
        +int bitrate
        +int sampleRate
        +int channels
        +bool hasMetadata
        +String filename
    }

    class TrackMarker {
        +double timestamp
        +String label
        +String fileId
        +TrackMarker(double, String, String)
    }

    class PlaylistRowComponent {
        -PlayerGUI* owner
        -PlayerGUI* otherPlayer1
        -PlayerGUI* otherPlayer2
        -int currentRow
        -Label filenameLabel
        -Label durationLabel
        -TextButton deleteButton
        -TextButton addToMixer1Button
        -TextButton addToMixer2Button
        -Colour backgroundColour
        +PlaylistRowComponent(PlayerGUI*)
        +updateRow(int, String, String, bool)
        +resized()
        +paint(Graphics)
        +buttonClicked(Button*)
        +mouseDown(MouseEvent)
        +mouseDrag(MouseEvent)
        +mouseDoubleClick(MouseEvent)
        +setBackgroundColour(Colour)
        +setOtherPlayer1(PlayerGUI*)
        +setOtherPlayer2(PlayerGUI*)
        -getDeleteButtonBounds() Rectangle
        -getAddToMixer1ButtonBounds() Rectangle
        -getAddToMixer2ButtonBounds() Rectangle
        -isClickOnDeleteButton(MouseEvent) bool
        -isClickOnAddToMixer1Button(MouseEvent) bool
        -isClickOnAddToMixer2Button(MouseEvent) bool
    }

    class MarkerRowComponent {
        -PlayerGUI* owner
        -int currentRow
        -Label markerLabel
        -Label timeLabel
        -TextButton deleteButton
        -Colour backgroundColour
        +MarkerRowComponent(PlayerGUI*)
        +updateRow(int, String, String)
        +resized()
        +paint(Graphics)
        +buttonClicked(Button*)
        +mouseDown(MouseEvent)
        -getDeleteButtonBounds() Rectangle
        -isClickOnDeleteButton(MouseEvent) bool
    }

    class WaveformComponent {
        -PlayerAudio* playerAudio
        +WaveformComponent(PlayerAudio*)
        +paint(Graphics)
        +resized()
    }

    class MarkersListBoxModel {
        -PlayerGUI* owner
        +MarkersListBoxModel(PlayerGUI*)
        +getNumRows() int
        +paintListBoxItem(int, Graphics, int, int, bool)
        +refreshComponentForRow(int, bool, Component*) Component*
    }

    class WaveformGeneratorThread {
        <<inner class>>
    }

    class WaveformListener {
        <<interface>>
        +waveformDataReady()
    }

    %% Inheritance Relationships
    MainComponent --|> AudioAppComponent
    MainComponent --|> DragAndDropContainer
    MainComponent --|> Slider::Listener

    PlayerGUI --|> Component
    PlayerGUI --|> Button::Listener
    PlayerGUI --|> Slider::Listener
    PlayerGUI --|> Timer
    PlayerGUI --|> ListBoxModel
    PlayerGUI --|> DragAndDropTarget
    PlayerGUI --|> WaveformListener

    PlaylistRowComponent --|> Component
    PlaylistRowComponent --|> Button::Listener

    MarkerRowComponent --|> Component
    MarkerRowComponent --|> Button::Listener

    WaveformComponent --|> Component

    MarkersListBoxModel --|> ListBoxModel

    WaveformGeneratorThread --|> Thread

    %% Composition Relationships (has-a)
    MainComponent *-- PlayerGUI : "contains 2"
    PlayerGUI *-- PlayerAudio : "contains 1"
    PlayerGUI *-- WaveformComponent : "contains 1"
    PlayerGUI *-- MarkersListBoxModel : "contains 1"
    PlayerAudio *-- AudioMetadata : "contains 1"
    PlayerGUI *-- TrackMarker : "contains many"

    %% Aggregation Relationships (references)
    PlayerGUI --> PlayerGUI : "otherPlayer1, otherPlayer2, sharedPlaylistSource"
    PlaylistRowComponent --> PlayerGUI : "owner, otherPlayer1, otherPlayer2"
    MarkerRowComponent --> PlayerGUI : "owner"
    MarkersListBoxModel --> PlayerGUI : "owner"
    WaveformComponent --> PlayerAudio : "playerAudio"
    PlayerAudio --> WaveformListener : "waveformListener"

    %% Notes
    note for MainComponent "Manages dual player setup\nand mixer controls"
    note for PlayerGUI "Main player interface with\nall controls and UI elements"
    note for PlayerAudio "Core audio engine with\nplayback and effects processing"
    note for PlayerGUI "Players can reference each other\nfor playlist sharing"
```

## Class Relationships Summary

### Inheritance Hierarchy

- **MainComponent** inherits from:

  - `juce::AudioAppComponent` (audio processing)
  - `juce::DragAndDropContainer` (drag and drop support)
  - `juce::Slider::Listener` (slider event handling)

- **PlayerGUI** inherits from:
  - `juce::Component` (UI component)
  - `juce::Button::Listener` (button events)
  - `juce::Slider::Listener` (slider events)
  - `juce::Timer` (timed updates)
  - `juce::ListBoxModel` (playlist model)
  - `juce::DragAndDropTarget` (drag and drop target)
  - `PlayerAudio::WaveformListener` (waveform updates)

### Composition Relationships

- **MainComponent** contains 2 `PlayerGUI` instances (player1, player2)
- **PlayerGUI** contains 1 `PlayerAudio` instance (core audio engine)
- **PlayerGUI** contains 1 `WaveformComponent` (waveform visualization)
- **PlayerGUI** contains 1 `MarkersListBoxModel` (markers list model)
- **PlayerGUI** contains multiple `TrackMarker` instances
- **PlayerAudio** contains 1 `AudioMetadata` instance

### Aggregation Relationships

- **PlayerGUI** references other `PlayerGUI` instances:

  - `otherPlayer1`: Reference to first other player
  - `otherPlayer2`: Reference to second other player
  - `sharedPlaylistSource`: Reference to player with shared playlist

- **PlaylistRowComponent** references `PlayerGUI` (owner)
- **MarkerRowComponent** references `PlayerGUI` (owner)
- **MarkersListBoxModel** references `PlayerGUI` (owner)
- **WaveformComponent** references `PlayerAudio` (playerAudio)
- **PlayerAudio** references `WaveformListener` (waveformListener)

## Key Design Patterns

1. **Model-View-Controller (MVC)**:

   - `PlayerAudio` (Model) - Audio processing logic
   - `PlayerGUI` (View/Controller) - UI and user interaction

2. **Observer Pattern**:

   - `WaveformListener` interface for waveform updates
   - `Timer` callback for periodic updates

3. **Composition Pattern**:

   - MainComponent aggregates multiple PlayerGUI instances
   - PlayerGUI aggregates PlayerAudio and various UI components

4. **Factory Pattern**:
   - `refreshComponentForRow()` creates PlaylistRowComponent instances dynamically

## Notes

- **PlayerGUI** instances can reference each other to support shared playlists and cross-player operations
- **TrackMarker** is a simple struct used to store marker data
- **AudioMetadata** is a struct containing extracted audio file metadata
- Inner classes like `WaveformGeneratorThread` are used for background processing
