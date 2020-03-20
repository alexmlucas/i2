#ifndef SIMPLE_BUTTON
#define SIMPLE_BUTTON
#include "Arduino.h"

class Simple_Button{
  protected:
    int m_pin;                                        // The digital pin the button is connected to.
    int m_debounce_ms;                                // The number of milliseconds for debouncing
    unsigned long m_last_event_time;                  // Timestamp of the last event
    boolean m_current_state;                          // The current state of the button
    void (*callback_function)(void);                         // The function to be called on a button press.
  public:
    Simple_Button(int pin, int debounce_milliseconds);
    bool check_pressed();
    void set_callback_func(void (*f)(void));
};
#endif
