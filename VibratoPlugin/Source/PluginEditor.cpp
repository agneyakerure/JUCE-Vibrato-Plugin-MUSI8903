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
    setSize (600, 400);
    
    frequencySlider.setSliderStyle(Slider::SliderStyle::Rotary);
    frequencySlider.setValue(5);
    frequencySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    frequencySlider.setRange(5, 14);
    frequencySlider.addListener(this);
    addAndMakeVisible(frequencySlider);
    
    setSize (400, 300);
    widthSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    widthSlider.setValue(0.001);
    widthSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    widthSlider.setRange(0.001, 0.02);
    widthSlider.addListener(this);
    addAndMakeVisible(frequencySlider);
    
    widthSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    widthSlider.setValue(0.001);
    widthSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    widthSlider.setRange(0.001, 0.02);
    widthSlider.addListener(this);
    addAndMakeVisible(widthSlider);
    
    setSize (600, 110);
    addAndMakeVisible (bypassButton);
    bypassButton.setButtonText ("Bypass");
    
    
    
}

VibratoPluginAudioProcessorEditor::~VibratoPluginAudioProcessorEditor()
{
}

//==============================================================================
void VibratoPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour (Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
    
}

void VibratoPluginAudioProcessorEditor::resized()
<<<<<<< HEAD
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    frequencySlider.setBounds(getLocalBounds());
    widthSlider.setBounds(getLocalBounds());
=======
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    const int border = 20;
    const int dialWidth = getWidth()/2 - border;
    const int dialHeight = getHeight()/2 - border;
    
    frequencySlider.setBounds(border, border, dialWidth, dialHeight);
    widthSlider.setBounds((getWidth() / 2), border, dialWidth, dialHeight);
>>>>>>> d07aba527b831d67450f531526b00354d7bda539
}

void buttonClicked (Button* button)
{
    
}

void VibratoPluginAudioProcessorEditor::sliderValueChanged(Slider *slider){
    if(slider == &frequencySlider)
    {
        //DBG(std::to_string(pCVibrato->getParam(CVibrato::kParamModFreqInHz)));
        //DBG(std::to_string(frequencySlider.getValue()));
        processor.setVibratoParameter(CVibrato::kParamModFreqInHz, (float)slider->getValue());
    }
    
    if(slider == &widthSlider)
    {
        //DBG(std::to_string(pCVibrato->getParam(CVibrato::kParamModFreqInHz)));
        //DBG(std::to_string(frequencySlider.getValue()));
        processor.setVibratoParameter(CVibrato::kParamModWidthInS, (float)slider->getValue());
    }
    
}
