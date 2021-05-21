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
    
    m_feedbackAmp->gain(0.2);
    m_highPassFilter->frequency(300.0);
    m_delay->delay(0, this->calculateDelayTime());
}

int Delay_Effect::calculateDelayTime()
{
  int crotchetInterval = MS_IN_MINUTE / m_parameterManager->getMasterTempo();
  int quaverInterval = round(crotchetInterval / m_currentDelayMultiplier);
  return quaverInterval;
}

void Delay_Effect::setDepth(int depth)
{
  int newDelayMultiplier = 0;
  
  if(depth < 32)
  {
    newDelayMultiplier = 2;
  } else if(depth >= 32 && depth < 64)
  {
    newDelayMultiplier = 4;
  } else if (depth >= 64 && depth < 96)
  {
    newDelayMultiplier = 6;
  } else if (depth >= 96 && depth < 127)
  {
    newDelayMultiplier = 8;
  }

  if(newDelayMultiplier != m_currentDelayMultiplier)
  {
    m_currentDelayMultiplier = newDelayMultiplier;
    this->refreshDelayTime();
  }
}

void Delay_Effect::refreshDelayTime()
{
  m_delay->delay(0, this->calculateDelayTime());
  Serial.println(this->calculateDelayTime());
}