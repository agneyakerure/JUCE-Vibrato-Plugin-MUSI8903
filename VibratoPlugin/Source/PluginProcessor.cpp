/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Vibrato.h"


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
                       )
#endif
{
    CVibrato::createInstance(pCVibrato);
    //iNumberOfFrames = samplesPerBlock;
    pCVibrato->initInstance(fMaxDelayInSec*getSampleRate(), getSampleRate(), getTotalNumInputChannels());
}

VibratoPluginAudioProcessor::~VibratoPluginAudioProcessor()
{
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
    
    //Error_t initInstance (float fMaxModWidthInS, float fSampleRateInHz, int iNumChannels);
    
    int iNumChannels = getTotalNumInputChannels();
    pCVibrato->setParam(CVibrato::VibratoParam_t::kParamModFreqInHz, fModFreq);
    pCVibrato->setParam(CVibrato::VibratoParam_t::kParamModWidthInS, fModWidth);
    
    ppfInputBuffer = new float*[iNumChannels];
    ppfOutputBuffer = new float*[iNumChannels];
    
    for (int i = 0; i < iNumChannels; i++)
    {
        ppfInputBuffer[i] = new float[samplesPerBlock];
        ppfOutputBuffer[i] = new float[samplesPerBlock];
    }
    
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

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    
//    float* channelData = buffer.getWritePointer (0);
//    m_CGlottis->process(channelData, channelData, buffer.getNumSamples());
//    m_CTract->process(channelData, channelData, buffer.getNumSamples());
//
//    for (int channel = 1; channel < totalNumInputChannels; channel++) {
//        float* other_channel_data = buffer.getWritePointer(channel);
//        memcpy(other_channel_data, channelData, sizeof(float) * buffer.getNumSamples());
//    }
    auto* channelData = buffer.getWritePointer (0);
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* inputChannelData = buffer.getReadPointer (channel);
        
        auto* channelData = buffer.getWritePointer (channel);
        
        memcpy(*ppfInputBuffer, inputChannelData, iNumberOfFrames);
        pCVibrato->process(ppfInputBuffer, ppfOutputBuffer, iNumberOfFrames);
        //auto** inputBuffer = buffer.getArrayOfReadPointers();
        memcpy(channelData, *ppfOutputBuffer, iNumberOfFrames);
//        for(int sample = 0; sample < buffer.getNumSamples(); sample++)
//        {
//
//            //channelData[sample] = buffer.getSample(channel, sample);
//
//
//        }
    }
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

//==============================================================================
void VibratoPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void VibratoPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VibratoPluginAudioProcessor();
}