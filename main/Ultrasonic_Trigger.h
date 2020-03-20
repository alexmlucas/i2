#ifndef ULTRASONIC_TRIGGER
#define ULTRASONIC_TRIGGER
#include "Arduino.h"
#include "Track.h"
#include <NewPing.h>

class Ultrasonic_Trigger: public NewPing{
  protected:
    int m_trigger_pin;
    int m_echo_pin;
    int m_max_distance;
    int m_debounce_ms;
    int m_current_segment;
    int m_last_segment;
    int m_last_beam_state;
    int m_last_note_value;
    elapsedMillis m_beam_timer_ms;
    elapsedMillis m_midi_timer_ms;
    bool m_note_off_due;
    bool m_no_activity;
    // NewPing m_new_ping;
    Track *mp_track;
    void (*m_callback_function)(void);                   // The function to be called on a beam event.
  public:
    Ultrasonic_Trigger(int trigger_pin, int echo_pin, int max_distance, int debounce_ms);
    void check_activity();
    bool check_and_return();
    void set_callback_func(void (*f)(void));
    void Ultrasonic_Trigger::set_track(Track *p_track);
};
#endif
