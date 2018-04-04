/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
VibratoPluginAudioProcessor::VibratoPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
                    parameters(*this, nullptr)
#endif
{
    CVibrato::createInstance(pCVibrato);
    NormalisableRange<float> frequencyRange(5.0f, 14.0f);
    parameters.createAndAddParameter("frequencySliderID", "frequencySlider", "frequencySlider", frequencyRange, 5.0f, nullptr, nullptr);
    
    NormalisableRange<float> widthRange(0.001f, 0.02f);
    parameters.createAndAddParameter("widthSliderID", "widthSlider", "widthSlider", widthRange, 0.001f, nullptr, nullptr);
    
    parameters.state = ValueTree("savedParams");
}

VibratoPluginAudioProcessor::~VibratoPluginAudioProcessor()
{
    CVibrato::destroyInstance(pCVibrato);
    pCVibrato = NULL;
}

//==============================================================================
const String VibratoPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VibratoPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VibratoPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VibratoPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VibratoPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VibratoPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VibratoPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VibratoPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String VibratoPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void VibratoPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void VibratoPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    pCVibrato->initInstance(fMaxDelayInSec, getSampleRate(), getTotalNumInputChannels());
    pCVibrato->setParam(CVibrato::VibratoParam_t::kParamModFreqInHz, fModFreq);
    pCVibrato->setParam(CVibrato::VibratoParam_t::kParamModWidthInS, fModWidth);
    
}

void VibratoPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VibratoPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void VibratoPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    //DBG(std::to_string(pCVibrato->getParam(CVibrato::kParamModFreqInHz)));
    auto **input = (float **)buffer.getArrayOfReadPointers();
    auto **output = buffer.getArrayOfWritePointers();
    if(!bypass)
        pCVibrato->process(input, output, buffer.getNumSamples());
}

//==============================================================================
bool VibratoPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VibratoPluginAudioProcessor::createEditor()
{
    return new VibratoPluginAudioProcessorEditor (*this);
}

void VibratoPluginAudioProcessor::setVibratoParameter (CVibrato::VibratoParam_t eParam, float fParamValue)
{
    pCVibrato->setParam(eParam, fParamValue);
}

void VibratoPluginAudioProcessor::setBypass(bool buttonState)
{
    bypass = buttonState;
}

bool VibratoPluginAudioProcessor::getBypass()
{
    return bypass;
}

//==============================================================================
void VibratoPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml (parameters.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void VibratoPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> savedParameters (getXmlFromBinary(data, sizeInBytes));
    
    if(savedParameters != nullptr)
    {
        if(savedParameters->hasTagName(parameters.state.getType()))
        {
            parameters.state = ValueTree::fromXml(*savedParameters);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VibratoPluginAudioProcessor();
}
