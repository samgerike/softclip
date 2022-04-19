//
//  MyLookAndFeel.hpp
//  Course Plugin

#pragma once

#include "JuceHeader.h"

using namespace juce;

class MyLookAndFeel : public LookAndFeel_V4
{
public:
    
    /*
     CONSTRUCTOR
     */
    MyLookAndFeel();
    
    /*
     DESTRUCTOR
     */
    ~MyLookAndFeel();
    
    /*
     Draws a slider on screen
     */
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override;
    
private:
    
};


