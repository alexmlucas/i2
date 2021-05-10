#include "Parameter_Manager.h"

Parameter_Manager::Parameter_Manager(Led_Controller *ledController)
{
    m_ledController = ledController;
    m_kitPatternMenu.storageIndex = 0;
    m_kitPatternMenu.value = 0;                                     // read from EEPROM here.
    m_ledController->setKitPattMenuLeds(m_kitPatternMenu.value);    // update LEDs
    m_kitPatternMenu.writeFlag = false;
}

void Parameter_Manager::poll()
{
    if(m_timeSinceParameterChange > WRITE_TIME)
    {
        if(m_kitPatternMenu.writeFlag)
        {
            // write to EEPROM
            Serial.println("writing");
            m_kitPatternMenu.writeFlag = false;
        }
    }    
}

void Parameter_Manager::flipKitPatternMenu()
{
    m_kitPatternMenu.value = !m_kitPatternMenu.value;
    m_ledController->setKitPattMenuLeds(m_kitPatternMenu.value);
    m_kitPatternMenu.writeFlag = true;
    m_timeSinceParameterChange = 0;
}