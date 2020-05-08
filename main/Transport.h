#ifndef TRANSPORT
#define TRANSPORT

#include <Arduino.h>
#include "Master_Clock.h"
#include "Sequencer.h"

class Transport
{
  private:
    Master_Clock* m_masterClock;
    Sequencer* m_sequencer;

  public:
    bool m_playFlag;
    bool m_lastPlayFlag;
    bool m_recordFlag;
    double* m_drumPadReadings;

    Transport(Master_Clock* masterClock, Sequencer* sequencer);
    void logDrumPadReadings(double* drumPadReadings);
    void forwardTriggerEvents(int trackNumber, double velocity);
    void poll();
};

#endif
