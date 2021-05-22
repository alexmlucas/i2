#include "Midi_Clock.h"

Midi_Clock::Midi_Clock(bool isMaster)
{
  m_bpm = DEFAULT_BPM;
  m_midiTickInterval = this->calculateMidiTickInterval(m_bpm);
  m_runFlag = false;
  m_isMaster = isMaster;
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

bool Midi_Clock::isMidiTick4th()                   
{
  return ((m_currentMidiTick % MODULO_4TH) == 0);
}

void Midi_Clock::poll()
{
  if(m_runFlag)
  {  
    if(m_timer > m_midiTickInterval)                // if the timer has exceed the midi tick interval...
    {
      if(m_isMaster)
      {
        usbMIDI.sendRealTime(usbMIDI.Clock);        // send midi_tick.
      }
      
      this->updateMidiTickCounter();                // ...update the midi tick counter.
      m_timer = 0;                                  // reset the timer. 
    }    
  }
}

void Midi_Clock::setRunFlag(int state)
{
  m_runFlag = state;
}

void Midi_Clock::setBpm(int bpm)
{
  m_bpm = bpm;
  m_midiTickInterval = this->calculateMidiTickInterval(m_bpm);
}

void Midi_Clock::incrementBpm()
{
  if(m_bpm < 300)
  {
    m_bpm = m_bpm + 5;
    m_midiTickInterval = this->calculateMidiTickInterval(m_bpm);
  }
}

void Midi_Clock::decrementBpm()
{
  if(m_bpm > 20)
  {
    m_bpm = m_bpm - 5;
    m_midiTickInterval = this->calculateMidiTickInterval(m_bpm);
  }
}

int Midi_Clock::getBpm()
{
  return m_bpm;
}

