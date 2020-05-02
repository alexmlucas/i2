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
    elapsedMillis m_timer;
    elapsedMillis m_envelopeReleaseTimer;
    bool m_inEnvelopeReleaseStage;
    
    bool m_eventQueued;

    bool m_fadeAndRetriggerActive;
    elapsedMillis m_fadeAndRetriggerTimer;
    float m_retriggerVelocity; 
    
    int m_leftMixerChannelNumber;
    int m_rightMixerChannelNumber;
    float m_sampleVolume;
    float m_queuedSampleVolume;
    float m_eventQueue[8];
    int m_numberOfQueuedEvents;

    void initialiseEnvelopeObjects();
    
  public:
    String m_sampleName;
    Sample_Player(AudioPlaySdWav *sdWav);

    void processTriggerEvent(float velocity);
    void playWithVelocity(float velocity);
    void fadeAndRetrigger(float velocity);
    void assignMixerObjects(AudioMixer4 *leftMixer, AudioMixer4 *rightMixer, int leftMixerChannelNumber, int rightMixerChannelNumber);
    void assignFadeObjects(AudioEffectFade *leftFade, AudioEffectFade *rightFade);
    void setSampleName(String sampleName);
    void poll();
};

#endif
