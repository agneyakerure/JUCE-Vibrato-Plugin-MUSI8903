/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Vibrato.h"


//==============================================================================
/**
*/
class VibratoPluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    VibratoPluginAudioProcessor();
    ~VibratoPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //Error_t setParam (VibratoParam_t eParam, float fParamValue);
    void setVibratoParameter (CVibrato::VibratoParam_t eParam, float fParamValue);
    void setBypass(bool buttonState);
    bool getBypass();
    AudioProcessorValueTreeState parameters;
    float fModWidth = 0.001f;
    float fModFreq  = 5; //5-14Hz
    
private:
    CVibrato *pCVibrato = 0;
    
    float fMaxDelayInSec = 1;
    bool bypass = false;
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibratoPluginAudioProcessor)
};
