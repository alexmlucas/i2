#include "Parameter_Manager.h"

Parameter_Manager::Parameter_Manager(Rhythm_Generator *rhythmGenerator)
{
    m_rhythmGenerator = rhythmGenerator;
    
    // ### Set parameter EEPROM storage indexes ###
    m_kitPatternMenu.storageIndex = 0;
    m_kit.storageIndex = 1;
    m_pattern.storageIndex = 2;
    m_speed.storageIndex = 3;

    // ### Read data from EEPROM ### (dummy data used at the moment!)
    m_kitPatternMenu.value = 1;                                     
    m_kit.value = 0;
    m_pattern.value = 1;  
    m_speed.value = 1;
    
    // ### Reset all write flags ###
    m_kitPatternMenu.writeFlag = false;            
    m_kit.writeFlag = false;
    m_pattern.writeFlag = false;
    m_speed.writeFlag = false;  

    // ### Set parameters in RAM ###         
    m_rhythmGenerator->setSpeed(m_speed.value);                     
    
    // ### Update LED states ###
    /*m_ledController->setKitPattMenuLeds(m_kitPatternMenu.value);    
    if(m_kitPatternMenu.value == 0)                                 // determine if the selected kit or pattern needs to be displayed.
    {
        m_ledController->setKitPattNumLeds(m_kit.value);
    } else if(m_kitPatternMenu.value == 1)
    {
        m_ledController->setKitPattNumLeds(m_pattern.value);
    }

    m_ledController->setSpeedMenuLeds(m_speed.value);*/               
}

void Parameter_Manager::poll()
{
    if(m_timeSinceParameterChange > WRITE_TIME)
    {
        if(m_kitPatternMenu.writeFlag)
        {
            // write to EEPROM here
            m_kitPatternMenu.writeFlag = false;                     // reset flag
        }

        if(m_speed.writeFlag)
        {
            // write to EEPROM here
            Serial.println("writing speed");
            m_speed.writeFlag = false;                              // reset flag
        }
    }    
}

void Parameter_Manager::setKitPattern(int index)
{
    if(m_kitPatternMenu.value == 0)
    {
        Serial.print("Setting kit ");
    } else if(m_kitPatternMenu.value == 1)
    {
        Serial.print("Setting pattern ");
    }
}

void Parameter_Manager::setSpeed(int speed)
{
    m_speed.value = speed;
    m_speed.writeFlag = true;
    m_timeSinceParameterChange = 0;
}

/*void Parameter_Manager::flipKitPatternMenu()
{
    m_kitPatternMenu.value = !m_kitPatternMenu.value;
    m_ledController->setKitPattMenuLeds(m_kitPatternMenu.value);
    m_kitPatternMenu.writeFlag = true;
    m_timeSinceParameterChange = 0;
}

void Parameter_Manager::decrementSpeed()
{
    if(m_speed.value > 0)                               // decrement looks more natural on the UI
    {
        m_speed.value--;
    } else
    {
        m_speed.value = 2;
    }

    m_rhythmGenerator->setSpeed(m_speed.value);         // set the speed of the rhythm generator
    m_speed.writeFlag = true;                           // flag EEPROM write.
    m_timeSinceParameterChange = 0;                     // reset timer.
    m_ledController->setSpeedMenuLeds(m_speed.value);   // update the LEDs
}


void Parameter_Manager::flipPlayState()
{
    m_playState = !m_playState;
    // set the sequencer running here.
    m_ledController->setPlayLed(m_playState);
}

void Parameter_Manager::flipRecordState()
{
    m_recordState = !m_recordState;
    // set the sequencer into record here.
    m_ledController->setRecordLed(m_recordState);
}

bool Parameter_Manager::getPlayState()
{
    return m_playState;
}

bool Parameter_Manager::getRecordState()
{
    return m_recordState;
}

void Parameter_Manager::triggerUndoEvent()
{
    // trigger the undo event - I'm not sure this really belongs here.
    m_ledController->pulseUndoLed();
}*/