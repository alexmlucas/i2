#ifndef TRACK
#define TRACK
#include "Arduino.h"
#include "Sample.h"

class Track{
  private:
    int m_stepCounter;
    int m_stepFrequency;
    bool m_currentlyActive;
    Sample *m_sample;

  public:
    Track();
    void incrementStepCounter();
    void resetStepCounter();
    void setActive(bool currentlyActive);
    bool getActive();
    void setStepFrequency(int stepFrequency);
    void setSample(Sample *sample);
    void playSample();
};

#endif
