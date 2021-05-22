#ifndef DELAY_EFFECT
#define DELAY_EFFECT
#include "Arduino.h"
#include <Audio.h>
#include "Constant_Parameters.h"
#include "Parameter_Manager.h"

// filter (fixed frequency)
// feedback
// wet/dry

class Delay_Effect
{ 
  private:
    const int MS_IN_MINUTE = 60000;
    const int DELAY_DIVISION = 2;
    AudioEffectDelay *m_delay;
    AudioAmplifier *m_feedbackAmp;
    AudioMixer4 *m_inputMixer;
    AudioMixer4 *m_leftOutputMixer;
    AudioMixer4 *m_rightOutputMixer;
    AudioFilterStateVariable *m_highPassFilter;
    Parameter_Manager *m_parameterManager;
    
  public:
    Delay_Effect(AudioEffectDelay *delay, AudioAmplifier *feedbackAmp, AudioMixer4 *inputMixer, AudioMixer4 *leftOutputMixer, AudioMixer4 *rightOutputMixer, AudioFilterStateVariable *highPassFilter, Parameter_Manager *Parameter_Manager);
    //void setDelayTime()
    int calculateDelayTime();
    void setDepth(int depth);
    void refreshDelayTime();
};

#endif