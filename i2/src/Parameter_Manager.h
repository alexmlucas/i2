#ifndef PARAMETER_MANAGER
#define PARAMETER_MANAGER
#include "Arduino.h"                            // Include the header file that defines INPUT and HIGH
#include "Eeprom_Parameter.h"
#include "Led_Controller.h"
#include "Sample_Player.h"
#include "Rhythm_Generator.h"
#include "Display_Controller.h"

class Parameter_Manager
{ 
  protected:
    const unsigned int WRITE_TIME = 2000;
    // parameter could have
    // an EEPROM index
    // a value
    // a write flag.

    // parameters are...
    // kit pattern state
    // slow fast state
    // tempo volume state
    // tempo
    // volume
    // kit
    // pattern

    // Rhythm
    // Echo
    Led_Controller *m_ledController;
    Rhythm_Generator *m_rhythmGenerator;
    Display_Controller *m_displayController;
    Eeprom_Parameter m_kitPatternMenu;
    Eeprom_Parameter m_kit;
    Eeprom_Parameter m_pattern;
    Eeprom_Parameter m_speed;

    // non-eeprom parameters
    bool m_playState = false;
    bool m_recordState = false;
    
    elapsedMillis m_timeSinceParameterChange;
    
  public:
    

    Parameter_Manager(Led_Controller *ledController, Display_Controller *m_displayController, Rhythm_Generator *rhythmGenerator);
    void poll();
    void flipKitPatternMenu();

    void decrementSpeed();
    void setKitPattern(int index);
    void flipPlayState();
    void flipRecordState();
    bool getPlayState();
    bool getRecordState();
    void triggerUndoEvent();
};

#endif
