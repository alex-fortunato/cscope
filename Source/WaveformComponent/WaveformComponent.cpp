#include "WaveformComponent.h"

WaveformComponent::WaveformComponent (AudioPluginAudioProcessor& p)
    : processor (p)
{
    startTimerHz (24);  // repaint at 24 Hz
}

void WaveformComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    juce::Path waveformPath;
    waveformPath.preallocateSpace (displayData.size());

    for (size_t i = 0; i < displayData.size(); ++i)
    {
        float x = juce::jmap (displayData[i].first,
                              -1.0f, 1.0f,
                              bounds.getX(), bounds.getRight());
        float y = juce::jmap (displayData[i].second,
                              -1.0f, 1.0f,
                              bounds.getBottom(), bounds.getY());

        if (i == 0)
            waveformPath.startNewSubPath (x, y);
        else
            waveformPath.lineTo (x, y);
    }

    g.setColour (juce::Colours::white);
    g.strokePath (waveformPath, { 1.0f });
}

void WaveformComponent::timerCallback()
{
    // copy & down-sample under lock
    const juce::ScopedLock sl (processor.getAudioLock());
    auto& buf    = processor.getAudioBuffer();
    int   total  = buf.getNumSamples();
    int   target = 256;
    int   step   = juce::jmax (1, total / target);

    displayData.clear();
    displayData.reserve (total / step + 1);

    auto* L = buf.getReadPointer (0);
    auto* R = buf.getNumChannels() > 1 ? buf.getReadPointer (1) : L;

    for (int i = 0; i < total; i += step)
        displayData.emplace_back (L[i], R[i]);

    repaint();
}
