#include "Simple_Button.h"

Simple_Button::Simple_Button(int debounce_milliseconds)
{
  m_direction = INPUT;
  m_debounce_ms = debounce_milliseconds;
  m_last_event_time = 0;
  m_current_state = false;
}

Simple_Button::Simple_Button(int pin, int debounce_milliseconds)
{
  m_direction = INPUT;
  m_pin = pin;
  pinMode(m_pin, m_direction);
  m_debounce_ms = debounce_milliseconds;
  m_last_event_time = 0;
  m_current_state = false;
}

void Simple_Button::update()
{
    boolean button_state;

    if(digitalRead(m_pin) == HIGH)
    {
        button_state = HIGH;
    } else
    {
        button_state = LOW;
    }

    if(button_state != m_current_state)                             // Has the button changed state?
    {                          
        if((millis() - m_last_event_time) > m_debounce_ms)          // If the debounce time has been exceeded...
        {         
            m_current_state = button_state;                         // ... change state.
            m_last_event_time = millis();                           // Reset the timer ready for the next iteration.
        
            if(button_state == HIGH)                                // If the button is HIGH...
            {
                Serial.println("button pressed");                   
            }
        }
    }
}

void Simple_Button::update(int pin)
{

    /*Serial.print("updating button on pin number... ");
    Serial.println(pin);*/

    boolean button_state;

    if(digitalRead(pin) == HIGH)
    {
        button_state = HIGH;
    } else
    {
        button_state = LOW;
    }

    if(button_state != m_current_state)                             // Has the button changed state?
    {                        
        if((millis() - m_last_event_time) > m_debounce_ms)          // If the debounce time has been exceeded...
        {         
            m_current_state = button_state;                         // ... change state.
            m_last_event_time = millis();                           // Reset the timer ready for the next iteration.
        
            if(button_state == HIGH)                                // If the button is HIGH...
            {
                Serial.println("button pressed");                   
            }
        }
    }
}