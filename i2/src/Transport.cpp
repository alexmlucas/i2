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
  int quantisedStep = -1;                                           // initialised with null value
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
        quantisedStep = m_sequencer->getQuantisedStep();
        m_sequencer->setTriggerEvent(m_track, m_velocity, quantisedStep);     // ...forward to quantiser.
        this->collectUndoEvent(0, quantisedStep, m_track);                    // ...log undo event.
        m_eventFlag = false;                                                  // ...reset the event flag.
        Serial.println("event");

        /*if(m_captureUndoFlag)
        {
          // add to undo array here.
        }*/
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

void Transport::resetUndoCollector()
{
  m_undoIndexCounter = 0;                 // reset counter
  
  for(int i = 0; i < 8; i++)             // wipe past data
  {
    for(int ii = 0; ii < 2; ii++)
    {
      m_undoCollector[i][ii] = -1;
    }
  }
}

void Transport::collectUndoEvent(int patternNumber, int sequenceIndex, int trackNumber)
{
  m_undoCollector[m_undoIndexCounter][0] = sequenceIndex;
  m_undoCollector[m_undoIndexCounter][1] = trackNumber;
  m_undoIndexCounter++;
}

void Transport::printUndoData()
{
  for(int i = 0; i < 8; i++)             // wipe past data
  {
    for(int ii = 0; ii < 2; ii++)
    {
      Serial.print(m_undoCollector[i][ii]);
      Serial.print(" ");
    }

    Serial.println();
  }
}

void Transport::undoRecordedData()
{
  for(int i = 0; i < 8; i++)            
  {
    if(m_undoCollector[i][0] > -1)       // if not a null value...
    {
      m_sequencer->removeStepData(m_undoCollector[i][0], m_undoCollector[i][1]);   // ...remove data from pattern
    }
  }
}