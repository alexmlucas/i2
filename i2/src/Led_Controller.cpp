#include "Led_Controller.h"

Led_Controller::Led_Controller()
{
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

  if(m_flashTimer > FLASH_TIME_MS)    // if flash time exceeded
  {
    if(m_kitPattLedFlashFlag)         // check to see if flash flag is set
    {
      if(m_kitPattLedState == HIGH)   // then flip
      {
        bitClear(m_muxLedStates[1], m_kitPattNumLedBits[m_currentKitPatt]);
        m_kitPattLedState = LOW;
      } else
      {
        bitSet(m_muxLedStates[1], m_kitPattNumLedBits[m_currentKitPatt]);
        m_kitPattLedState = HIGH;
      }

      this->writeMuxLeds();
    }

    m_flashTimer = 0;
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

void Led_Controller::setKitPattNumLeds(int index)
{
  switch(index)
  {
    case(0):
      bitSet(m_muxLedStates[1], m_kitPattNum1LedBit);
      bitClear(m_muxLedStates[1], m_kitPattNum2LedBit);
      bitClear(m_muxLedStates[1], m_kitPattNum3LedBit);
      bitClear(m_muxLedStates[1], m_kitPattNum4LedBit);
      m_currentKitPatt = 0;
      m_kitPattLedFlashFlag = false;
      break;
    case(1):
      bitClear(m_muxLedStates[1], m_kitPattNum1LedBit);
      bitSet(m_muxLedStates[1], m_kitPattNum2LedBit);
      bitClear(m_muxLedStates[1], m_kitPattNum3LedBit);
      bitClear(m_muxLedStates[1], m_kitPattNum4LedBit);
      m_currentKitPatt = 1;
      m_kitPattLedFlashFlag = false;
      break;
    case(2):
      bitClear(m_muxLedStates[1], m_kitPattNum1LedBit);
      bitClear(m_muxLedStates[1], m_kitPattNum2LedBit);
      bitSet(m_muxLedStates[1], m_kitPattNum3LedBit);
      bitClear(m_muxLedStates[1], m_kitPattNum4LedBit);
      m_currentKitPatt = 2;
      m_kitPattLedFlashFlag = false;
      break;
    case(3):
      bitClear(m_muxLedStates[1], m_kitPattNum1LedBit);
      bitClear(m_muxLedStates[1], m_kitPattNum2LedBit);
      bitClear(m_muxLedStates[1], m_kitPattNum3LedBit);
      bitSet(m_muxLedStates[1], m_kitPattNum4LedBit);
      m_currentKitPatt = 3;
      m_kitPattLedFlashFlag = false;
      break;
  }

  this->writeMuxLeds();   // write the changes;
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

void Led_Controller::setTempoVolMenuLeds(int state)
{
 if(state == 0)
  {
    bitSet(m_muxLedStates[0], m_tempoMenuLedBit);
    bitClear(m_muxLedStates[0], m_volMenuLedBit);
  } else
  {
    bitClear(m_muxLedStates[0], m_tempoMenuLedBit);
    bitSet(m_muxLedStates[0], m_volMenuLedBit);
  }
  // write the changes;
  this->writeMuxLeds();
}

void Led_Controller::setPlayLed(int state)
{
  if(state == HIGH)
  {
    bitSet(m_muxLedStates[0], m_playLedBit);
  } else if (state == LOW)
  {
    bitClear(m_muxLedStates[0], m_playLedBit);
  }

  this->writeMuxLeds();
}

void Led_Controller::setRecordLed(int state)
{
  if(state == HIGH)
  {
    bitSet(m_muxLedStates[0], m_recordLedBit);
  } else if (state == LOW)
  {
    bitClear(m_muxLedStates[0], m_recordLedBit);
  }

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
  m_rhythmLedPulseTimers[index] = 0;                              // reset the pulse timers
}

void Led_Controller::updatePulse()
{
  for(int i = 0; i < 4; i++)                          // update drum LED pulse
  {
    if(m_drumLedPulseFlags[i])                        // if flag is set
    {
      if(m_drumLedPulseTimers[i] > PULSE_LENGTH_MS)   // if timer exceeded
      {
        analogWrite(m_drumLedPins[i], 0);             // switch off led at index
        m_drumLedPulseFlags[i] = false;               // reset flag
      }
    }
  }

  for(int i = 0; i < 7; i++)                          // update rhythm LED pulse
  {
    if(m_rhythmLedPulseFlags[i] == true)
    {
      if(m_rhythmLedPulseTimers[i] > PULSE_LENGTH_MS)
      {
        this->setRhythmLed(i, !m_rhythmLedCurrentStates[i]);
        m_rhythmLedPulseFlags[i] = false;
      }
    }
  }

  if(m_undoLedPulseFlag)
  {
    //Serial.println(m_undoLedPulseTimer);
    if(m_undoLedPulseTimer >= PULSE_LENGTH_MS)
    {
      bitClear(m_muxLedStates[0], m_undoLedBit);
      this->writeMuxLeds();
      m_undoLedPulseFlag = false;
    }
  }
}

void Led_Controller::pulseUndoLed()
{
  bitSet(m_muxLedStates[0], m_undoLedBit);
  this->writeMuxLeds();
  m_undoLedPulseTimer = 0;
  m_undoLedPulseFlag = true;
}

void Led_Controller::setUndoLed(int state)
{
  if(state == HIGH)
  {
    bitSet(m_muxLedStates[0], m_undoLedBit);
  } else if (state == LOW)
  {
    bitClear(m_muxLedStates[0], m_undoLedBit);
  }

  this->writeMuxLeds();
}

void Led_Controller::setKitPattFlashing(int state)
{
  m_kitPattLedFlashFlag = state;
  m_flashTimer = 0;
  this->writeMuxLeds();
}