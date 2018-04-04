/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
VibratoPluginAudioProcessorEditor::VibratoPluginAudioProcessorEditor (VibratoPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (300, 200);
    
    frequencySliderAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "frequencySliderID", frequencySlider);
    widthSliderAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "widthSliderID", widthSlider);
    bypassButtonAttach = new AudioProcessorValueTreeState::ButtonAttachment(processor.parameters, "bypassButtonID", bypassButton);
    
    frequencySlider.setSliderStyle(Slider::SliderStyle::Rotary);
    frequencySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    frequencySlider.setRange(5, 14);
    frequencySlider.addListener(this);
    addAndMakeVisible(frequencySlider);
    
    widthSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    widthSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    widthSlider.setRange(0.001, 0.02);
    widthSlider.addListener(this);
    addAndMakeVisible(widthSlider);
    
    bypassButton.setButtonText ("Bypass");
    bypassButton.addListener(this);
    addAndMakeVisible(bypassButton);
}

VibratoPluginAudioProcessorEditor::~VibratoPluginAudioProcessorEditor()
{
    widthSlider.removeListener(this);
    frequencySlider.removeListener(this);
    bypassButton.removeListener(this);
}

//==============================================================================
void VibratoPluginAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Mod Freq", 30, 170, 100, 25, Justification::centred, 1);
    g.drawFittedText ("Mod Width", 170, 170, 100, 25, Justification::centred, 1);
    
}

void VibratoPluginAudioProcessorEditor::resized()
{
    frequencySlider.setBounds(-20,20,200,150);
    widthSlider.setBounds(120,20,200,150);
    bypassButton.setBounds(0,0,100,25);
    
}

void VibratoPluginAudioProcessorEditor::buttonClicked(Button* button)
{
    if (button == &bypassButton)
    {
        processor.setBypass(button->getToggleState());
    }
}

void VibratoPluginAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if(slider == &frequencySlider)
    {
        processor.setVibratoParameter(CVibrato::kParamModFreqInHz, (float)slider->getValue());
        processor.fModFreq = (float)slider->getValue();
    }
    
    if(slider == &widthSlider)
    {
        processor.setVibratoParameter(CVibrato::kParamModWidthInS, (float)slider->getValue());
        processor.fModWidth = (float)slider->getValue();
    }

}
