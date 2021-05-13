#include "Transport.h"

Transport::Transport(Midi_Clock *masterClock, Sequencer *sequencer, Led_Controller *ledController)
{
  m_masterClock = masterClock;
  m_sequencer = sequencer;
  m_ledController = ledController;
  m_playFlag = false;
  m_lastPlayFlag = false;
  m_newPlayEvent = false;
  m_recordFlag = false;
  m_eventFlag = false;
}

void Transport::poll()
{
  if(m_playFlag)                                                   
  {
    if(m_newPlayEvent)                                              // if play has just been activated...
    {                                             
      m_masterClock->_reset();                                      // ...reset the master clock timer.
      m_sequencer->playStep(0);                                     // ...play the first step.
      m_newPlayEvent = false;                                  
    }

    if(m_recordFlag)
    {
      if(m_eventFlag)
      {
        m_sequencer->quantiseTriggerEvent(m_track, m_velocity);     // ...forward to quantiser.
        m_eventFlag = false;                                        // ...reset the event flag.
        Serial.println("event");
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

void Transport::flipPlayState()
{
  if(!m_playFlag)                       // if currently off, log a new play event
  {
    m_newPlayEvent = true;
  }

  m_playFlag = !m_playFlag;
  m_masterClock->setRunFlag(m_playFlag);
  m_ledController->setPlayLed(m_playFlag);
}

void Transport::flipRecordState()
{
  m_recordFlag = !m_recordFlag;
  m_ledController->setRecordLed(m_recordFlag);
}