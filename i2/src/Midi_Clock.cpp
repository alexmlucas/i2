#include "Midi_Clock.h"

Midi_Clock::Midi_Clock(int bpm)
{
  m_bpm = bpm;
  m_midiTickInterval = this->calculateMidiTickInterval(bpm);
}

int Midi_Clock::calculateMidiTickInterval(int incomingBpm)
{
  int crotchetInterval = US_IN_MINUTE / incomingBpm;
  int midiTickInterval = round(crotchetInterval / PPQN);
  return midiTickInterval;
}

void Midi_Clock::_reset()
{
  m_timer = 0;
  m_currentMidiTick = 0;
}

void Midi_Clock::updateMidiTickCounter()
{
  if(m_currentMidiTick < PPQN - 1)
  {
    m_currentMidiTick++;
  } else 
  {
    m_currentMidiTick = 0;
  }
}

int Midi_Clock::getMidiTick()
{
  return m_currentMidiTick;
}

bool Midi_Clock::isMidiTick32nd()                   
{
  return ((m_currentMidiTick % MODULO_32ND) == 0);
}

bool Midi_Clock::isMidiTick16th()                   
{
  return ((m_currentMidiTick % MODULO_16TH) == 0);
}

bool Midi_Clock::isMidiTick8th()                   
{
  return ((m_currentMidiTick % MODULO_8TH) == 0);
}

void Midi_Clock::poll()
{
  if(m_timer > m_midiTickInterval)                // if the timer has exceed the midi tick interval...
  {
    this->updateMidiTickCounter();                // ...update the midi tick counter.
    m_timer = 0;                                  // reset the timer. 
  }
}
