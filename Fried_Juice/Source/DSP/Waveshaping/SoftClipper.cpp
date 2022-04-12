//
//  SoftClipper.cpp
//  Fried Juice - Shared Code
//
//  Created by Jacob Penn on 4/11/22.
//

#include "SoftClipper.h"

/* CONSTRUCTOR
 */
SoftClipper::SoftClipper()
{
    
}


/* DECONSTRUCTOR
 */
SoftClipper::~SoftClipper()
{
    
}

/* */
void SoftClipper::processSample(float& inSample)
{
    inSample = std::tanh(inSample);
}
