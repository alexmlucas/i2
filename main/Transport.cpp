#include "Transport.h"

Transport::Transport(Master_Clock* masterClock, Sequencer* sequencer)
{
  m_masterClock = masterClock;
  m_sequencer = sequencer;
  m_playFlag = true;
  m_lastPlayFlag = false;
  m_recordFlag = true;
}

void Transport::poll()
{
  if(m_playFlag)                                                   
  {
    if(m_playFlag != m_lastPlayFlag)                                // if play has just been activated...
    {                                             
      m_masterClock->resetTimer();                                  // ...reset the master clock timer.
      m_sequencer->playStep(0);                                     // ...play the first step.
      m_lastPlayFlag = m_playFlag;                                  
    }

    m_sequencer->poll();                                            // ask the sequencer to check if it needs to do anything.

    if(m_recordFlag)
    {
      for(int i = 0; i < 2; i++)
      {
        if(m_drumPadReadings[i] > 0)
        {
          m_sequencer->quantiseTriggerEvents(i, m_drumPadReadings[i]);      // forward to quantiser.
        }
      }      
    }
      
    m_masterClock->poll();                                          // poll the master clock. (maybe this first?)
  }
}

void Transport::logDrumPadReadings(double* drumPadReadings)
{
  m_drumPadReadings = drumPadReadings;
}

void Transport::forwardTriggerEvents(int trackNumber, double velocity)
{
  if(m_recordFlag && m_playFlag)
  {
    
  }
}
