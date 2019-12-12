#include "Sample.h"

Sample::Sample(AudioPlaySdWav *sdWav){
   m_sdWav = sdWav;
}

Sample::playSample(){
  m_sdWav->play(m_sampleName.c_str());
}

Sample::setMixersAndChannels(AudioMixer4 *leftMixer, AudioMixer4 *rightMixer, int leftMixerChannelNumber, int rightMixerChannelNumber){
  m_leftMixer = leftMixer;
  m_rightMixer = rightMixer;
  m_leftMixerChannelNumber = leftMixerChannelNumber;
  m_rightMixerChannelNumber = rightMixerChannelNumber;
}

Sample::setVolume(float sampleVolume){
  m_sampleVolume = sampleVolume;
  m_leftMixer->gain(m_leftMixerChannelNumber, m_sampleVolume);
  m_rightMixer->gain(m_leftMixerChannelNumber, m_sampleVolume);
}

Sample::setSampleName(String sampleName){
  
  m_sampleName = sampleName;
  Serial.println(m_sampleName);
}
