//
//  SoftClipper.h
//  Fried Juice - Shared Code
//
//  Created by Jacob Penn on 4/11/22.
//

#ifndef SoftClipper_h
#define SoftClipper_h

#include "JuceHeader.h"

class SoftClipper {
public:
    
    /* CONSTRUCTOR
     */
    SoftClipper();
    
    
    /* DECONSTRUCTOR
     */
    ~SoftClipper();
    
    /* */
    void processSample(float& inSample);
    
private:
    
};
    
#endif /* SoftClipper_h */
