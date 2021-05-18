#include "Parameter_Manager.h"

Parameter_Manager::Parameter_Manager()
{
    
    // ### Set parameter EEPROM storage indexes ###
    m_kitIndex.storageIndex = 1;
    m_patternIndex.storageIndex = 2;
    m_masterTempo.storageIndex = 3;
    m_masterVolume.storageIndex = 4;

    // ### Reset all write flags ###          
    m_kitIndex.writeFlag = false;
    m_patternIndex.writeFlag = false;
    m_masterTempo.writeFlag = false; 
    m_masterVolume.writeFlag = false;

    // ### Dummay data, will need to read from Eepromm ###  
    m_kitIndex.value = 1;
    m_patternIndex.value = 2;
    m_masterTempo.value = 110; 
    m_masterVolume.value = 9;
}

void Parameter_Manager::poll()
{
    if(m_timeSinceParameterChange > WRITE_TIME)
    {
        if(m_kitIndex.writeFlag)
        {
            // write to EEPROM here
            Serial.println("writing kit index");
            m_kitIndex.writeFlag = false;                              // reset flag
        }

        if(m_patternIndex.writeFlag)
        {
            // write to EEPROM here
            Serial.println("writing pattern index");
            m_patternIndex.writeFlag = false;                              // reset flag
        }

        if(m_masterTempo.writeFlag)
        {
            // write to EEPROM here
            Serial.println("writing master tempo");
            m_masterTempo.writeFlag = false;                              // reset flag
        }

        if(m_masterVolume.writeFlag)
        {
            // write to EEPROM here
            Serial.println("writing master volume");
            m_masterVolume.writeFlag = false;                              // reset flag
        }
    }    
}

int Parameter_Manager::getKitIndex()
{
    return m_kitIndex.value;
}

int Parameter_Manager::getPatternIndex()
{
    return m_patternIndex.value;
}

int Parameter_Manager::getMasterTempo()
{
    return m_masterTempo.value;
}

void Parameter_Manager::saveKitIndex(int kitIndex)
{
    m_kitIndex.value = kitIndex;
    m_kitIndex.writeFlag = true;
}

void Parameter_Manager::savePatternIndex(int patternIndex)
{
    m_patternIndex.value = patternIndex;
    m_patternIndex.writeFlag = true;
}

void Parameter_Manager::saveMasterTempo(int masterTempo)
{
    m_masterTempo.value = masterTempo;
    m_masterTempo.writeFlag = true;
}

void Parameter_Manager::saveMasterVolume(int masterVolume)
{
    m_masterVolume.value = masterVolume;
    m_masterVolume.writeFlag = true;
}