#ifndef SEQUENCE
#define SEQUENCE
#include "Arduino.h"
#include "Track.h"

const int NUM_OF_TRACKS = 8;

class Sequence{
  private:
    int m_counter;
    Track *m_trackContainer[NUM_OF_TRACKS];
    
  public:
    Sequence(Track *trackContainer[NUM_OF_TRACKS]);
    void incrementCounter();
};

#endif
