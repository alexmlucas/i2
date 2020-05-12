#include "Transport.h"

Transport::Transport(Midi_Clock* masterClock, Sequencer* sequencer)
{
  m_masterClock = masterClock;
  m_sequencer = sequencer;
  m_playFlag = true;
  m_lastPlayFlag = false;
  m_recordFlag = true;
  m_eventFlag = false;
}

void Transport::poll()
{
  if(m_playFlag)                                                   
  {
    if(m_playFlag != m_lastPlayFlag)                                // if play has just been activated...
    {                                             
      m_masterClock->_reset();                                      // ...reset the master clock timer.
      m_sequencer->playStep(0);                                     // ...play the first step.
      m_lastPlayFlag = m_playFlag;                                  
    }

    if(m_recordFlag)
    {
      if(m_eventFlag)
      {
        m_sequencer->quantiseTriggerEvent(m_track, m_velocity);     // ...forward to quantiser.
        m_eventFlag = false;                                        // ...reset the event flag.
      }
    }
  }
}

void Transport::logTriggerEvent(int track, float velocity)
{
  m_track = track;
  m_velocity = velocity;
  m_eventFlag = true;
}
