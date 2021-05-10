#ifndef PARAMETER_MANAGER
#define PARAMETER_MANAGER
#include "Arduino.h"                            // Include the header file that defines INPUT and HIGH
#include "Parameter.h"
#include "Led_Controller.h"
#include "Sample_Player.h"

class Parameter_Manager
{ 
  protected:
    const int WRITE_TIME = 2000;
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
    Parameter m_kitPatternMenu;
    elapsedMillis m_timeSinceParameterChange;

  public:
    Parameter_Manager(Led_Controller *ledController);
    void poll();
    void flipKitPatternMenu();
};

#endif
