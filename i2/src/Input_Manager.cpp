#include "Input_Manager.h"

Input_Manager::Input_Manager()
{

    m_piezoPins[0] =  A2;
    m_piezoPins[1] =  A1;
    m_piezoPins[2] =  A0;
    m_piezoPins[3] =  A3;
    
    pinMode(m_rhythmPotPin, INPUT);
    pinMode(m_muxAInPin, INPUT);
    pinMode(m_muxBInPin, INPUT);
    pinMode(m_muxCInPin, INPUT);
    pinMode(m_muxSelPin0, OUTPUT);
    pinMode(m_muxSelPin1, OUTPUT);
    pinMode(m_muxSelPin2, OUTPUT);

    for(int i = 0; i < 4; i++)
    {
        pinMode(m_piezoPins[i], INPUT);
        m_piezoPeaks[i] = 0;
        m_piezoStates[i] = 0;
        m_piezoTimers[i] = 0;
    }

    for(int i = 0; i < 8; i++)
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

    for(int i = 0; i < 4; i++)
    {
        int piezoReading = this->readPiezo(i);

        if(piezoReading > 0)
        {
            Serial.print("Piezo ");
            Serial.print(i);
            Serial.print(" = ");
            Serial.println(piezoReading);
        }
    }
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
                m_muxAButtonStates[m_muxReadIndex] = muxACurrentValue;              // update array
                m_muxAButtonEventTimes[m_muxReadIndex] = millis();                  // update event time

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

int Input_Manager::readPiezo(int index){
  int piezo = analogRead(index);
  int return_value = 0;                   

  if(m_piezoStates[index] == 0){                                // ----Idle state-------------
    
    if(piezo > PIEZO_THRESHOLD){
      m_piezoStates[index] = 1;                                 // If a reading is above the threshold, move to Peak tracking.
      m_piezoPeaks[index] = piezo;                              // The current reading is set as the peak.
      m_piezoTimers[index] = 0;
    }
    
  } else if(m_piezoStates[index] == 1){                         // ----Peak tracking state----    
                        
    if(piezo > m_piezoPeaks[index]){                            // Capture the largest reading.
      m_piezoPeaks[index] = piezo;
    }
    
    if(m_piezoTimers[index] >= PIEZO_PEAK_MS){                  // loop for a certain amount of time to get the peak value.
      return_value = m_piezoPeaks[index];                       // Set return value to the peak value.
      m_piezoTimers[index] = 0;                                 // Reset the timer.
      m_piezoStates[index] = 2;                                 // Move to Aftershock state.
    }
  } else{                                                       // ----Aftershock state-------

    if(piezo > PIEZO_THRESHOLD){                                // Keep refreshing timer if above threshold                  
      m_piezoTimers[index] = 0;                           
      
    } else if(m_piezoTimers[index] > PIEZO_AFTERSHOCK_MS){      // Return to Idle state now that aftershock time is exceeded.
      m_piezoStates[index] = 0;
      return_value = 0;
    }
  }

  return return_value;
}