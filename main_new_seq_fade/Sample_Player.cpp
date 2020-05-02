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
  if(!m_fadeAndRetriggerActive)               // if a fadeAndRetrigger event is not active...
  {
    Serial.println("fadeAndRetrigger is not Active");
    if(!m_sdWav->isPlaying())                 // if the sample is not playing.
    {
      Serial.println("The sample is not playing");
      this->playWithVelocity(velocity);       // ...play the sample.
    } else                                    //  else the sample is playing. therefore...
    {
      Serial.println("The sample is playing");
      this->fadeAndRetrigger(velocity);       // ...instigate a fadeAndRetrigger event.
    }
  } else                                      // else a fadeAndRetrigger event is active. 
  {
    Serial.print("fadeAndRetrigger is active... replacing velocity value with ");
    Serial.println(velocity);
    m_retriggerVelocity = velocity;           // ...replace the velocity.
  }

  //this->playWithVelocity(velocity);

  Serial.println("");
}

void Sample_Player::playWithVelocity(float velocity)
{
  //m_leftEnvelope->sustain(velocity);          // set the sustain level.
  //m_rightEnvelope->sustain(velocity);

  //m_leftEnvelope->noteOn();                   // open the envelopes.
  //m_rightEnvelope->noteOn();

  m_leftMixer->gain(m_leftMixerChannelNumber, velocity);
  m_rightMixer->gain(m_rightMixerChannelNumber, velocity);

  m_sdWav->play(m_sampleName.c_str());          // play the sample.
}

void Sample_Player::poll()          
{
  if(m_fadeAndRetriggerActive)                              // if fadeAndRetrigger is active
  {
    if(m_fadeAndRetriggerTimer == FADE_OUT_MS + 1)          // if 1ms has passed since the fade finished...
    {
      m_sdWav->stop();                                      // ...stop the sample.
    }

    if(m_fadeAndRetriggerTimer == (FADE_OUT_MS + 2))        // if 2ms have passed since the fade finished...
    {
      m_leftFade->fadeIn(FADE_IN_MS);                       // ...fade in.
      m_rightFade->fadeIn(FADE_IN_MS);
    }

    if(m_fadeAndRetriggerTimer == (FADE_OUT_MS + 3))        // if 3ms have passed since the fade finished...
    {
     this->playWithVelocity(m_retriggerVelocity);          // ...retrigger the sample.
      m_fadeAndRetriggerActive = false;                    // ...indicate that the fadeAndRetrigger event has ended.
    }
  }
}

void Sample_Player::fadeAndRetrigger(float velocity)
{
  m_retriggerVelocity = velocity;

  m_fadeAndRetriggerTimer = 0;                              // will the order of this and the noteOff events matter?
  
  m_leftFade->fadeOut(FADE_OUT_MS);                         // trigger the fade out.
  m_rightFade->fadeOut(FADE_OUT_MS);

  m_fadeAndRetriggerActive = true;
}

void Sample_Player::assignMixerObjects(AudioMixer4 *leftMixer, AudioMixer4 *rightMixer, int leftMixerChannelNumber, int rightMixerChannelNumber)
{
  m_leftMixer = leftMixer;
  m_rightMixer = rightMixer;
  m_leftMixerChannelNumber = leftMixerChannelNumber;
  m_rightMixerChannelNumber = rightMixerChannelNumber;
}

void Sample_Player::assignFadeObjects(AudioEffectFade *leftFade, AudioEffectFade *rightFade)
{
  m_leftFade = leftFade;
  m_rightFade = rightFade;
}

void Sample_Player::setSampleName(String sampleName)
{
  m_sampleName = sampleName;
}
