#include "Ultrasonic_Trigger.h"

Ultrasonic_Trigger::Ultrasonic_Trigger(int trigger_pin, int echo_pin, int max_distance, int debounce_ms):NewPing(trigger_pin, echo_pin, max_distance){
  m_debounce_ms = debounce_ms;
  m_beam_timer = 0;
  m_midi_timer_ms = 0;
  m_current_segment = -1;
  m_last_segment = -1;
  m_last_beam_state = false;
  m_last_note_value = -1;
  m_note_off_due = false;
  m_no_activity = true;

  // intialise m_beam_readings to null.
  for(int i = 0; i < MAX_BUFFER_SIZE; i++){
    m_values[i] = -1;
  } 

  m_value_index = 0;
  m_median_value = 0;

  m_activity_state = false;
  m_last_activity_state = false;
  m_state = 0;
  m_last_state = 0;
}

void Ultrasonic_Trigger::set_track(Track *p_track){
  mp_track = p_track;
}

void Ultrasonic_Trigger::set_led(Led *p_led){
  mp_led = p_led;
}

void Ultrasonic_Trigger::check_activity(){

  if(m_beam_timer > FILTER_MS){

    // -------- Get Median Value --------
    int current_value = this->ping_cm();            // read the current value
   
    m_values[m_value_index] = current_value;        // add the value to the buffer.
    m_value_index++;                                // increment the index
  
    if(m_value_index == MAX_BUFFER_SIZE){           // if the buffer has been filled...
      for(int i; i < MAX_BUFFER_SIZE; i++){         // ...calculate the median
        m_median_value += m_values[i];
      }
      m_median_value /= MAX_BUFFER_SIZE;      
      m_value_index = 0;                            // reset the buffer.
    }    

    // split between two ranges to begin with.
    // distance could be between 1 and 60 cm.
    
    // -------- Process Input --------
    if(m_median_value == 0){
      m_state = 0;
    } else if(m_median_value > 0 && m_median_value <=30){
      m_state = 1;
    } else if(m_median_value > 30 && m_median_value <= 60){
      m_state = 2;
    }

    Serial.println(m_state);



    

    if(m_state != m_last_state){          // if the state has changed, act on it.
      switch(m_state){                    // set the step frequency based on m_state.
        case 1:
          mp_track->setStepFrequency(2);
          break;
        case 2:
          mp_track->setStepFrequency(4);
          break;
      }

      if(m_state > 0){                    
        mp_led->set_on(true);             // switch on the LED.
        mp_track->setActive(true);        // activate the track.
      } else{
        mp_led->set_on(false);            // switch off the LED.
        mp_track->setActive(false);       // deactivate the track.
      }

      m_last_state = m_state;             // update m_last_state.
    }

    







    
    /*// -------- Process Input --------
    if(m_median_value){                             // if the median is a non-zero value...
      m_activity_state = true;
    } else{
      m_activity_state = false;
    }
  
    if(m_activity_state != m_last_activity_state){  // if the activity state has changed, act on it.
      if(m_activity_state){                         // set the LED accordingly.
        mp_led->set_on(true);
        mp_track->setStepFrequency(10);             // set the step frequency and activate track.
        mp_track->resetStepCounter();               // reset the step counter.
        mp_track->setActive(true);
      } else {
        mp_led->set_on(false);
        mp_track->setActive(false);                 // switch the track off.
      }
  
      m_last_activity_state = m_activity_state;     // update the last activity state.
    }*/

    m_beam_timer = 0;                               // reset timer.
  }
}

bool Ultrasonic_Trigger::check_and_return(){
  bool return_value = false;
  int current_distance = this->ping_cm();

  if(current_distance > 0){
   return_value = true;
   m_beam_timer = 0;
  }

  return return_value;
}

void Ultrasonic_Trigger::set_callback_func(void (*f)(void)){
  m_callback_function = f;
}
