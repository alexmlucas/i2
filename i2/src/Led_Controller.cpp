#include "Led_Controller.h"

Led_Controller::Led_Controller()
{
  pinMode(m_muxLatchPin, OUTPUT);
  pinMode(m_muxClockPin, OUTPUT);
  pinMode(m_muxDataPin, OUTPUT);

    for(int i = 0; i < 3; i++)            // initialise mux LEDs
    {
        m_muxLedStates[i] = 0;
    }

    this->writeMuxLeds();
    digitalWrite(m_rhythm2LedPin, LOW);   // intialise directly wired rhythm 2 LED
}

void Led_Controller::poll()
{
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

void Led_Controller::writeMuxLeds()
{
    digitalWrite(m_muxLatchPin, LOW);

    for(int i = 0; i < 3; i++)
    {
        shiftOut(m_muxDataPin, m_muxClockPin, MSBFIRST, m_muxLedStates[i]);
    }

    digitalWrite(m_muxLatchPin, HIGH);
}