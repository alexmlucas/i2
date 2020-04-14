#include "Sample.h"

Sample::Sample(AudioPlaySdWav *sdWav){
  m_sdWav = sdWav;
}

void Sample::playSample(float sampleVolume){
  this->setVolume(sampleVolume);
  m_sdWav->play(m_sampleName.c_str());
  
}

void Sample::setMixersAndChannels(AudioMixer4 *leftMixer, AudioMixer4 *rightMixer, int leftMixerChannelNumber, int rightMixerChannelNumber){
  m_leftMixer = leftMixer;
  m_rightMixer = rightMixer;
  m_leftMixerChannelNumber = leftMixerChannelNumber;
  m_rightMixerChannelNumber = rightMixerChannelNumber;
}

void Sample::setVolume(float sampleVolume){
  m_sampleVolume = sampleVolume;
  m_leftMixer->gain(m_leftMixerChannelNumber, m_sampleVolume);
  m_rightMixer->gain(m_leftMixerChannelNumber, m_sampleVolume);
}

void Sample::setSampleName(String sampleName){
  m_sampleName = sampleName;
  Serial.println(m_sampleName);
}
