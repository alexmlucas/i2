#include "Master_Clock.h"

Master_Clock::Master_Clock(int bpm)
{
  m_bpm = bpm;
  m_midiTickInterval = this->calculateMidiTickInterval(bpm);
}

int Master_Clock::calculateMidiTickInterval(int incomingBpm)
{
  int crotchetInterval = US_IN_MINUTE / incomingBpm;
  int midiTickInterval = round(crotchetInterval / PPQN);
  return midiTickInterval;
}

void Master_Clock::resetTimer()
{
  m_timer = 0;
}

void Master_Clock::updateMidiTickCounter()
{
  if(m_currentMidiTick < PPQN - 1)
  {
    m_currentMidiTick++;
  } else 
  {
    m_currentMidiTick = 0;
  }
}

int Master_Clock::getMidiTick()
{
  return m_currentMidiTick;
}

bool Master_Clock::isMidiTick32nd()                   
{
  return ((m_currentMidiTick % 3) == 0);
}

void Master_Clock::poll()
{
  if(m_timer > m_midiTickInterval)                // if the timer has exceed the midi tick interval...
  {
    this->updateMidiTickCounter();                // ...update the midi tick counter.
    this->resetTimer();                           // reset the timer. 
  }
}
