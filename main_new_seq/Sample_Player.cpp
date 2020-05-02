#include "Sample_Player.h"

Sample_Player::Sample_Player(AudioPlaySdWav *sdWav)
{
  m_sdWav = sdWav;
  m_eventQueued = false;
  m_inEnvelopeReleaseStage = false;
  m_numberOfQueuedEvents = 0;
  
  m_fadeAndRetriggerActive = false;

  for(int i = 0; i < (sizeof(m_eventQueue) / sizeof(m_eventQueue[0])); i++)   // initialise the event queue
  {
    m_eventQueue[i] = 0.0;
  }
}

void Sample_Player::processTriggerEvent(float velocity)
{
  /*if(!m_fadeAndRetriggerActive)               // if a fadeAndRetrigger event is not active...
  {
    Serial.println("fadeAndRetrigger is not Active");
    if(!m_sdWav->isPlaying())                 // if the sample is not playing.
    {
      Serial.println("The sample is not playing");
      Serial.print("Playing with a velocity of ");
      Serial.println(velocity);
      this->playWithVelocity(velocity);       // ...play the sample.
    } else                                    //  if the sample is playing.
    {
      Serial.println("The sample is playing");
      Serial.print("Retriggering with velocity of ");
      Serial.println(velocity);
      this->fadeAndRetrigger(velocity);       // ...instigate a fadeAndRetrigger event.
    }
  } else                                      // if fadeRetrigger event is active. 
  {
    Serial.print("fadeAndRetrigger is active... replacing velocity value with ");
    Serial.println(velocity);
    m_retriggerVelocity = velocity;           // ...replace the velocity.
  }*/

  this->playWithVelocity(velocity);

  Serial.println("");
}

void Sample_Player::playWithVelocity(float velocity)
{
  //m_leftEnvelope->sustain(velocity);          // set the sustain level.
  //m_rightEnvelope->sustain(velocity);

  m_leftEnvelope->noteOn();                   // open the envelopes.
  m_rightEnvelope->noteOn();
  
  m_sdWav->play(m_sampleName.c_str());        // play the sample.
}

void Sample_Player::poll()          
{
  if(m_fadeAndRetriggerActive)                              // if fadeAndRetrigger is active
  {
    if(m_fadeAndRetriggerTimer == (_RETRIGGER_MS))          // if 6 ms have passed since the fadeAndRetrigger event started...
    {
      m_sdWav->stop();                                      // ...stop the sample.
      this->playWithVelocity(m_retriggerVelocity);          // ...play the sample.
      m_fadeAndRetriggerActive = false;                     // ...indicate that the fadeAndRetrigger event has ended.
    }
  }
}

void Sample_Player::fadeAndRetrigger(float velocity)
{
  m_retriggerVelocity = velocity;

  m_fadeAndRetriggerTimer = 0;                        // will the order of this and the noteOff events matter?
  
  m_leftEnvelope->noteOff();                          // trigger the envelope release stage.
  m_rightEnvelope->noteOff();

  m_fadeAndRetriggerActive = true;
}

void Sample_Player::assignMixerObjects(AudioMixer4 *leftMixer, AudioMixer4 *rightMixer, int leftMixerChannelNumber, int rightMixerChannelNumber)
{
  m_leftMixer = leftMixer;
  m_rightMixer = rightMixer;
  m_leftMixerChannelNumber = leftMixerChannelNumber;
  m_rightMixerChannelNumber = rightMixerChannelNumber;
}

void Sample_Player::assignEnvelopeObjects(AudioEffectEnvelope *leftEnvelope, AudioEffectEnvelope *rightEnvelope)
{
  m_leftEnvelope = leftEnvelope;
  m_rightEnvelope = rightEnvelope;

  this->initialiseEnvelopeObjects();
}

void Sample_Player::initialiseEnvelopeObjects()
{
  m_leftEnvelope->attack(_ATTACK_MS);
  m_rightEnvelope->attack(_ATTACK_MS);

  m_leftEnvelope->hold(_HOLD_MS);
  m_rightEnvelope->hold(_HOLD_MS);

  m_leftEnvelope->decay(_DECAY_MS);
  m_rightEnvelope->decay(_DECAY_MS);

  m_leftEnvelope->sustain(0.7);
  m_rightEnvelope->sustain(0.7);

  m_leftEnvelope->release(_RELEASE_MS);
  m_rightEnvelope->release(_RELEASE_MS); 
}

void Sample_Player::setSampleName(String sampleName)
{
  m_sampleName = sampleName;
}
