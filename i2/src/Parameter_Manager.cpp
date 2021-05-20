#include "Parameter_Manager.h"

Parameter_Manager::Parameter_Manager()
{
    // ### Set parameter EEPROM storage indexes ###
    m_kitIndex.storageIndex = 0;
    m_patternIndex.storageIndex = 1;
    m_masterTempo.storageIndex = 2;
    m_masterVolume.storageIndex = 3;

    // ### Reset all write flags ###          
    m_kitIndex.writeFlag = false;
    m_patternIndex.writeFlag = false;
    m_masterTempo.writeFlag = false; 
    m_masterVolume.writeFlag = false;

    // ### Read data from Eepromm ###  
    m_kitIndex.value = EEPROM.read(m_kitIndex.storageIndex);
    m_patternIndex.value = EEPROM.read(m_patternIndex.storageIndex);
    m_masterTempo.value = EEPROM.read(m_masterTempo.storageIndex); 
    m_masterVolume.value = EEPROM.read(m_masterVolume.storageIndex);

}

void Parameter_Manager::poll()
{
    if(m_timeSinceParameterChange > WRITE_TIME)
    {
        if(m_kitIndex.writeFlag)
        {
            EEPROM.write(m_kitIndex.storageIndex, m_kitIndex.value);
            m_kitIndex.writeFlag = false;                              // reset flag
        }

        if(m_patternIndex.writeFlag)
        {
            EEPROM.write(m_patternIndex.storageIndex, m_patternIndex.value);
            m_patternIndex.writeFlag = false;                              // reset flag
        }

        if(m_masterTempo.writeFlag)
        {
            EEPROM.write(m_masterTempo.storageIndex, m_masterTempo.value);
            m_masterTempo.writeFlag = false;                              // reset flag
        }

        if(m_masterVolume.writeFlag)
        {
            EEPROM.write(m_masterVolume.storageIndex, m_masterVolume.value);
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

int Parameter_Manager::getMasterVolume()
{
    return m_masterVolume.value;
}

void Parameter_Manager::saveKitIndex(int kitIndex)
{
    m_kitIndex.value = kitIndex;
    m_timeSinceParameterChange = 0;
    m_kitIndex.writeFlag = true;
}

void Parameter_Manager::savePatternIndex(int patternIndex)
{
    m_patternIndex.value = patternIndex;
    m_timeSinceParameterChange = 0;
    m_patternIndex.writeFlag = true;
}

void Parameter_Manager::saveMasterTempo(int masterTempo)
{
    m_masterTempo.value = masterTempo;
    m_timeSinceParameterChange = 0;
    m_masterTempo.writeFlag = true;
}

void Parameter_Manager::saveMasterVolume(int masterVolume)
{
    m_masterVolume.value = masterVolume;
    m_timeSinceParameterChange = 0;
    m_masterVolume.writeFlag = true;
}