#ifndef PIEZO_TRIGGER
#define PIEZO_TRIGGER
#include "Arduino.h"

const int THRESHOLD = 15                      ;     // minimum reading, avoid "noise".
const int PEAK_MS = 2;        // time to read peak value.
const int AFTERSHOCK_MS = 10;  // time of aftershocks and vibration.

class Piezo_Trigger{
  protected:
    int m_pin;                                        // The pin the piezo is connected to.
    int m_peak;                                       // Remember the last peak value.
    int m_state;                                      // Activity scan state.
    elapsedMillis m_msec;                             // Timer to end states.
    void (*m_callback_function)(void);                // The function to be called on a piezo event.
  public:
    Piezo_Trigger(int pin);
    int checkActivity();
    void set_callback_func(void (*f)(void));
};

#endif
