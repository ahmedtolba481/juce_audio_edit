# JUCE Audio Player - Dual Deck DJ Application

A professional dual-deck audio player application built with JUCE framework, designed for DJ mixing and audio playback with advanced features.

## Features

### 🎵 Dual Player System
- **Two Independent Players**: Side-by-side player interface for seamless mixing
- **Shared Playlist**: Single playlist shared between both players for easy track management
- **Mixer Controls**: Horizontal volume sliders (0-10) for each track with discrete step increments

### 🎛️ Advanced Audio Processing
- **Reverb Effect**: Toggle reverb with adjustable wet level (0-100%)
- **Delay Effect**: Toggle delay with adjustable delay time (0-1000ms) and feedback control
- **Real-time Processing**: All effects applied in real-time during playback

### 📋 Playlist Management
- **Drag & Drop**: Add files by dragging them into the playlist
- **Custom Playlist UI**: Each playlist item shows filename, duration, and control buttons
- **Mixer Buttons**: "Mixer 1" and "Mixer 2" buttons to load tracks directly to respective players
- **Delete Tracks**: Remove tracks from playlist with automatic unloading from players
- **Playlist Loop**: Enable/disable playlist looping
- **Clear Playlist**: Clear all tracks and stop both players

### 🎯 Audio Playback Controls
- **Play/Pause**: Standard playback control
- **Seek**: Click on waveform or use position slider to jump to any position
- **Speed Control**: Adjust playback speed (0.5x - 2.0x)
- **Volume Control**: Adjust volume with mute functionality
- **Skip Forward/Backward**: Navigate through tracks
- **Begin/End**: Jump to start or end of track
- **Restart**: Restart current track

### 🔁 A-B Loop Functionality
- **Set Point A**: Mark the start of a loop
- **Set Point B**: Mark the end of a loop
- **Enable Loop**: Toggle A-B loop on/off
- **Clear Loop**: Remove A-B loop points
- **Visual Indicators**: See loop points on the waveform

### 📍 Track Markers
- **Add Markers**: Add custom markers at any point in the track with labels
- **Jump to Markers**: Click on markers to jump to that position
- **Delete Markers**: Remove individual markers
- **Persistent Storage**: Markers are saved per file and restored on load

### 📊 Waveform Visualization
- **Real-time Display**: Visual waveform representation of the loaded audio
- **Playhead Indicator**: Shows current playback position
- **Interactive Seeking**: Click on waveform to jump to position
- **A-B Loop Visualization**: Visual indicators for loop points

### 💾 Session Management
- **Load Last Session**: Restore previous session state for both players independently
- **Auto-save**: Settings automatically saved when changed
- **Independent Sessions**: Each player maintains its own session data:
  - Currently loaded file and position
  - Volume, speed, and mute state
  - A-B loop settings
  - Reverb and delay effect settings
  - Playlist state
  - Track markers

### 🎨 User Interface
- **Modern Design**: Clean, professional interface with gradient backgrounds
- **Player Identification**: Clear labels for Player 1 and Player 2
- **Visual Separation**: Visible separator line between players
- **Color-coded Controls**: Different colors for each player for easy identification
- **Responsive Layout**: Adaptive layout that adjusts to window size

## Requirements

### Build Requirements
- **JUCE Framework** (version 6.x or later)
- **C++17** compatible compiler
- **CMake** (if using CMake build system)
- **TagLib** library for metadata extraction

### Platform Support
- Windows (tested on Windows 10/11)
- macOS (with proper JUCE configuration)
- Linux (with proper JUCE configuration)

## Building the Project

### Using Projucer (JUCE's Project Manager)
1. Open `juce_audio_edit.jucer` in Projucer
2. Configure your IDE/exporter settings
3. Save and open the project in your IDE
4. Build the project

### Using CMake
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage

### Loading Audio Files
1. **Add Files**: Click "Add Files" button or drag files into the playlist
2. **Load to Player**: Click "Mixer 1" or "Mixer 2" buttons next to a track in the playlist
3. **Direct Load**: Click the "Load" button to browse and load a file directly

### Mixing Tracks
1. Load different tracks to Player 1 and Player 2
2. Use the mixer sliders at the bottom to control volume (0-10 scale)
3. Adjust effects (Reverb/Delay) on each player independently
4. Use playback controls to synchronize tracks

### Using Effects
- **Reverb**: Click "Rev" button to enable, adjust slider for wet level
- **Delay**: Click "Delay" button to enable, adjust slider for delay time
- Effects are applied in real-time and persist with session save/load

### A-B Looping
1. Play the track to the desired start point
2. Click "Set Point A" button
3. Continue playing to the desired end point
4. Click "Set Point B" button
5. Click "Enable A-B Loop" to activate looping
6. Click "Clear" to remove loop points

### Adding Markers
1. Play or seek to desired position
2. Click "Add Marker" button
3. Enter a label for the marker
4. Marker appears in the markers list
5. Click on any marker to jump to that position

### Saving/Loading Sessions
- **Auto-save**: Settings are automatically saved when changed
- **Load Last Session**: Click "Load Last Session" button to restore:
  - Last loaded file and playback position
  - Volume, speed, and mute settings
  - A-B loop points
  - Reverb and delay settings
  - Playlist contents
  - Track markers

## Project Structure

```
Source/
├── MainComponent.h/cpp      - Main application component with dual player setup
├── PlayerGUI.h/cpp          - Individual player GUI and controls
├── PlayerAudio.h/cpp        - Audio playback engine and effects processing
└── [Other JUCE generated files]
```

### Key Components

- **MainComponent**: Manages both players and mixer controls
- **PlayerGUI**: Individual player interface with all controls
- **PlayerAudio**: Core audio processing engine with effects

## Technical Details

### Audio Processing
- **Sample Rate**: Supports standard audio sample rates (44.1kHz, 48kHz, etc.)
- **Effects Processing**: Uses JUCE DSP module for high-quality audio effects
- **Mixing**: Real-time audio mixing with independent volume control per track

### File Format Support
- MP3, WAV, FLAC, OGG, and other formats supported by JUCE's AudioFormatManager
- Metadata extraction using TagLib library

### Session Storage
- Session data stored in platform-specific application data directory
- Separate properties files for each player:
  - `Player1_settings`: Player 1 session data
  - `Player2_settings`: Player 2 session data

## Keyboard Shortcuts
(Note: Keyboard shortcuts may vary based on implementation)
- Space: Play/Pause
- Left/Right Arrows: Seek backward/forward
- Up/Down Arrows: Volume up/down

## Troubleshooting

### Audio Not Playing
- Check audio device settings in system preferences
- Ensure audio files are in supported formats
- Verify file paths are accessible

### Session Not Loading
- Check application data directory permissions
- Verify properties files exist in correct location
- Check for file path changes if files were moved

### Effects Not Working
- Ensure audio is playing (effects only process during playback)
- Check that effects are enabled via toggle buttons
- Verify slider values are set correctly

## License

[Specify your license here]

## Credits

Built with JUCE Framework
Audio effects powered by JUCE DSP module
Metadata extraction using TagLib

## Version History

### Version 1.0
- Initial release with dual player support
- Basic playback controls
- Playlist management
- A-B loop functionality
- Waveform visualization
- Track markers
- Reverb and Delay effects
- Session save/load functionality

