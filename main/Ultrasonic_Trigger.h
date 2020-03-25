#ifndef ULTRASONIC_TRIGGER
#define ULTRASONIC_TRIGGER
#include "Arduino.h"
#include "Track.h"
#include "Led.h"
#include <NewPing.h>

#define MAX_BUFFER_SIZE 16
#define FILTER_MS 5

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
    elapsedMillis m_beam_timer;
    elapsedMillis m_midi_timer_ms;
    bool m_note_off_due;
    bool m_no_activity;
    // NewPing m_new_ping;
    Track *mp_track;
    Led *mp_led;
    void (*m_callback_function)(void);                   // The function to be called on a beam event.
    int m_values[MAX_BUFFER_SIZE];
    int m_value_index;
    int m_median_value;
    bool m_activity_state;
    bool m_last_activity_state;
    int m_state;
    int m_last_state;
    
  public:
    Ultrasonic_Trigger(int trigger_pin, int echo_pin, int max_distance, int debounce_ms);
    void check_activity();
    bool check_and_return();
    void set_callback_func(void (*f)(void));
    void set_track(Track *p_track);
    void set_led(Led *p_led);
};
#endif
