#pragma once

#include "PluginProcessor.h"
#include <JuceHeader.h>


//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    // void paint (juce::Graphics&) override;
    void resized() override;

private:

    bool hasLoadedPage = false;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;

    juce::WebBrowserComponent webView;

    void sendAudioDataToJS();

    void setupWebView();
    void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
