#ifndef TRANSPORT
#define TRANSPORT

#include <Arduino.h>
#include "Midi_Clock.h"
#include "Sequencer.h"
#include "Led_Controller.h"

class Transport
{
  private:
    Midi_Clock *m_masterClock;
    Sequencer *m_sequencer;
    Led_Controller *m_ledController; 

  public:
    bool m_playFlag;
    bool m_lastPlayFlag;
    bool m_newPlayEvent;
    bool m_recordFlag;
    bool m_eventFlag;
    int m_track;
    float m_velocity;

    Transport(Midi_Clock *masterClock, Sequencer *sequencer, Led_Controller *ledController);
    void logTriggerEvent(int track, float velocity);
    void poll();
    void flipPlayState();
    void flipRecordState();
};

#endif
