#ifndef SAMPLE
#define SAMPLE
#include "Arduino.h"
#include <Audio.h>

class Sample{
  
  private:
    AudioPlaySdWav *m_sdWav;
    AudioMixer4 *m_leftMixer;
    AudioMixer4 *m_rightMixer;
    int m_leftMixerChannelNumber;
    int m_rightMixerChannelNumber;
    float m_sampleVolume;
    
      
  public:
    String m_sampleName;
    Sample(AudioPlaySdWav *sdWav);
    playSample();
    setMixersAndChannels(AudioMixer4 *leftMixer, AudioMixer4 *rightMixer, int leftMixerChannelNumber, int rightMixerChannelNumber);
    setVolume(float sampleVolume);
    setSampleName(String sampleName);
};

#endif
