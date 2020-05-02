#ifndef SAMPLE_PLAYER
#define SAMPLE_PLAYER
#include "Arduino.h"
#include <Audio.h>

#define _ATTACK_MS 40
#define _HOLD_MS 0
#define _DECAY_MS 0
#define _RELEASE_MS 5
#define _RETRIGGER_MS 6

class Sample_Player{
  
  private:
    AudioPlaySdWav *m_sdWav;
    AudioMixer4 *m_leftMixer;
    AudioMixer4 *m_rightMixer;
    AudioEffectEnvelope *m_leftEnvelope;
    AudioEffectEnvelope *m_rightEnvelope;
    elapsedMillis m_timer;
    elapsedMillis m_envelopeReleaseTimer;
    bool m_inEnvelopeReleaseStage;
    
    bool m_eventQueued;

    bool m_fadeAndRetriggerActive;
    elapsedMillis m_fadeAndRetriggerTimer;
    bool m_retriggerVelocity; 
    
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
    void assignEnvelopeObjects(AudioEffectEnvelope *leftEnvelope, AudioEffectEnvelope *rightEnvelope);
    void setSampleName(String sampleName);
    void poll();
};

#endif
