#ifndef MIDI_CLOCK
#define MIDI_CLOCK

#include <Arduino.h>
#include "Constant_Parameters.h"

class Midi_Clock
{
  private:
    const int DEFAULT_BPM = 120;
    const int MODULO_32ND = 3;
    const int MODULO_16TH = 6;
    const int MODULO_8TH = 12;
    const int MODULO_4TH = 24;
    
  public:
    int m_bpm;
    int m_currentMidiTick;
    int m_midiTickInterval;
    bool m_runFlag;
    bool m_isMaster;
    elapsedMicros m_timer;
    

    Midi_Clock(bool isMaster);
    int calculateMidiTickInterval(int incomingBpm);
    void _reset();
    void updateMidiTickCounter();
    int getMidiTick();
    bool isMidiTick32nd();
    bool isMidiTick16th();
    bool isMidiTick8th();
    bool isMidiTick4th();
    void poll();
    void setRunFlag(int state);
    void setBpm(int bpm);
    void incrementBpm();
    void decrementBpm();
    int getBpm();
};

#endif
