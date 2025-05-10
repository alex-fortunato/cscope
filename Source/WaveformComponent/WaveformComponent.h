#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class WaveformComponent  : public juce::Component,
                           private juce::Timer
{
public:
    WaveformComponent (AudioPluginAudioProcessor& p);
    ~WaveformComponent() override = default;

    // ← DECLARATION only (no body, no class prefix)
    void paint (juce::Graphics& g) override;

private:
    void timerCallback() override;

    AudioPluginAudioProcessor& processor;
    std::vector<std::pair<float,float>> displayData;
};
