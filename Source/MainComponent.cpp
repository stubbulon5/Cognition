#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    juce::Rectangle<int> r = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea;
    setSize (r.getWidth(), r.getHeight());
    
    addChildComponent(testWidget);
//    testWidget.setBounds (10, 10, getWidth()-20, getHeight()-400);
    
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    testWidget.paint(g);

}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    testWidget.setBounds (10, 30, getWidth()-20, getHeight()-400);
}
