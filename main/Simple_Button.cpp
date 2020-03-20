#include "Simple_Button.h"

Simple_Button::Simple_Button(int pin, int debounce_milliseconds){
  m_pin = pin;
  pinMode(m_pin, INPUT);
  m_debounce_ms = debounce_milliseconds;
  m_last_event_time = 0;
  m_current_state = LOW;
}

bool Simple_Button::check_pressed(){
  boolean button_state;

  if(digitalRead(m_pin) == HIGH){
    button_state = HIGH;
  } else{
    button_state = LOW;
  }

  if(button_state != m_current_state){                          // Has the button changed state?
    Serial.println("state has changed");
    if((millis() - m_last_event_time) > m_debounce_ms){         // If the debounce time has been exceeded...
      m_current_state = button_state;                           // ... change state.
      m_last_event_time = millis();                             // Reset the timer ready for the next iteration.
      
      if(button_state == HIGH){                                 // If the button is HIGH...
        if(m_callback_function != NULL){                        // ... If there's a callback function...
          m_callback_function();                                // ... call it!
        }

        Serial.println("Button pressed");

      }
    }
  }
  return m_current_state;
}

void Simple_Button::set_callback_func(void (*f)(void)){
  m_callback_function = f;
}
