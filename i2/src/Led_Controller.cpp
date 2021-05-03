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

void Led_Controller::poll()       // used solely to flash the play led when engaged
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

void Led_Controller::setKitPattMenuLeds(int kitLedState, int pattLedState)
{
  // depending on the incoming values, set or clear the appropriate bit
  if(kitLedState == 1)
  {
    bitSet(m_muxLedStates[1], m_kitMenuLedBit);
  } else
  {
    bitClear(m_muxLedStates[1], m_kitMenuLedBit);
  }

  if(pattLedState == 1)
  {
    bitSet(m_muxLedStates[1], m_pattMenuLedBit);
  } else
  {
    bitClear(m_muxLedStates[1], m_pattMenuLedBit);
  }

  // write the changes;
  this->writeMuxLeds();
}

void Led_Controller::setSlowFastMenuLeds(int slowLedState, int fastLedState)
{
  // depending on the incoming values, set or clear the appropriate bit
  if(slowLedState == 1)
  {
    bitSet(m_muxLedStates[2], m_slowMenuLedBit);
  } else
  {
    bitClear(m_muxLedStates[2], m_slowMenuLedBit);
  }

  if(fastLedState == 1)
  {
    bitSet(m_muxLedStates[2], m_fastMenuLedBit);
  } else
  {
    bitClear(m_muxLedStates[2], m_fastMenuLedBit);
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

void Led_Controller::setRhythmNumLeds(int num2LedState, int num3LedState, int num4LedState, int num5LedState, int num6LedState, int num7LedState, int num8LedState)
{
  // depending on the incoming values, set or clear the appropriate bit
  if(num2LedState == 1)
  {
    digitalWrite(m_rhythm2LedPin, HIGH);
  } else
  {
    digitalWrite(m_rhythm2LedPin, LOW);
  }

  if(num3LedState == 1)
  {
    bitSet(m_muxLedStates[2], m_rhythm3Bit);
  } else
  {
    bitClear(m_muxLedStates[2], m_rhythm3Bit);
  }

  if(num4LedState == 1)
  {
    bitSet(m_muxLedStates[2], m_rhythm4Bit);
  } else
  {
    bitClear(m_muxLedStates[2], m_rhythm4Bit);
  }

  if(num5LedState == 1)
  {
    bitSet(m_muxLedStates[2], m_rhythm5Bit);
  } else
  {
    bitClear(m_muxLedStates[2], m_rhythm5Bit);
  }

  if(num6LedState == 1)
  {
    bitSet(m_muxLedStates[2], m_rhythm6Bit);
  } else
  {
    bitClear(m_muxLedStates[2], m_rhythm6Bit);
  }

  if(num7LedState == 1)
  {
    bitSet(m_muxLedStates[2], m_rhythm7Bit);
  } else
  {
    bitClear(m_muxLedStates[2], m_rhythm7Bit);
  }

  if(num8LedState == 1)
  {
    bitSet(m_muxLedStates[2], m_rhythm8Bit);
  } else
  {
    bitClear(m_muxLedStates[2], m_rhythm8Bit);
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

void Led_Controller::setDrumLeds(int drumPad0LedValue, int drumPad1LedValue, int drumPad2LedValue, int drumPad3LedValue)
{
  analogWrite(m_drumLedPins[0], drumPad0LedValue);
  analogWrite(m_drumLedPins[1], drumPad1LedValue);
  analogWrite(m_drumLedPins[2], drumPad2LedValue);
  analogWrite(m_drumLedPins[3], drumPad3LedValue);
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

void Led_Controller::setPulseDrumLed(int ledNumber, int ledValue)
{
  Serial.println(ledNumber);
  m_drumLedPulseFlags[ledNumber] = true;                      // set the pulse flag.
  analogWrite(m_drumLedPins[ledNumber], ledValue);    // switch on the led.
  drumLedPulseTimers[ledNumber] = 0;                  // reset the pulse timer.    
}

void Led_Controller::updatePulse()
{
  for(int i = 0; i < 4; i++)
  {
    if(m_drumLedPulseFlags[i])                        // if flag is set
    {
      if(drumLedPulseTimers[i] > m_pulseLengthMs)     // if timer exceeded
      {
        analogWrite(m_drumLedPins[i], 0);             // switch off led at index
        m_drumLedPulseFlags[i] = false;               // reset flag
        Serial.print("switching off");
        Serial.println(i);
      }
    }
  }
}
