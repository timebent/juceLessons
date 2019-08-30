/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/

class SinOsc
{
public:
    
    SinOsc() {}
    // ~SinOsc();
    
    SinOsc(float freq, float amp, double sampleRate) {
        mSampleRate = sampleRate;
        setFreq(freq);
        mAmp = amp;
        mPhase = 0;
        calculatePhaseStep(freq);
    }
    
    float getSample() {
        float mSample = calculateAmp(mPhase);
        incrementPhase(mPhase);
        return mSample * mAmp;
    }
    void setFreq(float freq) {
        mFreq = freq;
        calculatePhaseStep(freq);
    }
    
private:
    void calculatePhaseStep(float freq) {
        mPhaseStep = (twoPi * freq) / mSampleRate;
    };
    
    float calculateAmp(float phase) {
        return sin(phase);
    }
    
    void incrementPhase(float phase) {
        mPhase += mPhaseStep;
        if(mPhase >= twoPi) {mPhase = mPhase - twoPi;}
    }
    
    float mPhase;
    float mPhaseStep;
    float mFreq;
    float mAmp;
    double mSampleRate;
    float mSample;
    float twoPi = M_PI * 2;
};

class SineWithClassAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SineWithClassAudioProcessor();
    ~SineWithClassAudioProcessor();

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
    
    std::vector<SinOsc> sineVector;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SineWithClassAudioProcessor)
    Random random = Random::getSystemRandom();
    int timer = 0.0;
};
