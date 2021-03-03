#include "Input_Manager.h"

Input_Manager::Input_Manager()
{
    pinMode(m_rhythmPotPin, INPUT);
    pinMode(m_muxAInPin, INPUT);
    pinMode(m_muxBInPin, INPUT);
    pinMode(m_muxCInPin, INPUT);
    pinMode(m_muxSelPin0, OUTPUT);
    pinMode(m_muxSelPin1, OUTPUT);
    pinMode(m_muxSelPin2, OUTPUT);

    for(int i = 0; i < 8; i++)              // initialise variables.
    {
        m_muxAButtonStates[i] = 0;
        m_muxBButtonStates[i] = 0;
        m_muxCButtonStates[i] = 0;
        m_muxAButtonEventTimes[i] = 0;
        m_muxBButtonEventTimes[i] = 0;
        m_muxCButtonEventTimes[i] = 0;
    }

    m_echoPotLastValue = 0;
    m_muxReadTimer = 0;
    m_muxReadIndex = 0;

    m_readMuxChannel = false;
    m_changeMuxChannel = true;
}

void Input_Manager::poll()
{
    this->readMuxs();
    this->readDirectPot();
}

void Input_Manager::readMuxs()
{
    if(m_changeMuxChannel == true)
    {
        this->setSensor(m_muxReadIndex);
        m_changeMuxChannel = false;
        m_muxReadTimer = 0;
    }

    if(m_muxReadTimer > MUX_READ_DELAY_US)
    {
        // ** mux A **
        int muxACurrentValue = digitalRead(m_muxAInPin); 
        
        if(muxACurrentValue != m_muxAButtonStates[m_muxReadIndex])                   // has something changed?
        {
            // check to see if the debounce time has been exceeded
            if((millis() - m_muxAButtonEventTimes[m_muxReadIndex]) > DEBOUNCE_MS)    // debounce
            {
                m_muxAButtonStates[m_muxReadIndex] = muxACurrentValue;           // update array
                m_muxAButtonEventTimes[m_muxReadIndex] = millis();               // update event time

                if(m_muxAButtonStates[m_muxReadIndex] == 1)
                {
                    // button on
                    Serial.print("muxA button ");
                    Serial.print(m_muxReadIndex);
                    Serial.println("on.");

                } else if(m_muxAButtonStates[m_muxReadIndex] == 0)
                {
                    // button off 
                    Serial.print("muxA button ");
                    Serial.print(m_muxReadIndex);
                    Serial.println("off.");
                }
            }
        }
        
        // ** mux B **
        if(m_muxReadIndex == 4)                                              // handle pot differently
        {
            int muxBCurrentValue = analogRead(m_muxBInPin);

            // check to see if the pot value has changed.
            if(muxBCurrentValue <= (m_echoPotLastValue - POT_NOISE_FILTER) || muxBCurrentValue >= (m_echoPotLastValue + POT_NOISE_FILTER))
            {
                // the pot value has changed.
                m_echoPotLastValue = muxBCurrentValue;
                Serial.print("echo pot value = ");
                Serial.println(m_echoPotLastValue);
            }
        } else
        {
            int muxBCurrentValue = digitalRead(m_muxBInPin);

            if(muxBCurrentValue != m_muxBButtonStates[m_muxReadIndex])
            {
                // check to see if the debounce time has been exceeded
                if((millis() - m_muxBButtonEventTimes[m_muxReadIndex]) > DEBOUNCE_MS)    // debounce
                {

                    m_muxBButtonStates[m_muxReadIndex] = muxBCurrentValue;           // update array
                    m_muxBButtonEventTimes[m_muxReadIndex] = millis();               // update event time

                    if(m_muxBButtonStates[m_muxReadIndex] == 1)
                    {
                        // button on
                        Serial.print("muxB button ");
                        Serial.print(m_muxReadIndex);
                        Serial.println("on.");

                    } else if(m_muxBButtonStates[m_muxReadIndex] == 0)
                    {
                        // button off 
                        Serial.print("muxB button ");
                        Serial.print(m_muxReadIndex);
                        Serial.println("off.");
                    }
                }
            }
        }
            
        // ** mux C **
        int muxCCurrentValue = digitalRead(m_muxCInPin); 
        
        if(muxCCurrentValue != m_muxCButtonStates[m_muxReadIndex])                   // has something changed?
        {
            // check to see if the debounce time has been exceeded
            if((millis() - m_muxCButtonEventTimes[m_muxReadIndex]) > DEBOUNCE_MS)    // debounce
            {

                m_muxCButtonStates[m_muxReadIndex] = muxCCurrentValue;           // update array
                m_muxCButtonEventTimes[m_muxReadIndex] = millis();               // update event time

                if(m_muxCButtonStates[m_muxReadIndex] == 1)
                {
                    // button on
                    Serial.print("muxC button ");
                    Serial.print(m_muxReadIndex);
                    Serial.println("on.");

                } else if(m_muxCButtonStates[m_muxReadIndex] == 0)
                {
                    // button off 
                    Serial.print("muxC button ");
                    Serial.print(m_muxReadIndex);
                    Serial.println("off.");
                }
            }
        }
            
        if(m_muxReadIndex == 7)                                 // increment or wrap index
        {
            m_muxReadIndex = 0;
        } else
        {
            m_muxReadIndex++;
        }

        m_changeMuxChannel = true;
    }        
}

void Input_Manager::readDirectPot()
{
    int rhythmPotCurrentValue = analogRead(m_rhythmPotPin);

    // check to see if the pot value has changed.
    if(rhythmPotCurrentValue <= (m_rhythmPotLastValue - POT_NOISE_FILTER) || rhythmPotCurrentValue >= (m_rhythmPotLastValue + POT_NOISE_FILTER))                {
        // the pot value has changed.
        m_rhythmPotLastValue = rhythmPotCurrentValue;
        Serial.print("rhythm pot value = ");
        Serial.println(m_rhythmPotLastValue);
    }
}



void Input_Manager::setSensor(int index)
{
  int b0 = bitRead(index, 0);
  int b1 = bitRead(index, 1);
  int b2 = bitRead(index, 2);

  digitalWrite(m_muxSelPin0, b0);
  digitalWrite(m_muxSelPin1, b1);
  digitalWrite(m_muxSelPin2, b2);  
} 