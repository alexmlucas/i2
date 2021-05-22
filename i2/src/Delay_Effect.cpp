#include "Delay_Effect.h"

Delay_Effect::Delay_Effect(AudioEffectDelay *delay, AudioAmplifier *feedbackAmp, AudioMixer4 *inputMixer, AudioMixer4 *leftOutputMixer, AudioMixer4 *rightOutputMixer, AudioFilterStateVariable *highPassFilter, Parameter_Manager *parameterManager)
{ 
    m_delay = delay;
    m_feedbackAmp = feedbackAmp;
    m_inputMixer = inputMixer;
    m_leftOutputMixer = leftOutputMixer;
    m_rightOutputMixer = rightOutputMixer;
    m_highPassFilter = highPassFilter;
    m_parameterManager = parameterManager;

    //m_inputMixer->gain(0, 0.9);
    //m_inputMixer->gain(1, 0.9);
    //m_inputMixer->gain(2, 0.9);
    //m_leftWetDryMixer->gain(0, 0.4);
    //m_leftWetDryMixer->gain(1, 0.4);
    //m_rightWetDryMixer->gain(0, 0.4);
    //m_rightWetDryMixer->gain(1, 0.4);
    
    m_feedbackAmp->gain(0);
    m_leftOutputMixer->gain(1, 0);
    m_rightOutputMixer->gain(1, 0);
    m_highPassFilter->frequency(250.0);
    m_delay->delay(0, this->calculateDelayTime());
}

int Delay_Effect::calculateDelayTime()
{
  int crotchetInterval = MS_IN_MINUTE / m_parameterManager->getMasterTempo();
  int quaverInterval = round(crotchetInterval / DELAY_DIVISION);
  return quaverInterval;
}

void Delay_Effect::setDepth(int depth)
{
  float feedbackAmount = map((float)depth, 0, 127, 0.0, 0.9);
  float mixAmount = map((float)depth, 0, 127, 0.0, 0.9);
  this->m_feedbackAmp->gain(feedbackAmount);
  this->m_leftOutputMixer->gain(1, mixAmount);
  this->m_rightOutputMixer->gain(1, mixAmount);
}

void Delay_Effect::refreshDelayTime()
{
  m_delay->delay(0, this->calculateDelayTime());
  Serial.println(this->calculateDelayTime());
}