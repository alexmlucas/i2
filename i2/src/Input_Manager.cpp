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

void Input_Manager::setParameterManager(Parameter_Manager *parameterManager)
{
    m_parameterManager = parameterManager;
}

void Input_Manager::setTransport(Transport *transport)
{
    m_transport = transport;
}

void Input_Manager::setSequencer(Sequencer *sequencer)
{
    m_sequencer = sequencer;
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
            m_transport->resetUndoCollector();

            if(m_kitBankState)                                         // add 4 to the trigger index if bank active
            {
                
                m_rhythmGenerator->triggerRhythm(i + 4, piezoReading);
            } else
            {
                m_rhythmGenerator->triggerRhythm(i, piezoReading);
            }
                   
            
            /* Serial.print("Piezo ");
            Serial.print(i);
            Serial.print(" = ");
            Serial.println(piezoReading);*/
        }
    }

    if(m_undoHeld)
    {
        if(m_undoTimer > PRESS_HOLD_TIMER_MS)
        {
            // clear pattern
            m_transport->requestPatternClear();
            m_ledController->setUndoLed(LOW);
            m_undoHeld = false;
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
                    switch(m_muxReadIndex)  
                    {                
                        case 7:                                                                 // filter index 7, the speed control which needs different treatment.
                            m_rhythmGenerator->decrementSpeed();                                // decrement speed
                            m_parameterManager->setSpeed(m_rhythmGenerator->getSpeed());        // update the parameter manager
                            break;
                        default:
                            m_rhythmGenerator->flipRhythmBit(m_muxReadIndex);       
                            break;
                    }
                }
            }
        }
        
        // ** mux B **
        if(m_muxReadIndex == 4)                                                     // handle pot differently
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

                        if(m_muxReadIndex == 5)                     // play button
                        {
                            m_transport->flipPlayState();
                        }

                        if(m_muxReadIndex == 6)                     // undo
                        {
                            m_ledController->setUndoLed(HIGH);
                            m_transport->undoRecordedData();
                            m_undoHeld = true;                     // detect press and hold.
                            m_undoTimer = 0;
                        }

                        if(m_muxReadIndex == 7)                     // record
                        {
                            m_transport->flipRecordState();
                        }
                    } else if(m_muxBButtonStates[m_muxReadIndex] == 0)
                    {
                        // button off 
                        Serial.print("muxB button ");
                        Serial.print(m_muxReadIndex);
                        Serial.println("off.");

                        if(m_muxReadIndex == 6)                     // undo
                        {
                            m_ledController->setUndoLed(LOW);
                            m_undoHeld = false;                     // cease press and hold.
                        }
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
                    if(m_muxReadIndex == 7)
                    {
                        // flip kit pattern menu
                        this->flipKitPatternMenuState();                                    // flip the state internal to this class.
                    } else                                                                  // else, we're dealing with a kitPatt button.
                    {
                        int newKitPattIndex = 0;

                        switch(m_muxReadIndex)                                              // convert the incomming index to a sensible value
                        {
                            case 3:
                                // kit/pattern button 4
                                newKitPattIndex = 3;
                                break;
                            case 4:
                                // kit/pattern button 3
                                newKitPattIndex = 2;
                                break;
                            case 5:
                                // kit/pattern button 2
                                newKitPattIndex = 1;
                                break;
                            case 6:
                                // kit/pattern button 1
                                newKitPattIndex = 0;
                                break;
                        }


                        if(m_kitPatternMenuState == 0)                                      // the kit menu is selected
                        {
                            if(newKitPattIndex == m_lastKitValue)                           // the button has been pressed a second time
                            {
                                m_kitBankState = !m_kitBankState;                           // flip the bank state
                            } else 
                            {
                                m_kitBankState = 0;                                         // otherwise reset the state
                            }

                            if(m_kitBankState == 0)                                         // if not banked...
                            {
                                for(int i = 0; i < 8; i++)
                                {
                                    m_samplePlayers[i].setKit(newKitPattIndex);             // set kit, i.e set the filename of all sample players           
                                }  
                                m_parameterManager->saveKit(newKitPattIndex);               // save the change to eeprom
                                m_ledController->setKitPattFlashing(false);
                                m_ledController->setKitPattNumLeds(newKitPattIndex);
                            } else 
                            {
                                m_ledController->setKitPattFlashing(true);
                            }

                            m_lastKitValue = newKitPattIndex;
                        }

                        if(m_kitPatternMenuState == 1)                                      // the pattern menu is selected
                        {
                            Serial.println("we're in");
                            if(newKitPattIndex == m_lastPatternValue)                       // the button has been pressed a second time
                            {
                                m_patternBankState = !m_patternBankState;                   // flip the bank state
                            } else 
                            {
                                m_patternBankState = 0;                                     // otherwise reset the state
                            }

                            if(m_patternBankState == 0)                                     // if not banked...
                            {
                                m_sequencer->setPatternIndex(newKitPattIndex);              // set pattern
                                m_parameterManager->savePattern(newKitPattIndex);           // save the change to eeprom              
                                m_ledController->setKitPattFlashing(false);
                                m_ledController->setKitPattNumLeds(newKitPattIndex);
                            } else                                                          // else we are banked
                            {
                                m_sequencer->setPatternIndex(newKitPattIndex + 4);
                                m_ledController->setKitPattFlashing(true);
                            }
                            
                            m_lastPatternValue = newKitPattIndex;
                        }

                        /*int newKitPattIndex = 0;
                        int currentKitPatternIndex = 0;

                        if(m_kitPatternMenuState)
                        {
                            currentKitPatternIndex = m_parameterManager->getPattern();
                        } else
                        {
                            currentKitPatternIndex = m_parameterManager->getKit();
                        }

                        switch(m_muxReadIndex)
                        {
                            case 3:
                                // kit/pattern button 4
                                newKitPattIndex = 3;
                                break;
                            case 4:
                                // kit/pattern button 3
                                newKitPattIndex = 2;
                                break;
                            case 5:
                                // kit/pattern button 2
                                newKitPattIndex = 1;
                                break;
                            case 6:
                                // kit/pattern button 1
                                newKitPattIndex = 0;
                                break;
                        }

                        if(newKitPattIndex == m_lastKitPattIndex)           // flip the bank state if required.
                        {
                            m_bankState = !m_bankState;
                        }

                        Serial.print("new index = ");
                        Serial.println(newKitPattIndex);
                        Serial.print("last index = ");
                        Serial.println(m_lastKitPattIndex);
                        Serial.print("bank state = ");
                        Serial.println(m_bankState);

                        m_lastKitPattIndex = newKitPattIndex;

                        if(m_kitPatternMenuState)                                           // if pattern is selected
                        {
                            if(m_bankState)                                                 // if in bank state...
                            {
                                newKitPattIndex = newKitPattIndex + 4;                      // ...add four to index
                            }
                            
                            m_sequencer->setPatternIndex(newKitPattIndex);                  // change the pattern in the sequencer
                            m_parameterManager->savePattern(newKitPattIndex);               // save the change to eeprom
                        } else                                                              // otherwise, kit is selected
                        {
                            m_kitBankState = m_bankState;                                   // update the kitBankState

                            if(!m_kitBankState)                                             // if not in a bankstate...
                            {
                                for(int i = 0; i < 8; i++)
                                {
                                    m_samplePlayers[i].setKit(newKitPattIndex);             // set kit, i.e set the filename of all sample players           
                                }  
                                m_parameterManager->saveKit(newKitPattIndex);               // save the change to eeprom
                                //m_kitPatternMenuState = false;         
                            }    
                        }



                        m_ledController->setKitPattNumLeds(newKitPattIndex);    */            // update the LEDs
                    }
                } else if(m_muxCButtonStates[m_muxReadIndex] == 0)
                {
                    // button off 
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

void Input_Manager::setKitPatternMenuState(int state)
{
    m_kitPatternMenuState = state;
    m_ledController->setKitPattMenuLeds(state);
}

void Input_Manager::setTempoVolMenuState(int state)
{
    m_tempoVolMenuState = state;
    m_ledController->setTempoVolMenuLeds(state);
}

void Input_Manager::flipKitPatternMenuState()
{
    m_kitPatternMenuState = !m_kitPatternMenuState;
    m_ledController->setKitPattMenuLeds(m_kitPatternMenuState);         // update leds
}