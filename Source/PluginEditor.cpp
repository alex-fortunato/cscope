#include "PluginEditor.h"
#include "PluginProcessor.h"
#include <JuceHeader.h>

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p), processorRef(p) {
  juce::ignoreUnused(processorRef);
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.

    // Initialize WevView
    //setupWebView(); // Moved to resized function
    addAndMakeVisible(webView);
    startTimer(30); // 30ms timer for sending audio data to JS

  setSize(400, 300);
  setResizable(true, true);
  setResizeLimits(400, 300, 2000, 1500);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
  stopTimer();
}

//==============================================================================
// void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
//   // (Our component is opaque, so we must completely fill the background with a
//   // solid colour)
//   // g.fillAll(
//   //     getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
//   //
//   // g.setColour(juce::Colours::white);
//   //
//   // g.setFont(15.0f);
//   //
//   // auto firstLineBounds = getLocalBounds().translated(0, -15);
//   // g.drawFittedText("Renata is pretty", firstLineBounds,
//   //                  juce::Justification::centred, 1);
//   //
// }

void AudioPluginAudioProcessorEditor::resized() {
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor..
  webView.setBounds(getLocalBounds());

  if (! hasLoadedPage) {
    setupWebView();
    hasLoadedPage = true;
  }

}

void AudioPluginAudioProcessorEditor::setupWebView()
{
  // 1) Make WebView fill our editor
  webView.setSize (getWidth(), getHeight());

  // 2) Pull HTML out of BinaryData
  auto html = juce::String::fromUTF8 (BinaryData::interface_html,
                                      BinaryData::interface_htmlSize);

  // 3) Write it to a temp file so WebKit can load it as file://
  auto tmpFile = juce::File::getSpecialLocation (juce::File::tempDirectory)
                     .getChildFile ("cscope_interface.html");

  // Overwrite each run
  tmpFile.replaceWithText (html, false, true, "\n");

  // 4) Build a proper file:// URL and load it
  juce::URL url (tmpFile);
  auto urlStr = url.toString (true);

  DBG ("[CScope] Loading embedded interface with URL: " << urlStr);
  webView.goToURL (urlStr);
}




void AudioPluginAudioProcessorEditor::timerCallback()
{
  sendAudioDataToJS();
}

void AudioPluginAudioProcessorEditor::sendAudioDataToJS()
{
  // Lock the processor's audio buffer while we read from it
  const juce::ScopedLock sl(processorRef.getAudioLock());
  juce::AudioBuffer<float>& buffer = processorRef.getAudioBuffer();

  // Prepare javascript arrays for left and right channels
  juce::var leftArray = juce::var(juce::Array<juce::var>());
  juce::var rightArray = juce::var(juce::Array<juce::var>());

  // Number of samples to send (downsample to improve performance)
  const int totalSamples = buffer.getNumSamples();
  const int samplesToSend = 1024;
  const int downsampleFactor = juce::jmax(1, totalSamples / samplesToSend);

  // Get channel pointers
  const float* leftChannel = buffer.getReadPointer(0);
  const float* rightChannel = buffer.getNumChannels() > 1 ? buffer.getReadPointer(1) : buffer.getReadPointer(0);

  // Copy samples into our javascript arrays
  for (int i = 0; i < totalSamples; i += downsampleFactor)
  {
    leftArray.append(leftChannel[i]);
    rightArray.append(rightChannel[i]);
  }

  // Build a JSON object { left: [...], right: [...] }
  juce::DynamicObject* jsonObj = new juce::DynamicObject();
  jsonObj->setProperty("left", leftArray);
  jsonObj->setProperty("right", rightArray);

  juce::var jsonVar(jsonObj);
  juce::String jsonStr = juce::JSON::toString(jsonVar);

  // Inject into the page for your JS to pick up
  // webView.executeJavaScript("updateOscilloscope(" + jsonStr + ");");
  juce::String script = "window.latestOscilloscopeData = " + jsonStr + ";";
  webView.evaluateJavascript (script);
}