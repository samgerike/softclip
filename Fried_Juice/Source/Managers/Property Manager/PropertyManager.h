/*
  ==============================================================================

    PropertyManager.h
    Created: 13 Mar 2022 11:24:24am
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#pragma once
#ifndef PropertyManager_h
#define PropertyManager_h

#include "JuceHeader.h"


class ProcessorInterface;

class PropertyManager{

public:
    
    /**/
    PropertyManager(ProcessorInterface* inInterface);

    /**/
    ~PropertyManager();


    void PrintSomething();
    
    
private:
    
    ProcessorInterface* mProcessorInterface;
    
    
};









#endif
