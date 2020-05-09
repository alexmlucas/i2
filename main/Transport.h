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
    double* m_drumPadReadings;

    Transport(Midi_Clock* masterClock, Sequencer* sequencer);
    void logDrumPadReadings(double* drumPadReadings);
    void poll();
};

#endif
