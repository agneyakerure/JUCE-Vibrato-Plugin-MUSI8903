/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class VibratoPluginAudioProcessorEditor  : public AudioProcessorEditor,
                                           public Slider::Listener,
                                           public Button::Listener
{
public:
    VibratoPluginAudioProcessorEditor (VibratoPluginAudioProcessor&);
    ~VibratoPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider *slider) override;
    void buttonClicked(Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VibratoPluginAudioProcessor& processor;
    Slider frequencySlider, widthSlider;
    ToggleButton bypassButton;
    Label freqLabel, widthLabel;
    
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> frequencySliderAttach;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> widthSliderAttach;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibratoPluginAudioProcessorEditor)
};
