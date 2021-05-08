#include "Rhythm_Generator.h"

// half speed is 8ths.
// standard speed is at 16ths.
// double speed is 32nds.

Rhythm_Generator::Rhythm_Generator(Midi_Clock* rhythmClock, Transport* transport, Sample_Player* samplePlayers) 
{
  m_rhythmValue = 128;
  m_rhythmClock = rhythmClock;
  m_transport = transport;
  m_samplePlayers = samplePlayers;
  m_velocity = 0;
  m_currentStep = 0;
  m_isPlayingFlag = false;
  m_lastMidiTick = -1;
  m_speed = 1;
}

void Rhythm_Generator::poll()
{
  if(m_isPlayingFlag)
  {
    int currentMidiTick = m_rhythmClock->getMidiTick();

    if(currentMidiTick != m_lastMidiTick)                             // if this is a new midi tick...
    {
      int invertedStep = abs(m_currentStep - 7);                      // convert step to appropriate bit
      bool triggerFlag = bool(bitRead(m_rhythmValue, invertedStep));  // read bit.
      bool midiTickOnStepFlag = false;                                // reset flag to play when on a new MIDI tick.
      
      switch(m_speed)                                                 // ...set the midiTickOnStepFlag according to the playback speed.
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
          Serial.println("triggering");
          m_samplePlayers[m_track].processTriggerEvent(m_velocity);     // ...trigger the sample 
          m_transport->logTriggerEvent(m_track, m_velocity);            // ...log the trigger event with the transport
          m_ledController->pulseDrumLed(m_track, m_velocity * 256);     // pulse the drum LED
        }

        if(m_currentStep != 0)                                              // Pulse rhythm LED if not step 0
        {
          m_ledController->pulseRhythmLed(m_currentStep - 1);               // tweak the index number slightly                      
        }

        this->advance();                                                // advance the step counter. (should set play to off after 7th step!)
      }
      m_lastMidiTick = currentMidiTick;                                 // capture the midiTick value.
    }
  }
}

void Rhythm_Generator::setLedController(Led_Controller *ledController)
{
    m_ledController = ledController;
}

void Rhythm_Generator::setDisplayController(Display_Controller *displayController)
{
    m_displayController = displayController;
}

void Rhythm_Generator::setRhythm(int rhythmValue)
{
  m_displayController->displayNumber(rhythmValue);
  m_rhythmValue = 128 + rhythmValue;
  this->displayRhythm();
}

void Rhythm_Generator::flipRhythmBit(int bitIndex)
{
  //int modifiedBitIndex = abs(bitIndex - 7);
  
  if(int(bitRead(m_rhythmValue, bitIndex)))
  {
    bitClear(m_rhythmValue, bitIndex);
  } else
  {
    bitSet(m_rhythmValue, bitIndex);
  }

  this->displayRhythm();
}

void Rhythm_Generator::displayRhythm()
{
  m_ledController->setRhythmLed(0, int(bitRead(m_rhythmValue, 6)));
  m_ledController->setRhythmLed(1, int(bitRead(m_rhythmValue, 5)));
  m_ledController->setRhythmLed(2, int(bitRead(m_rhythmValue, 4)));
  m_ledController->setRhythmLed(3, int(bitRead(m_rhythmValue, 3)));
  m_ledController->setRhythmLed(4, int(bitRead(m_rhythmValue, 2)));
  m_ledController->setRhythmLed(5, int(bitRead(m_rhythmValue, 1)));
  m_ledController->setRhythmLed(6, int(bitRead(m_rhythmValue, 0)));

  Serial.print(int(bitRead(m_rhythmValue, 7)));
  Serial.print(" ");
  Serial.print(int(bitRead(m_rhythmValue, 6)));
  Serial.print(" ");
  Serial.print(int(bitRead(m_rhythmValue, 5)));
  Serial.print(" ");
  Serial.print(int(bitRead(m_rhythmValue, 4)));
  Serial.print(" ");
  Serial.print(int(bitRead(m_rhythmValue, 3)));
  Serial.print(" ");
  Serial.print(int(bitRead(m_rhythmValue, 2)));
  Serial.print(" ");
  Serial.print(int(bitRead(m_rhythmValue, 1)));
  Serial.print(" ");
  Serial.println(int(bitRead(m_rhythmValue, 0)));
}

void Rhythm_Generator::triggerRhythm(int track, float velocity)
{
  m_track = track;                // the track to play
  m_velocity = velocity;          // the velocity to play the sample
  m_isPlayingFlag = true;         // we're now playing
  m_rhythmClock->_reset();        // reset the clock used by the rhythm generator
  m_lastMidiTick = -1;            // null value for last tick
  m_currentStep = 0;              // reset the current step.
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

void Rhythm_Generator::decrementSpeed()
{
  if(m_speed > 0)                                 // decrement looks more natural on the UI
  {
    m_speed--;
  } else
  {
    m_speed = 2;
  }
  m_ledController->setSpeedMenuLeds(m_speed);
}
