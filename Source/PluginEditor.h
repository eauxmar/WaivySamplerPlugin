/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class HelloSamplerAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                          public juce::Slider::Listener
{
public:
    HelloSamplerAudioProcessorEditor (HelloSamplerAudioProcessor&);
    ~HelloSamplerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    //added methods below
    void sliderValueChanged (juce::Slider* slider) override;
    
    
    void loadImage();

private:
    juce::TextButton mLoadButton {"load"};
    juce::TextEditor mQueryBox;
    juce::String typedText;
    
    juce::Image image;
    juce::ImageComponent imageComponent;
    
    juce::Rectangle<int> imageBounds;
    
    //slider inits
    juce::Slider mAttackSlider, mDecaySlider, mSustainSlider, mReleaseSlider;
    juce::Label mAttackLabel, mDecayLabel, mSustainLabel, mReleaseLabel;
    
    juce::Slider mMasterVolumeSlider;
    //juce::Label mMasterVolumeLabel;

    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HelloSamplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloSamplerAudioProcessorEditor)
};

