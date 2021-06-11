#ifndef PARAMETER_MANAGER
#define PARAMETER_MANAGER
#include "Arduino.h"                            // Include the header file that defines INPUT and HIGH
#include <EEPROM.h>
#include "Eeprom_Parameter.h"
#include "Eeprom_Pattern.h"
#include "Pattern_32.h"
#include "Led_Controller.h"
#include "Sample_Player.h"
#include "Rhythm_Generator.h"
#include "Display_Controller.h"

class Parameter_Manager
{ 
  protected:
    const unsigned int WRITE_TIME = 2000;

    Rhythm_Generator *m_rhythmGenerator;
    Eeprom_Parameter m_kitIndex;
    Eeprom_Parameter m_patternIndex;
    Eeprom_Parameter m_masterTempo;
    Eeprom_Parameter m_masterVolume;
    //Eeprom_Pattern m_patterns[4];
    elapsedMillis m_timeSinceParameterChange;
    
  public:
    Parameter_Manager();
    void poll();
    int getKitIndex();
    int getPatternIndex();
    int getMasterTempo();
    int getMasterVolume();
    //Pattern_32 getPattern(int patternIndex);
    void saveKitIndex(int kitIndex);
    void savePatternIndex(int patternIndex);
    void saveMasterTempo(int masterTempo);
    void saveMasterVolume(int masterVolume);
    //void savePattern(int patternIndex, Pattern_32 patternToSave);
};

#endif
