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

    m_echoPotLastRawValue = 0;
    m_rhythmPotLastRawValue = 0;
    m_rhythmPotLastMappedValue = 0;
    m_muxReadTimer = 0;
    m_muxReadIndex = 0;

    m_readMuxChannel = false;
    m_changeMuxChannel = true;
}

void Input_Manager::setSamplePlayers(Sample_Player *samplePlayers)
{
    m_samplePlayers = samplePlayers;
}

void Input_Manager::setLedController(Led_Controller *ledController)
{
    m_ledController = ledController;
}

void Input_Manager::setRhythmGenerator(Rhythm_Generator *rhythmGenerator)
{
    m_rhythmGenerator = rhythmGenerator;
}

void Input_Manager::poll()
{
    this->readMuxs();
    this->readDirectPot();

    for(int i = 0; i < 4; i++)
    {
        float piezoReading = this->readPiezo(i);

        if(piezoReading > 0)
        {
            piezoReading = constrain(piezoReading, 0, 100);
            piezoReading = map(piezoReading, 0, 100, 1, 2.5);           // ...scale reading to appropriate range for logarithmic curve
            piezoReading = log(piezoReading);
            m_rhythmGenerator->triggerRhythm(i, piezoReading);          
            
            /* Serial.print("Piezo ");
            Serial.print(i);
            Serial.print(" = ");
            Serial.println(piezoReading);*/
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
                    switch(m_muxReadIndex)                  // filter index 7; the speed control which needs different treatment.
                    {
                        case 7:
                            m_rhythmGenerator->decrementSpeed();
                            break;
                        default:
                            m_rhythmGenerator->flipRhythmBit(m_muxReadIndex);

                    }
                }
            }
        }
        
        // ** mux B **
        if(m_muxReadIndex == 4)                                              // handle pot differently
        {
            int muxBCurrentValue = analogRead(m_muxBInPin);

            // check to see if the pot value has changed.
            if(muxBCurrentValue <= (m_echoPotLastRawValue - POT_NOISE_FILTER) || muxBCurrentValue >= (m_echoPotLastRawValue + POT_NOISE_FILTER))
            {
                // the pot value has changed.
                m_echoPotLastRawValue = muxBCurrentValue;
                Serial.print("echo pot value = ");
                Serial.println(m_echoPotLastRawValue);
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
    int rhythmPotCurrentRawValue = analogRead(m_rhythmPotPin);

    // check to see if the pot value has changed.
    if(rhythmPotCurrentRawValue <= (m_rhythmPotLastRawValue - POT_NOISE_FILTER) || rhythmPotCurrentRawValue >= (m_rhythmPotLastRawValue + POT_NOISE_FILTER))                {
        // the pot value has changed.
        m_rhythmPotLastRawValue = rhythmPotCurrentRawValue;

        int rhythmPotCurrentMappedValue = map(m_rhythmPotLastRawValue, 0, 1024, 0, 127);

        if(rhythmPotCurrentMappedValue != m_rhythmPotLastMappedValue)    // further filtering on mapped value.
        {
            m_rhythmGenerator->setRhythm(rhythmPotCurrentMappedValue);
            Serial.print("rhythm pot value = ");
            Serial.println(rhythmPotCurrentMappedValue);
            m_rhythmPotLastMappedValue = rhythmPotCurrentMappedValue;
        }
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
  int piezo = analogRead(m_piezoPins[index]);
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