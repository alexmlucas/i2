#ifndef LED
#define LED
#include "Arduino.h"                            // Include the header file that defines INPUT and HIGH

#define _OFF 0
#define _ON 1
#define PULSE_LENGTH_MS 100

class Led{ 
     
  protected:

     int m_colour;
     int m_on_value;

     bool m_isShiftReg;
     int m_ShiftRegIndex;
     int m_pin;
     int m_muxIndex;
     int m_bit;
     
     bool m_currently_on;
     bool m_flash_flag;
     bool m_pulse_flag;
     int m_flash_rate_ms;
     int m_last_flash_time;
     elapsedMillis m_ms_since_pulse_on;
  public:
    Led(int pin);
    Led(int muxIndex, int bit);
    void set_on(bool _state);
    void set_flashing(bool _state);
    void pulse();
    void update_flashing();
    void update_pulse();
    void poll();
};

#endif
