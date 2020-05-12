#ifndef TRANSPORT
#define TRANSPORT

#include <Arduino.h>
#include "Midi_Clock.h"
#include "Sequencer.h"

class Transport
{
  private:
    Midi_Clock* m_masterClock;
    Sequencer* m_sequencer;

  public:
    bool m_playFlag;
    bool m_lastPlayFlag;
    bool m_recordFlag;
    bool m_eventFlag;
    int m_track;
    float m_velocity;

    Transport(Midi_Clock* masterClock, Sequencer* sequencer);
    void logTriggerEvent(int track, float velocity);
    void poll();
};

#endif
