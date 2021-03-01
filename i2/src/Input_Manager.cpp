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
    }

    m_echoPotLastValue = 0;
    m_buttonReadTimer = 0;
}

void Input_Manager::poll()
{
    this->readMuxs();
    this->readDirectPot();
}

void Input_Manager::readMuxs()
{
    if(m_buttonReadTimer > BUTTON_READ_INTERVAL)
    {
        for(int i = 0; i < 8; i++)
        {
            this->setSensor(i);

            // ** mux A **
            int muxACurrentValue = digitalRead(m_muxAInPin); 
            
            if(muxACurrentValue != m_muxAButtonStates[i])           // has something changed?
            {
                if(muxACurrentValue)
                {
                    // button on
                } else
                {
                    // button off 
                }

                m_muxAButtonStates[i] = muxACurrentValue;           // update array
            }
            
            // ** mux B **
            if(i == 4)                                              // handle pot differently
            {
                int muxBCurrentValue = analogRead(m_muxBInPin);

                // check to see if the pot value has changed.
                if(muxBCurrentValue <= (m_echoPotLastValue - POT_NOISE_FILTER) || muxBCurrentValue >= (m_echoPotLastValue + POT_NOISE_FILTER))                {
                    // the pot value has changed.
                    m_echoPotLastValue = muxBCurrentValue;
                }
            } else
            {
                int muxBCurrentValue = digitalRead(m_muxBInPin); 

                if(muxBCurrentValue != m_muxBButtonStates[i])       // has something changed?
                {
                    if(muxBCurrentValue)
                    {
                        // button on

                    } else 
                    {
                        // button off
                    }
                    
                    m_muxBButtonStates[i] = muxBCurrentValue;       // update array
                }
            }
                
            // ** mux C **
            int muxCCurrentValue = digitalRead(m_muxCInPin); 
            
            if(muxCCurrentValue != m_muxCButtonStates[i])           // has something changed?
            {
                if(muxCCurrentValue)
                {
                    // button on
                } else
                {
                    // button off
                }

                m_muxCButtonStates[i] = muxCCurrentValue;           // update array
            }
        }

        m_buttonReadTimer = 0;
    }
}

void Input_Manager::readDirectPot()
{
    int rhythmPotCurrentValue = analogRead(m_rhythmPotPin);

    // check to see if the pot value has changed.
    if(rhythmPotCurrentValue <= (m_rhythmPotLastValue - POT_NOISE_FILTER) || rhythmPotCurrentValue >= (m_rhythmPotLastValue + POT_NOISE_FILTER))                {
        // the pot value has changed.
        m_rhythmPotLastValue = rhythmPotCurrentValue;
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