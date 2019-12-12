#ifndef TRACK
#define TRACK
#include "Arduino.h"

class Track{
  private:
    int m_counter;
    int m_stepFrequency;
    bool m_currentlyActive;

  public:
    Track();
    void incrementCounter();
    void resetCounter();
    void setActive(bool currentlyActive);
    bool getActive();
    void setStepFrequency(int stepFrequency);
    void playSample();
};

#endif
