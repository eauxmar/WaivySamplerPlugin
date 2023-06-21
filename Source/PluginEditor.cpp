/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloSamplerAudioProcessorEditor::HelloSamplerAudioProcessorEditor (HelloSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    mLoadButton.onClick = [&]() {
        // Fetch the text from the query box and store it in typedText
        typedText = mQueryBox.getText();

        // Build the command string
        juce::String command = "/Users/omar/opt/anaconda3/bin/python /Users/omar/Documents/THESIS_CODE/argparsescript.py " + typedText;

        // Execute the command
        int result = system(command.toRawUTF8());
        if (result != 0)
        {
            // Handle error, print to console for now
            std::cout << "System command failed with code: " << result << std::endl;
        }

        loadImage();
        
        // Now load the file
        audioProcessor.loadFile();
        
        repaint();
    };
    //attack sliders below
    mAttackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
    mAttackSlider.setRange(0.0f, 5.0f, 0.01f);
    mAttackSlider.addListener(this);
    addAndMakeVisible(mAttackSlider);
    //attack labels
    mAttackLabel.setFont(10.0f);
    mAttackLabel.setText("Attack", juce::dontSendNotification);
    mAttackLabel.setJustificationType(juce::Justification::centredBottom);
    mAttackLabel.attachToComponent(&mAttackSlider, false);
    
    
    //decay sliders below
    mDecaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
    mDecaySlider.setRange(0.0f, 5.0f, 0.01f);
    mDecaySlider.addListener(this);
    addAndMakeVisible(mDecaySlider);
    //decay labels
    mDecayLabel.setFont(10.0f);
    mDecayLabel.setText("Decay", juce::dontSendNotification);
    mDecayLabel.setJustificationType(juce::Justification::centredBottom);
    mDecayLabel.attachToComponent(&mDecaySlider, false);
    
    
    //sustain sliders below
    mSustainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
    mSustainSlider.setRange(0.0f, 5.0f, 0.01f);
    mSustainSlider.addListener(this);
    addAndMakeVisible(mSustainSlider);
    //sustain labels
    mSustainLabel.setFont(10.0f);
    mSustainLabel.setText("Sustain", juce::dontSendNotification);
    mSustainLabel.setJustificationType(juce::Justification::centredBottom);
    mSustainLabel.attachToComponent(&mSustainSlider, false);
    
    
    //release sliders below
    mReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
    mReleaseSlider.setRange(0.0f, 5.0f, 0.01f);
    mReleaseSlider.addListener(this);
    addAndMakeVisible(mReleaseSlider);
    //release labels
    mReleaseLabel.setFont(10.0f);
    mReleaseLabel.setText("Release", juce::dontSendNotification);
    mReleaseLabel.setJustificationType(juce::Justification::centredBottom);
    mReleaseLabel.attachToComponent(&mReleaseSlider, false);
    

    
    //load initial image and load button
    loadImage();

    addAndMakeVisible(mLoadButton);

    // Set up the query box
    mQueryBox.setMultiLine(false);
    mQueryBox.setReturnKeyStartsNewLine(false);
    mQueryBox.setReadOnly(false);
    mQueryBox.setScrollbarsShown(true);
    mQueryBox.setCaretVisible(true);
    mQueryBox.setPopupMenuEnabled(true);
    mQueryBox.setText("");
    addAndMakeVisible(mQueryBox);
    
    setSize (500, 400);
}

HelloSamplerAudioProcessorEditor::~HelloSamplerAudioProcessorEditor()
{
}

//==============================================================================
void HelloSamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawImage(image, 8, 8, getWidth() - 16, 64, 0, 0, image.getWidth(), image.getHeight());
    
    g.setColour (juce::Colours::black);  // Set the colour of the border
    g.drawRect (imageBounds.toFloat(), 3.0f);
}

void HelloSamplerAudioProcessorEditor::resized()
{
    // Calculate component positions
    const int marginX = 20;
    const int marginY = 20;
    const int buttonWidth = 100;
    const int buttonHeight = 30;
    const int queryBoxHeight = 30;
    const int sliderWidth = 80;
    const int sliderHeight = 100;
    const int sliderSpacing = 20;
    
    // Set bounds for image component
    const int imageX = marginX;
    const int imageY = marginY; // Adjust the vertical position to be at the top of the screen
    const int imageWidth = getWidth() - 2 * marginX;
    const int imageHeight = getHeight() / 4;
    imageComponent.setBounds(imageX, imageY, imageWidth, imageHeight);
    
    // Set bounds for load button
    const int loadButtonX = (getWidth() - buttonWidth) / 2;
    const int loadButtonY = imageY + imageHeight + marginY;
    mLoadButton.setBounds(loadButtonX, loadButtonY, buttonWidth, buttonHeight);
    
    // Set bounds for query box
    const int queryBoxX = marginX;
    const int queryBoxY = loadButtonY + buttonHeight + marginY;
    const int queryBoxWidth = getWidth() - 2 * marginX;
    mQueryBox.setBounds(queryBoxX, queryBoxY, queryBoxWidth, queryBoxHeight);

    // Set bounds for sliders
    const int slidersX = marginX + 40;
    const int slidersY = queryBoxY + queryBoxHeight + marginY +10; // Increase the vertical position

    mAttackSlider.setBounds(slidersX, slidersY, sliderWidth, sliderHeight);
    mDecaySlider.setBounds(slidersX + sliderWidth + sliderSpacing, slidersY, sliderWidth, sliderHeight);
    mSustainSlider.setBounds(slidersX + 2 * (sliderWidth + sliderSpacing), slidersY, sliderWidth, sliderHeight);
    mReleaseSlider.setBounds(slidersX + 3 * (sliderWidth + sliderSpacing), slidersY, sliderWidth, sliderHeight);
}

void HelloSamplerAudioProcessorEditor::loadImage()
{
    juce::File imagefile("/Users/omar/Documents/THESIS_CODE/argparse_output/closest_match_waveform.png");
    image = juce::ImageFileFormat::loadFrom(imagefile);

    // Set the image to the ImageComponent and add it to the GUI
    imageComponent.setImage(image);
    addAndMakeVisible(imageComponent);
}


void HelloSamplerAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &mAttackSlider)
    {
        audioProcessor.getADSRParams().attack = mAttackSlider.getValue();
    }
    else if (slider == &mDecaySlider)
    {
        audioProcessor.getADSRParams().decay = mDecaySlider.getValue();
    }
    else if (slider == &mSustainSlider)
    {
        audioProcessor.getADSRParams().sustain = mSustainSlider.getValue();
    }
    else if (slider == &mReleaseSlider)
    {
        audioProcessor.getADSRParams().release = mReleaseSlider.getValue();
    }
    audioProcessor.updateADSR();
    
}
