#include "Sequencer.h"

Sequencer::Sequencer(Master_Clock* masterClock, Sample_Player* samplePlayers)
{
  m_masterClock = masterClock;
  m_currentStep = 0;
  m_lastMidiTick = -1;
  m_samplePlayers = samplePlayers;
}

// ### Play the Current Step ###
void Sequencer::playStep()
{
  for(int i = 0; i <= (TRACK_AMOUNT - 1); i++)                                    // interate through tracks.       
  {                      
    float velocity = patterns[m_currentPattern].m_steps[m_currentStep][i];        // get the velocity value at the index.

    if(velocity > 0)                                                              // if velocity is above 0...
    {
      m_samplePlayers[i].processTriggerEvent(velocity);                        // ...play the sample.
    }
  }
}

// ### Play the Step at the Index Number Provided ###
void Sequencer::playStep(int stepNumber)
{
  for(int i = 0; i <= (TRACK_AMOUNT - 1); i++)                                    // interate through tracks.       
  {                      
    float velocity = patterns[m_currentPattern].m_steps[stepNumber][i];           // get the velocity value at the index.

    if(velocity > 0)                                                              // if velocity is above 0...
    {                          
      m_samplePlayers[i].processTriggerEvent(velocity);                          // ...play the sample.
    }
  }
}

void Sequencer::advance()                                                         // advance to the next step
{
  if(m_currentStep < (PATTERN_LENGTH - 1))
  {       
    m_currentStep++;
  } else
  {
    m_currentStep = 0;
  }
}

void Sequencer::addQueuedEvents()                                                 // add queued events to sequence...
{
  for(int i = 0; i <= (TRACK_AMOUNT - 1); i++)                                    // interate through tracks.       
  {
    double velocity = m_quantiseQueue[i];
                     
    if(velocity > 0)                                                              // if velocity is above 0...
    {
      patterns[m_currentPattern].m_steps[m_currentStep][i] = velocity;            // add the value to the sequence                            
      m_quantiseQueue[i] = 0;                                                     // reset the value.              
    }
  }
}

void Sequencer::quantiseTriggerEvents(int trackNumber, double velocity)           // ### this function will add the trigger events to the queue ###
{
  int quantisedStep = this->getQuantisedStep();                                   // get the quantised step

  if(quantisedStep == m_currentStep)
  {
    Serial.println("adding immediately");
    patterns[m_currentPattern].m_steps[quantisedStep][trackNumber] = velocity;    // ...add to pattern immediately - this step won't play again until the next pattern iteration.
  } else                                                                          // else, it has been quantised to the next step, therefore...
  {
    Serial.println("adding to queue");
    m_quantiseQueue[trackNumber] = velocity;                                      // ...add to the queue.
  }
}

int Sequencer::getQuantisedStep()
{
  int quantiseTick = m_masterClock->getMidiTick() % QUANTISE_MODULO;              // There are three midi ticks per 32nd step. which one are we on?...
  float quantiseFloat = quantiseTick * 0.333;                                     // Divide the value by three to get a float ready for rounding.
  int quantisedStep = round(m_currentStep + quantiseFloat);                       // get the quantised step by adding the float to the current step, then rounding.
  
  if(quantisedStep == 32)                                                         // accomodate wrap-around from 31 to 0
  {                                          
    quantisedStep = 0;
  }
  
  return quantisedStep;    
}

void Sequencer::poll()
{
  int currentMidiTick = m_masterClock->getMidiTick();       // get the current midi tick value

  if(currentMidiTick != m_lastMidiTick)                     // if this is a new midi tick.
  { 
    if(m_masterClock->isMidiTick32nd())                     // if is a 32nd tick...
    {
      this->advance();                                      // ...advance the sequence.
      this->playStep();                                     // ...play the step.
      this->addQueuedEvents();                              // ...add queued record quantise events.
    }

    m_lastMidiTick = currentMidiTick;                       // capture the midiTick value.
  }
}
        
