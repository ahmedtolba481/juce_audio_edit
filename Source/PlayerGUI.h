#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"

class PlayerGUI : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::Timer,
    public juce::ListBoxModel 
{
public:
    PlayerGUI();
    ~PlayerGUI() override;
    void resized() override;
    void paint(juce::Graphics& g) override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();
    void unloadMetaData();
    
    void timerCallback() override;
    
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics& g,
    int width, int height, bool rowIsSelected) override;
    void selectedRowsChanged(int lastRowSelected) override;
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
    // GUI elements

    juce::ListBox playlistBox;
    juce::TextButton addFilesButton{ "Add Files" };
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
    juce::TextButton loadLast{ "Load Last Session" };
    juce::TextButton clearPlaylistButton{ "Clear Playlist" };
    juce::TextButton deleteTrackButton{ "Delete Track" };
    juce::TextButton unLoadTrack{ "Unload Track" };
    // A-B Loop controls
    juce::TextButton setPointAButton{ "Set A" };
    juce::TextButton setPointBButton{ "Set B" };
    juce::TextButton clearABButton{ "Clear A-B" };
    juce::TextButton enableABLoopButton{ "A-B Loop: OFF" };
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
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
    
    juce::String formatTime(double timeInSeconds);
    void updatePositionSlider();
    void updateABLoopDisplay();
    void drawABLoopMarkers(juce::Graphics& g); // New method for drawing markers
    std::unique_ptr<juce::PropertiesFile> propertiesFile;
    
    void updateMetadataDisplay();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};
