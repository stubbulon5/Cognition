/*
  ==============================================================================

    uiVizWidgetBase.h
    Created: 17 Mar 2024 8:22:41am
    Author:  Zabba

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class uiVizWidgetBase  : public juce::Component
{
public:
    uiVizWidgetBase()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    ~uiVizWidgetBase() override
    {
    }

    virtual void paint (juce::Graphics& g) override
    {
        
    }

    virtual void resized() override
    {

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (uiVizWidgetBase)
};
