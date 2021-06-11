#ifndef OUTPUT_AMP
#define OUTPUT_AMP
#include "Arduino.h"
#include <Audio.h>

class Output_Amplifier
{ 
  private:
    AudioAmplifier *m_leftAmp;
    AudioAmplifier *m_rightAmp;
    int m_level;
    
  public:
    Output_Amplifier(AudioAmplifier *leftAmp, AudioAmplifier *rightAmp);
    void setLevel(int level);
    int getLevelAsInt();
    void incrementLevel();
    void decrementLevel();
};

#endif
