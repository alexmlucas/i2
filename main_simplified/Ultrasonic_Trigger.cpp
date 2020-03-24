#include "Ultrasonic_Trigger.h"

Ultrasonic_Trigger::Ultrasonic_Trigger(int trigger_pin, int echo_pin, int max_distance, int debounce_ms):NewPing(trigger_pin, echo_pin, max_distance){
  m_debounce_ms = debounce_ms;
  m_beam_timer_ms = 0;
  m_midi_timer_ms = 0;
  m_current_segment = -1;
  m_last_segment = -1;
  m_last_beam_state = false;
  m_last_note_value = -1;
  m_note_off_due = false;
  m_no_activity = true;
}

void Ultrasonic_Trigger::set_track(Track *p_track){
  mp_track = p_track;
}

void Ultrasonic_Trigger::set_led(Led *p_led){
  mp_led = p_led;
}

void Ultrasonic_Trigger::check_activity(){
  bool beam_broken = false;

  if(m_beam_timer_ms > m_debounce_ms){
    int current_distance = this->ping_median();
  
    // determine the segment.
    if(current_distance > 0){
      beam_broken = true;
      //mp_led->set_on(true);
    } else{
      beam_broken = false;
      //mp_led->set_on(false);
    }
    
    // only act if the value has changed.
    if(beam_broken != m_last_beam_state){

      // if bean has been broken...
      if(beam_broken){
        Serial.println("on");
        //mp_track->setStepFrequency(9);
        //mp_track->setActive(true);
        
      } else {
        //mp_track->setActive(false);
        
        Serial.println("off");
      }
      
      m_last_beam_state = beam_broken;
    }

    /*if(button_state == HIGH){                                 // If the button is HIGH...
      if(callback_function != NULL){                            // ... If there's a callback function...
        callback_function();                                    // ... call it!
      }

      Serial.println("Button pressed");
    }*/
  
    m_beam_timer_ms = 0;
  }  
}

bool Ultrasonic_Trigger::check_and_return(){
  bool return_value = false;
  int current_distance = this->ping_cm();

  if(current_distance > 0){
   return_value = true;
   m_beam_timer_ms = 0;
  }

  return return_value;
}

void Ultrasonic_Trigger::set_callback_func(void (*f)(void)){
  m_callback_function = f;
}
