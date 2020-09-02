#ifndef SIMPLE_BUTTON
#define SIMPLE_BUTTON
#include <Arduino.h>
#include "Interface_Element.h"

class Simple_Button: public Interface_Element
{
  protected:                                        // The digital pin the button is connected to.
    int m_debounce_ms;                                  // The number of milliseconds for debouncing
    unsigned long m_last_event_time;                    // Timestamp of the last event
    boolean m_current_state;                            // The current state of the button
  public:
    
    Simple_Button(int debounce_milliseconds);           // Present to allow base class to be initialised from shift_register button, which doesn't have a pin.
    Simple_Button(int pin, int debounce_milliseconds);
    void update() override;
    void update(int pin) override;                      // allows a pin to be provide by a multiplexer.
};
#endif