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
            piezoReading = map(piezoReading, 0, 100, 1, 2.5);               // ...scale reading to appropriate range for logarithmic curve
            piezoReading = log(piezoReading);
            m_transport->resetUndoCollector();

            if(m_currentKitIndex > 3)
            {
                m_rhythmGenerator->triggerRhythm(i + 4, piezoReading);      // shift index by 4 to trigger second bank
            } else
            {
                m_rhythmGenerator->triggerRhythm(i, piezoReading);
            }
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
                m_delayEffect->setDepth(map(m_echoPotLastRawValue, 6, 1022, 0, 127));
                Serial.print("echo pot value = ");
                Serial.println(m_echoPotLastRawValue);
            }
        } else
        {
            int muxBCurrentValue = digitalRead(m_muxBInPin);

            if(muxBCurrentValue != m_muxBButtonStates[m_muxReadIndex])
            {
                // check to see if the debounce time has been exceeded
                if((millis() - m_muxBButtonEventTimes[m_muxReadIndex]) > DEBOUNCE_MS)           // debounce
                {
                    m_muxBButtonStates[m_muxReadIndex] = muxBCurrentValue;                      // update array
                    m_muxBButtonEventTimes[m_muxReadIndex] = millis();                          // update event time

                    if(m_muxBButtonStates[m_muxReadIndex] == 1)
                    {
                        // button on
                        Serial.print("muxB button ");
                        Serial.print(m_muxReadIndex);
                        Serial.println("on.");

                        if(m_muxReadIndex == 0)                                                                 // tempo volume menu button
                        {
                            m_tempoVolMenuState = !m_tempoVolMenuState;
                            m_ledController->setTempoVolMenuLeds(m_tempoVolMenuState);

                            if(m_tempoVolMenuState == 0)                                                        // if tempo menu selected...
                            {
                                m_displayController->displayNumber(m_masterClock->getBpm());                    // ...display the tempo.
                            } else if(m_tempoVolMenuState == 1)
                            {
                                m_displayController->displayNumber(m_outputAmplifier->getLevelAsInt());         // ...display the tempo.
                            }
                        }

                        if(m_muxReadIndex == 1)                     // up button
                        {
                            if(m_tempoVolMenuState == 0)            // if tempo menu selected
                            {
                                m_masterClock->incrementBpm();
                                m_rhythmClock->incrementBpm();
                                m_displayController->displayNumber(m_masterClock->getBpm());
                                m_parameterManager->saveMasterTempo(m_masterClock->getBpm());
                            } else if (m_tempoVolMenuState == 1)
                            {
                                m_outputAmplifier->incrementLevel();
                                m_displayController->displayNumber(m_outputAmplifier->getLevelAsInt());
                                m_parameterManager->saveMasterVolume(m_outputAmplifier->getLevelAsInt());
                            }
                        }

                        if(m_muxReadIndex == 2)                     // down button
                        {
                             if(m_tempoVolMenuState == 0)           // if tempo menu selected
                            {
                                m_masterClock->decrementBpm();
                                m_rhythmClock->decrementBpm();
                                m_displayController->displayNumber(m_masterClock->getBpm());
                                m_parameterManager->saveMasterTempo(m_masterClock->getBpm());
                                m_delayEffect->refreshDelayTime();
                            } else if(m_tempoVolMenuState == 1)
                            {
                                m_outputAmplifier->decrementLevel();
                                m_displayController->displayNumber(m_outputAmplifier->getLevelAsInt());
                                m_parameterManager->saveMasterVolume(m_outputAmplifier->getLevelAsInt());
                                m_delayEffect->refreshDelayTime();
                            }
                        }

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

                        if(m_kitPatternMenuState == 0)                                  // the kit menu is selected
                        {
                            for(int i = 0; i < 8; i++)
                            {
                                m_samplePlayers[i].setKit(newKitPattIndex);             // set kit, always use an index of 0-3          
                            }

                            if(newKitPattIndex == m_currentKitIndex)                    // if second press
                            {
                                if(m_currentKitIndex < 4)                               // if below 4... 
                                {
                                    newKitPattIndex = newKitPattIndex + 4;              // bank up
                                } else 
                                {
                                    newKitPattIndex = newKitPattIndex - 4;              // else bank down
                                }
                            }
                            
                            m_sequencer->setPatternIndex(newKitPattIndex);              // ...set with 4 added to index
                            m_parameterManager->saveKitIndex(newKitPattIndex);
                            m_ledController->setKitPattNumLeds(newKitPattIndex);
                            m_currentKitIndex = newKitPattIndex; 
                        }

                        if(m_kitPatternMenuState == 1)                                  // the pattern menu is selected
                        {
                            if(newKitPattIndex == m_currentPattIndex)                   // if second press
                            {
                                if(m_currentPattIndex < 4)                              // if below 4... 
                                {
                                    newKitPattIndex = newKitPattIndex + 4;              // bank up
                                } else 
                                {
                                    newKitPattIndex = newKitPattIndex - 4;              // else bank down
                                }
                            }

                            m_sequencer->setPatternIndex(newKitPattIndex);              // ...set with 4 added to index
                            m_parameterManager->savePatternIndex(newKitPattIndex);
                            m_ledController->setKitPattNumLeds(newKitPattIndex);
                            m_currentPattIndex = newKitPattIndex; 
                        }
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
        Serial.print("rhythm pot value = ");
        Serial.println(m_rhythmPotLastRawValue);


        int rhythmPotCurrentMappedValue = map(m_rhythmPotLastRawValue, 1, 1022, 0, 127);

        if(rhythmPotCurrentMappedValue != m_rhythmPotLastMappedValue)    // further filtering on mapped value.
        {
            m_rhythmGenerator->setRhythm(rhythmPotCurrentMappedValue);
            
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

    if(m_kitPatternMenuState == 0)                                      // kit selected
    {
        m_ledController->setKitPattNumLeds(m_currentKitIndex);
    } else if(m_kitPatternMenuState == 1)                               // pattern selected
    {
        m_ledController->setKitPattNumLeds(m_currentPattIndex);
    }
}

void Input_Manager::setClocks(Midi_Clock *masterClock, Midi_Clock *rhythmClock)
{
    m_masterClock = masterClock;
    m_rhythmClock = rhythmClock;
}

void Input_Manager::setDisplayController(Display_Controller *displayController)
{
    m_displayController = displayController;
}

void Input_Manager::setOutputAmplifier(Output_Amplifier *outputAmplifier)
{
    m_outputAmplifier = outputAmplifier;
}

void Input_Manager::setKitIndex(int kitIndex)
{
    m_currentKitIndex = kitIndex;
    m_ledController->setKitPattNumLeds(m_currentKitIndex);         // light LEDs as this menu is selected at startup
}

void Input_Manager::setPattIndex(int pattIndex)
{
    m_currentPattIndex = pattIndex;
}

void Input_Manager::setDelayEffect(Delay_Effect *delayEffect)
{
    m_delayEffect = delayEffect;
}
