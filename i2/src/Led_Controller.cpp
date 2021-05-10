#include "Led_Controller.h"

Led_Controller::Led_Controller(Midi_Clock* masterClock)
{
  m_masterClock = masterClock;

  pinMode(m_muxLatchPin, OUTPUT);
  pinMode(m_muxClockPin, OUTPUT);
  pinMode(m_muxDataPin, OUTPUT);
  pinMode(m_rhythm2LedPin, OUTPUT);
  pinMode(m_drumLedPins[0], OUTPUT);
  pinMode(m_drumLedPins[1], OUTPUT);
  pinMode(m_drumLedPins[2], OUTPUT);
  pinMode(m_drumLedPins[3], OUTPUT);

  for(int i = 0; i < 3; i++)              // initialise mux LEDs
  {
      m_muxLedStates[i] = 0;
  }

  m_playLedCurrentState = false;
  m_playStateActive = false;

  this->writeMuxLeds();
  digitalWrite(m_rhythm2LedPin, LOW);   // intialise directly wired LEDs
  analogWrite(m_drumLedPins[0], 0);
  analogWrite(m_drumLedPins[1], 0);
  analogWrite(m_drumLedPins[2], 0);
  analogWrite(m_drumLedPins[3], 0);
}

void Led_Controller::poll()
{
  this->updatePulse();

  /*if(m_playStateActive)
  {
    if(m_masterClock->isMidiTick8th())
    {
      m_playLedCurrentState = !m_playLedCurrentState;

      if(m_playLedCurrentState)
      {
        bitSet(m_muxLedStates[0], m_playLedBit);
        //m_playLedCurrentState = true;
      } else 
      {
        bitClear(m_muxLedStates[0], m_playLedBit);
        //m_playLedCurrentState = false;
      }

      this->writeMuxLeds();
    }
  }*/
}

void Led_Controller::assignKitPattMenuLeds(Led *kitPattMenuLeds[])
{
  for(int i = 0; i < 2; i++)
  {
    m_kitPattMenuLeds[i] = kitPattMenuLeds[i];
  }
}

void Led_Controller::setSpeedMenuLeds(int state)
{
  // depending on the incoming values, set or clear the appropriate bit
  switch(state)
  {
    case(0):
      bitSet(m_muxLedStates[2], m_slowMenuLedBit);
      bitClear(m_muxLedStates[2], m_fastMenuLedBit);
      break;
    case(1):
      bitClear(m_muxLedStates[2], m_slowMenuLedBit);
      bitClear(m_muxLedStates[2], m_fastMenuLedBit);
      break;
    case(2):
      bitClear(m_muxLedStates[2], m_slowMenuLedBit);
      bitSet(m_muxLedStates[2], m_fastMenuLedBit);
      break;
  }
  // write the changes;
  this->writeMuxLeds();
}

void Led_Controller::setKitPattNumLeds(int num1LedState, int num2LedState, int num3LedState, int num4LedState )
{
  // depending on the incoming values, set or clear the appropriate bit
  if(num1LedState == 1)
  {
    bitSet(m_muxLedStates[1], m_kitPattNum1LedBit);
  } else
  {
    bitClear(m_muxLedStates[1], m_kitPattNum1LedBit);
  }

  if(num2LedState == 1)
  {
    bitSet(m_muxLedStates[1], m_kitPattNum2LedBit);
  } else
  {
    bitClear(m_muxLedStates[1], m_kitPattNum2LedBit);
  }

  if(num3LedState == 1)
  {
    bitSet(m_muxLedStates[1], m_kitPattNum3LedBit);
  } else
  {
    bitClear(m_muxLedStates[1], m_kitPattNum3LedBit);
  }

  if(num4LedState == 1)
  {
    bitSet(m_muxLedStates[1], m_kitPattNum4LedBit);
  } else
  {
    bitClear(m_muxLedStates[1], m_kitPattNum4LedBit);
  }

  // write the changes;
  this->writeMuxLeds();
}

void Led_Controller::setKitPattMenuLeds(int state)
{
  if(state == 0)
  {
    bitSet(m_muxLedStates[1], m_kitMenuLedBit);
    bitClear(m_muxLedStates[1], m_pattMenuLedBit);
  } else
  {
    bitClear(m_muxLedStates[1], m_kitMenuLedBit);
    bitSet(m_muxLedStates[1], m_pattMenuLedBit);
  }
  // write the changes;
  this->writeMuxLeds();
}

