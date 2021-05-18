#include "Sample_Player.h"

/*Sample_Player::Sample_Player(AudioPlaySdWav *sdWav)
{
  m_sdWav = sdWav;
  m_fadeAndRetriggerActive = false;
  m_stopRequestMade = false;
  m_fadeInRequestMade = false;
}*/

Sample_Player::Sample_Player(AudioPlaySdWav *sdWav, int kitIndex, int sampleIndex)
{
  m_sdWav = sdWav;
  m_fadeAndRetriggerActive = false;
  m_stopRequestMade = false;
  m_fadeInRequestMade = false;
  m_sampleIndex = sampleIndex;
  m_kitIndex = kitIndex;
  m_sampleName = this->buildFilename(kitIndex, sampleIndex);
}

String Sample_Player::buildFilename(int kitIndex, int sampleIndex)
{
  String filename = String(kitIndex);        // build filename & location
  filename += "/";
  filename += String(sampleIndex);
  filename += ".wav";
  Serial.println(filename);
  return filename;
}

void Sample_Player::setKit(int kitIndex)
{
  m_kitIndex = kitIndex;
  m_sampleName = this->buildFilename(m_kitIndex, m_sampleIndex);
}

void Sample_Player::processTriggerEvent(float velocity)
{
  if(!m_fadeAndRetriggerActive)               // if a fadeAndRetrigger event is not active...
  {
    if(!m_sdWav->isPlaying())                 // if the sample is not playing.
    {
      this->playWithVelocity(velocity);       // ...play the sample.
    } else                                    //  else the sample is playing. therefore...
    {
      Serial.println("fade and retrigger");
      this->fadeAndRetrigger(velocity);       // ...instigate a fadeAndRetrigger event.
    }
  } else                                      // else a fadeAndRetrigger event is active. 
  {
    m_retriggerVelocity = velocity;           // ...replace the velocity.
  }
}

void Sample_Player::playWithVelocity(float velocity)
{
  Serial.println(m_sampleName);
  this->setMixerLevels(velocity);                           // set the mixer levels.
  m_sdWav->play(m_sampleName.c_str());                      // play the sample.
}

void Sample_Player::setMixerLevels(float velocity)
{
  m_leftMixer->gain(m_leftMixerChannelNumber, velocity);
  m_rightMixer->gain(m_rightMixerChannelNumber, velocity);
}

void Sample_Player::fadeAndRetrigger(float velocity)
{
  m_retriggerVelocity = velocity;

  m_fadeAndRetriggerTimer = 0;                              // will the order of this and the noteOff events matter?

  m_leftFade->fadeOut(FADE_OUT_MS);                         // trigger the fade out.
  m_rightFade->fadeOut(FADE_OUT_MS);

  //Serial.println("Fading out sample at address: ");
  //Serial.println(int(this));

  m_fadeAndRetriggerActive = true;
}

void Sample_Player::poll()          
{
  if(m_fadeAndRetriggerActive)                              // if fadeAndRetrigger is active
  {
    if(m_fadeAndRetriggerTimer >= FADE_OUT_MS + 1)          // if 1ms has passed since the fade finished...
    {
      if(!m_stopRequestMade)                                // if a stop request hasn't already been made during this event.
      {
        m_sdWav->stop();                                    // ...stop the sample.
        m_stopRequestMade = true;                           // ...log the request.
      }
    }

    if(m_fadeAndRetriggerTimer >= (FADE_OUT_MS + 2))        // if 2ms have passed since the fade finished...
    {
      if(!m_fadeInRequestMade)                              // if a fadeIn reqest hasn't already been made during this event.
      {
        m_leftFade->fadeIn(FADE_IN_MS);                     // ...fade in.
        m_rightFade->fadeIn(FADE_IN_MS);
        //Serial.println("Fading in sample at address: ");
        //Serial.println(int(this));
        m_fadeInRequestMade = true;                         // ...log that the request.
      }
    }

    if(m_fadeAndRetriggerTimer >= (FADE_OUT_MS + 3))        // if 3ms have passed since the fade finished...
    {
      this->playWithVelocity(m_retriggerVelocity);          // ...retrigger the sample.
      m_fadeAndRetriggerActive = false;                     // ...indicate that the fadeAndRetrigger event has ended.
      m_stopRequestMade = false;                            // ...reset the flags
      m_fadeInRequestMade = false;
    }
  }
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