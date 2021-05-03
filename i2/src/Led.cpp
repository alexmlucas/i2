#include "Led.h"                           

Led::Led(int pin)
{
  m_on_value = 255;
  m_flash_flag = false;
  m_pulse_flag = false; 
  m_currently_on = false;
  m_flash_rate_ms = 250;
  m_pin = pin;
  pinMode(m_pin, OUTPUT);
  analogWrite(m_pin, m_currently_on);
}

Led::Led(int muxIndex, int bit)
{
  m_on_value = 255;
  m_flash_flag = false;
  m_pulse_flag = false; 
  m_currently_on = false;
  m_flash_rate_ms = 250;
  m_bit = bit;
}

void Led::set_on(bool _state){
  set_flashing(false); // Before doing anything, make sure flashing is switched off.
  
  switch(_state){
    case _OFF:
      analogWrite(m_pin, 0);
      m_currently_on = false;
      break;
    case _ON:
      analogWrite(m_pin, m_on_value);
      m_currently_on = true;
      break;
  }
}

void Led::pulse()
{
  m_pulse_flag = true;            // set the pulse flag
  set_on(true);                   // switch on the led.
  m_ms_since_pulse_on = 0;        // reset the pulse on timer.
}

void Led::poll()                  // a generic class for refreshing the led state.
{              
  this->update_pulse();                  
  this->update_flashing();
}

void Led::set_flashing(bool _state){
  m_flash_flag = _state;
  m_currently_on = false;
  analogWrite(m_pin, 0);
}

void Led::update_pulse()
{
  if(m_pulse_flag){
    if(m_ms_since_pulse_on > PULSE_LENGTH_MS){    // if pulse length is exceeded...
      set_on(false);                              // ...switch off...
      m_pulse_flag = false;                        // ...and turn off pulse flag.
    }
  }
}

void Led::update_flashing()
{
  if(m_flash_flag){
    if((millis() - m_last_flash_time) > m_flash_rate_ms){

      if(m_currently_on){
        set_on(false);        // if already on, switch off...
      } else {              
        set_on(true);         // ...and vice versa.
      }

      m_last_flash_time = millis();
    }
  }
}