void Led_Controller::setRhythmLed(int index, int state)
{
  if(index == 0)
  {
    digitalWrite(m_rhythm2LedPin, state);
    m_rhythmLedCurrentStates[0] = state;            
  }

  if(index == 1)
  {
    if(state == HIGH)
    {
      bitSet(m_muxLedStates[2], m_rhythm3Bit);      // This function differs from the one above as these LEDs are connected via a mux chip
    } else
    {
      bitClear(m_muxLedStates[2], m_rhythm3Bit);
    }
    m_rhythmLedCurrentStates[1] = state;
  }

  if(index == 2)
  {
    if(state == HIGH)
    {
      bitSet(m_muxLedStates[2], m_rhythm4Bit);
    } else
    {
      bitClear(m_muxLedStates[2], m_rhythm4Bit);
    }
    m_rhythmLedCurrentStates[2] = state;
  }

  if(index == 3)
  {
    if(state == HIGH)
    {
      bitSet(m_muxLedStates[2], m_rhythm5Bit);
    } else
    {
      bitClear(m_muxLedStates[2], m_rhythm5Bit);
    }
    m_rhythmLedCurrentStates[3] = state;
  }

  if(index == 4)
  {
    if(state == HIGH)
    {
      bitSet(m_muxLedStates[2], m_rhythm6Bit);
    } else
    {
      bitClear(m_muxLedStates[2], m_rhythm6Bit);
    }
    m_rhythmLedCurrentStates[4] = state;
  }

  if(index == 5)
  {
    if(state == HIGH)
    {
      bitSet(m_muxLedStates[2], m_rhythm7Bit);

    } else
    {
      bitClear(m_muxLedStates[2], m_rhythm7Bit);
    }
    m_rhythmLedCurrentStates[5] = state;
  }

  if(index == 6)
  {
    if(state == HIGH)
    {
      bitSet(m_muxLedStates[2], m_rhythm8Bit);
    } else 
    {
      bitClear(m_muxLedStates[2], m_rhythm8Bit);
    }
    m_rhythmLedCurrentStates[6] = state;
  }

  // write the changes;
  this->writeMuxLeds();
}

void Led_Controller::setTempoVolMenuLeds(int tempoLedState, int volLedState)
{
  // depending on the incoming values, set or clear the appropriate bit
  if(tempoLedState == 1)
  {
    bitSet(m_muxLedStates[0], m_tempoMenuLedBit);
  } else
  {
    bitClear(m_muxLedStates[0], m_tempoMenuLedBit);
  }

  if(volLedState == 1)
  {
    bitSet(m_muxLedStates[0], m_volMenuLedBit);
  } else
  {
    bitClear(m_muxLedStates[0], m_volMenuLedBit);
  }

  // write the changes;
  this->writeMuxLeds();
}

void Led_Controller::setTransportLeds(int playLedState, int recordLedState, int undoLedState)
{
  // depending on the incoming values, set or clear the appropriate bit
  if(playLedState == 1)
  {
    bitSet(m_muxLedStates[0], m_playLedBit);
    m_playLedCurrentState = true;
    m_playStateActive = true;

  } else
  {
    bitClear(m_muxLedStates[0], m_playLedBit);
    m_playLedCurrentState = false;
    m_playStateActive = false;

  }

  if(recordLedState == 1)
  {
    bitSet(m_muxLedStates[0], m_recordLedBit);
  } else
  {
    bitClear(m_muxLedStates[0], m_recordLedBit);
  }

  if(undoLedState == 1)
  {
    bitSet(m_muxLedStates[0], m_undoLedBit);
  } else
  {
    bitClear(m_muxLedStates[0], m_undoLedBit);
  }

  // write the changes;
  this->writeMuxLeds();
}

void Led_Controller::writeMuxLeds()
{
    digitalWrite(m_muxLatchPin, LOW);

    for(int i = 0; i < 3; i++)
    {
        shiftOut(m_muxDataPin, m_muxClockPin, MSBFIRST, m_muxLedStates[i]);
    }

    digitalWrite(m_muxLatchPin, HIGH);
}

void Led_Controller::pulseDrumLed(int ledNumber, int ledValue)
{
  m_drumLedPulseFlags[ledNumber] = true;                // set the pulse flag.
  analogWrite(m_drumLedPins[ledNumber], ledValue);      // switch on the led.
  m_drumLedPulseTimers[ledNumber] = 0;                  // reset the pulse timer.    
}

void Led_Controller::pulseRhythmLed(int index)
{
  m_rhythmLedPulseFlags[index] = true;                            // set the pulse flag.
  this->setRhythmLed(index, !m_rhythmLedCurrentStates[index]);    // light and flip the led state
  m_rhythmLedPulseTimers[index] = true;                           // reset the pulse timers
}


void Led_Controller::updatePulse()
{
  for(int i = 0; i < 4; i++)                          // update drum LED pulse
  {
    if(m_drumLedPulseFlags[i])                        // if flag is set
    {
      if(m_drumLedPulseTimers[i] > m_pulseLengthMs)   // if timer exceeded
      {
        analogWrite(m_drumLedPins[i], 0);             // switch off led at index
        m_drumLedPulseFlags[i] = false;               // reset flag
      }
    }
  }

  for(int i = 0; i < 8; i++)                          // update rhythm LED pulse
  {
    if(m_rhythmLedPulseFlags[i])
    {
      if(m_rhythmLedPulseTimers[i] > m_pulseLengthMs)
      {
        this->setRhythmLed(i, !m_rhythmLedCurrentStates[i]);
        m_rhythmLedPulseFlags[i] = false;
      }
    }
  }
}