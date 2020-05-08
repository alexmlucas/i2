#ifndef MASTER_CLOCK
#define MASTER_CLOCK

#include <Arduino.h>
#include "Constant_Parameters.h"

class Master_Clock
{
  public:
    int m_bpm;
    int m_currentMidiTick;
    int m_midiTickInterval;
    elapsedMicros m_timer;
    
    Master_Clock(int bpm);
    int calculateMidiTickInterval(int incomingBpm);
    void resetTimer();
    void updateMidiTickCounter();
    int getMidiTick();
    bool isMidiTick32nd();
    void poll();
};

#endif
