#include "Piezo_Trigger.h"

Piezo_Trigger::Piezo_Trigger(int pin){
  m_pin = pin;
  pinMode(m_pin, INPUT);
  m_peak = 0;
  m_state = 0;
}

void Piezo_Trigger::set_callback_func(void (*f)(void)){
  m_callback_function = f;
}

int Piezo_Trigger::checkActivity(){
  int piezo = analogRead(m_pin);
  int return_value = 0;                   // reset values.

  if(m_state == 0){                       // ----Idle state-------------
    
    if(piezo > THRESHOLD){
      m_state = 1;                        // If a reading is above the threshold, move to Peak tracking.
      m_peak = piezo;                     // The current reading is set as the peak.
      m_msec = 0;
    }
    
  } else if(m_state == 1){                // ----Peak tracking state----    
                        
    if(piezo > m_peak){                   // Capture the largest reading.
      m_peak = piezo;
    }
    
    if(m_msec >= PEAK_MS){                // loop for a certain amount of time to get the peak value.
      return_value = m_peak;              // Set return value to the peak value.
      m_msec = 0;                         // Reset the timer.
      m_state = 2;                        // Move to Aftershock state.
    }
    
  } else{                                 // ----Aftershock state-------

    if(piezo > THRESHOLD){                // Keep refreshing timer if above threshold                  
      m_msec = 0;                           
      
    } else if(m_msec > AFTERSHOCK_MS){    // Return to Idle state now that aftershock time is exceeded.
      m_state = 0;
      return_value = 0;
    }
  }

  return return_value;
}
