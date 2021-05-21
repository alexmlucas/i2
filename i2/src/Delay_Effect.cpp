#include "Delay_Effect.h"

Delay_Effect::Delay_Effect(AudioEffectDelay *delay, AudioAmplifier *feedbackAmp, AudioMixer4 *inputMixer, AudioMixer4 *leftWetDryMixer, AudioMixer4 *rightWetDryMixer, AudioFilterStateVariable *highPassFilter, Parameter_Manager *parameterManager)
{ 
    m_delay = delay;
    m_feedbackAmp = feedbackAmp;
    m_inputMixer = inputMixer;
    m_leftWetDryMixer = leftWetDryMixer;
    m_rightWetDryMixer = rightWetDryMixer;
    m_highPassFilter = highPassFilter;
    m_parameterManager = parameterManager;

    //m_inputMixer->gain(0, 0.9);
    //m_inputMixer->gain(1, 0.9);
    //m_inputMixer->gain(2, 0.9);
    //m_leftWetDryMixer->gain(0, 0.4);
    //m_leftWetDryMixer->gain(1, 0.4);
    //m_rightWetDryMixer->gain(0, 0.4);
    //m_rightWetDryMixer->gain(1, 0.4);
    
    m_feedbackAmp->gain(0.1);
    m_highPassFilter->frequency(100.0);

 
    m_delay->delay(0, this->calculateDelayTime());         // channel, delay in ms.
    //m_delay->delay(1, 50.0);         // channel, delay in ms.

}

int Delay_Effect::calculateDelayTime()
{
  // MS  = 60,000 
  int crotchetInterval = MS_IN_MINUTE / m_parameterManager->getMasterTempo();
  int quaverInterval = round(crotchetInterval / 2);
  return quaverInterval;
}