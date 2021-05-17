#ifndef SAMPLE_PLAYER
#define SAMPLE_PLAYER
#include "Arduino.h"
#include <Audio.h>

#define FADE_OUT_MS 5
#define FADE_IN_MS 1

class Sample_Player{
  
  private:
    AudioPlaySdWav *m_sdWav;
    AudioMixer4 *m_leftMixer;
    AudioMixer4 *m_rightMixer;
    AudioEffectFade *m_leftFade;
    AudioEffectFade *m_rightFade;

    bool m_fadeAndRetriggerActive;                    // keep track of when fadeAndRetrigger is active
    bool m_stopRequestMade;                           // record that a stop request has been made during fadeAndRetrigger event
    bool m_fadeInRequestMade;                         // record that a fadeIn request has been made during fadeAndRetrigger event
    elapsedMillis m_fadeAndRetriggerTimer;
    float m_retriggerVelocity;     
    int m_leftMixerChannelNumber;
    int m_rightMixerChannelNumber;
    String m_sampleName;
    int m_sampleIndex;

    void playWithVelocity(float velocity);
    void fadeAndRetrigger(float velocity);
    void setMixerLevels(float velocity);
    
  public:
    elapsedMillis m_latencyTimer; 
  
    //Sample_Player(AudioPlaySdWav *sdWav);

    Sample_Player(AudioPlaySdWav *sdWav, int kitIndex, int sampleIndex);
    void processTriggerEvent(float velocity);
    void assignMixerObjects(AudioMixer4 *leftMixer, AudioMixer4 *rightMixer, int leftMixerChannelNumber, int rightMixerChannelNumber);
    void assignFadeObjects(AudioEffectFade *leftFade, AudioEffectFade *rightFade);
    void setKit(int kitIndex);
    void setSampleName(String sampleName);
    void poll();
    String buildFilename(int kitIndex, int sampleIndex);

};

#endif
