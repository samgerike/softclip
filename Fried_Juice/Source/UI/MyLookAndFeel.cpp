//
//  MyLookAndFeel.cpp
//  Course Plugin

#include "MyLookAndFeel.h"


    
/*
 CONSTRUCTOR
 */
MyLookAndFeel::MyLookAndFeel(){
    
}

/*
 DESTRUCTOR
 */
MyLookAndFeel::~MyLookAndFeel(){
    
}

/*
 Draws a slider on screen
 */
void MyLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    //Sets colors of the slider
//    auto outline = Colours::darkred;
//    auto fill = Colours::red;
    uint8 a_color = 145;
    auto gradient_fill = ColourGradient(Colour(214,214,214), 100, 0, Colour(a_color, a_color, a_color, 0.f), 50, 100, false);
    
    //Creates a bounding box rectangle to contain our rotary slider
    auto bounds = Rectangle<int> (x, y, width, height).toFloat();
    auto bounds_inner = Rectangle<int> (x, y, width, height).toFloat().reduced(5);
    
    //Finds the smaller value between width and height of our bounds and sets the radius of the slider to half of that value
    auto arcRadius = jmin(bounds_inner.getWidth(), bounds.getHeight()) / 2.0f;
    
    //Finds the total travel distance of the slider and multiplies it by the current slider position then adds it to the starting angle
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
//    //Line width is assigned as the lesser of 8 or half the radius
//    auto lineW = jmin(8.0f, radius * 0.5f);
    
    //Uses line width to determine the correct arc radius for positional inidcator so it stays centered on the line
    //auto arcRadius = radius - lineW * 0.5f;
    
    g.setColour(Colour(49, 47, 47));
    g.fillEllipse(bounds);
    
    g.setGradientFill(gradient_fill);
    g.fillEllipse(bounds_inner);
    
    
    //Initialize a juce path and create the slider background arc
//    Path backgroundArc;
//    backgroundArc.addCentredArc(bounds.getCentreX(),
//                            bounds.getCentreY(),
//                            arcRadius, arcRadius,
//                            0.f,
//                            rotaryStartAngle,
//                            rotaryEndAngle,
//                            true);
    //Apply color and arc parameters to draw with passed in Graphics object
//    g.setColour(outline);
//    g.strokePath(backgroundArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));
    
//    if (slider.isEnabled())
//    {
//        //Create an arc to display the value of our parameters
//        Path valueArc;
//        valueArc.addCentredArc(bounds.getCentreX(),
//                               bounds.getCentreY(),
//                               arcRadius,
//                               arcRadius,
//                               0.0f,
//                               rotaryStartAngle,
//                               toAngle,
//                               true);
//        //Apply color and arc parameters to draw with passed in Graphics object
//        g.setColour(fill);
//        g.strokePath(valueArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));
//    }
    
    //Create an ellipse to mark the current value of the slider
    auto tickWidth = bounds.getWidth() * .09f;
    uint8 b_color = 196;
    g.setColour(Colour(b_color, b_color, b_color, .8f));
    g.drawLine(bounds.getCentreX() + arcRadius * std::cos (toAngle - MathConstants<float>::halfPi), bounds.getCentreY() + arcRadius * std::sin (toAngle - MathConstants<float>::halfPi), bounds.getCentreX(), bounds.getCentreY(), tickWidth);
    
    
    
}

