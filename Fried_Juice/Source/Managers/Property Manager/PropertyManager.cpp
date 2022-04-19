/*
  ==============================================================================

    PropertyManager.cpp
    Created: 13 Mar 2022 11:24:24am
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#include "PropertyManager.h"
#include "ProcessorInterface.h"
#include "PresetManager.h"

#include "FolderManager.h"
#include "ParameterManager.h"

class PresetManager;

/*
 
  loop through the presets from the preset manager's function getCurrentPresetNames and print them using DBG.
 
 */

PropertyManager::PropertyManager(ProcessorInterface* inInterface)
: mProcessorInterface(inInterface)
{
    StringArray presetNames = mProcessorInterface->getPresetManager()->getCurrentPresetNames();
    for (String s : presetNames) { DBG(s); }
}

PropertyManager::~PropertyManager()
{
    
}

void PropertyManager::PrintSomething()
{
    DBG("something");
}
