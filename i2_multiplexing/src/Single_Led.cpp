#include "Single_Led.h"                           

Single_Led::Single_Led()
{
  m_direction = OUTPUT;
  m_on_value = 255;
  m_flash_flag = false;
  m_currently_on = true;
  this->set_on(true);
  m_flash_rate_ms = 250;
}

void Single_Led::set_pinout(int pin)
{
  m_pin = pin;
  pinMode(m_pin, m_direction);
  analogWrite(m_pin, m_currently_on);
}

void Single_Led::set_on(bool _state)
{
  set_flashing(false); // Before doing anything, make sure flashing is switched off.
  
  switch(int(_state))
  {
    case _OFF:
      analogWrite(m_pin, 0);
      m_currently_on = false;
      break;
    case _ON:
      m_currently_on = true;
      break;
  }
}

void Single_Led::set_flashing(bool _state)
{
  m_flash_flag = _state;
  m_currently_on = false;
  analogWrite(m_pin, 0);
}

void Single_Led::update()
{
  if(m_flash_flag == true)
  {
    if((millis() - m_last_flash_time) > m_flash_rate_ms)
    {
      m_currently_on = !m_currently_on;

      if(m_currently_on == true)
      {
        analogWrite(m_pin, m_on_value);
      } else {
        analogWrite(m_pin, 0);
      }

      m_last_flash_time = millis();
    }
  }
}

void Single_Led::update(int pin)
{
  /*Serial.print("updating LED on pin number... ");
  Serial.println(pin);*/

  //this->set_on(true);
  

  analogWrite(4, 255);

  /*if(m_flash_flag == true)
  {
    if((millis() - m_last_flash_time) > m_flash_rate_ms)
    {
      m_currently_on = !m_currently_on;

      if(m_currently_on == true)
      {
        analogWrite(pin, m_on_value);
      } else {
        analogWrite(pin, 0);
      }

      m_last_flash_time = millis();
    }
  }*/
}