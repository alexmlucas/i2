#include "Rhythm_Generator.h"

// half speed is 8ths.
// standard speed is at 16ths.
// double speed is 32nds.

Rhythm_Generator::Rhythm_Generator(Midi_Clock* rhythmClock, Transport* transport, Sample_Player* samplePlayers) 
{
  m_rhythm = 128;
  m_rhythmClock = rhythmClock;
  m_transport = transport;
  m_samplePlayers = samplePlayers;
  m_velocity = 0;
  m_currentStep = 0;
  m_isPlayingFlag = false;
  m_lastMidiTick = -1;
  m_playbackSpeed = 1;
}

void Rhythm_Generator::printRhythm()
{
  Serial.print(int(bitRead(m_rhythm, 7)));
  Serial.print(" ");

  Serial.print(int(bitRead(m_rhythm, 6)));
  Serial.print(" ");

  Serial.print(int(bitRead(m_rhythm, 5)));
  Serial.print(" ");

  Serial.print(int(bitRead(m_rhythm, 4)));
  Serial.print(" ");

  Serial.print(int(bitRead(m_rhythm, 3)));
  Serial.print(" ");

  Serial.print(int(bitRead(m_rhythm, 2)));
  Serial.print(" ");

  Serial.print(int(bitRead(m_rhythm, 1)));
  Serial.print(" ");

  Serial.println(int(bitRead(m_rhythm, 0)));
}

void Rhythm_Generator::triggerRhythm(int track, float velocity)
{
  m_track = track;
  m_velocity = velocity;
  m_isPlayingFlag = true;
  m_rhythmClock->_reset();
  m_lastMidiTick = -1;
  m_currentStep = 0;
}

void Rhythm_Generator::poll()
{
  if(m_isPlayingFlag)
  {
    int currentMidiTick = m_rhythmClock->getMidiTick();

    if(currentMidiTick != m_lastMidiTick)                               // if this is a new midi tick...
    {
      int invertedStep = abs(m_currentStep - 7);
      bool triggerFlag = bool(bitRead(m_rhythm, invertedStep));
      bool midiTickOnStepFlag = false;
      
      switch(m_playbackSpeed)                                           // ...set the midiTickOnStepFlag according to the playback speed.
      {
        case 0:
          midiTickOnStepFlag = m_rhythmClock->isMidiTick8th();
          break;
        case 1:
          midiTickOnStepFlag = m_rhythmClock->isMidiTick16th();
          break;
        case 2:
          midiTickOnStepFlag = m_rhythmClock->isMidiTick32nd();             
          break;
      }

      if(midiTickOnStepFlag)                                            // if the clock's midi tick is on an step we're interested in...
      {
        if(triggerFlag)                                                 // if the rhythm generator step is 'on'
        {
          m_samplePlayers[m_track].processTriggerEvent(m_velocity);     // ...trigger the sample 
          m_transport->logTriggerEvent(m_track, m_velocity);            // ...log the trigger event with the transport
        }

        this->advance();                                                // advance the step counter. (should set play to off after 7th step!)
      }
      m_lastMidiTick = currentMidiTick;                                 // capture the midiTick value.
    }
  }
}

void Rhythm_Generator::advance()                                                         // advance to the next step
{
  if(m_currentStep < (RHYTHM_LENGTH - 1))
  {       
    m_currentStep++;
  } else
  {
    m_isPlayingFlag = false;
    m_currentStep = 0;
  }
}
