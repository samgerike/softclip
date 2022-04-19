/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveShaperAudioProcessor::WaveShaperAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
    mParameterManager.reset(new ParameterManager(this));
    mPresetManager.reset(new PresetManager(this));
}

WaveShaperAudioProcessor::~WaveShaperAudioProcessor()
{
}

//==============================================================================
const juce::String WaveShaperAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WaveShaperAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WaveShaperAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WaveShaperAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WaveShaperAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WaveShaperAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WaveShaperAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WaveShaperAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String WaveShaperAudioProcessor::getProgramName (int index)
{
    return {};
}

void WaveShaperAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void WaveShaperAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

}

void WaveShaperAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WaveShaperAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void WaveShaperAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    if (wrapperType == AudioProcessor::wrapperType_Standalone && SIMPLE_SAMPLE_IN_STANDALONE) {
        _generateSimpleSample(buffer);
    }
    
    float* left = buffer.getWritePointer(0);
    float* right = buffer.getWritePointer(1);
    
    float drive = getParameterManager()->getCurrentValue(DRIVE);
    
    for (int i = 0; i < buffer.getNumSamples(); i++) {
        left[i] *= drive;
        right[i] *= drive;
        
        mClipper.processSample(left[i]);
        mClipper.processSample(right[i]);
    }
}

ParameterManager* WaveShaperAudioProcessor::getParameterManager()
{
    return mParameterManager.get();
}

PresetManager* WaveShaperAudioProcessor::getPresetManager()
{
    return mPresetManager.get();
}

AudioProcessor* WaveShaperAudioProcessor::getAudioProcessor()
{
    return this;
}

//==============================================================================
bool WaveShaperAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* WaveShaperAudioProcessor::createEditor()
{
    return new WaveShaperAudioProcessorEditor (*this);
}

//==============================================================================
void WaveShaperAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // Get the underlying ValueTree from out "Parameter Value Tree"
    auto tree_state = mParameterManager->getValueTree()->copyState();
    
    // Convert the value tree into an XML object which can be saved on disk to as binary
    std::unique_ptr<juce::XmlElement> xml(tree_state.createXml());
    
    /* */
    DBG(xml->toString());

    /* store as binary */
    copyXmlToBinary(*xml, destData);
    
}

void WaveShaperAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get()) {
        
        DBG(xmlState->toString());
        
        juce::ValueTree parameter_tree = juce::ValueTree::fromXml(*xmlState);
        mParameterManager->getValueTree()->replaceState(parameter_tree);
        
    }
}

void WaveShaperAudioProcessor::_generateSimpleSample(AudioBuffer<float>& inBuffer)
{
#if SIMPLE_SAMPLE_IN_STANDALONE
    static int mPhase = 0;
    
    if (!mTestingSample.isFileLoaded()) {
        
        File dir = File::getSpecialLocation(File::SpecialLocationType::currentExecutableFile);
        
        String dir_name = dir.getFileName();
        
        while (dir_name.contains("Fried_Juice") == false) {
            dir = dir.getParentDirectory();
            dir_name = dir.getFileName();
        }
        
        String file_name = "break.wav";
        
        File sample = dir
        .getChildFile("Test_Audio")
        .getChildFile(file_name);

        mTestingSample.loadFile(sample);
    }
    
    for (int i = 0; i < inBuffer.getNumSamples(); i++) {
        std::vector<float> samples(2);
        mTestingSample.getSample(mPhase, samples);
        inBuffer.setSample(0, i, samples[0]);
        inBuffer.setSample(1, i, samples[1]);
        mPhase += 1;
        if (mPhase >= mTestingSample.getLengthInSamples()) {
            mPhase = 0;
        }
    }
#endif
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WaveShaperAudioProcessor();
}
