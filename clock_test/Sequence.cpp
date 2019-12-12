#include "Sequence.h"

Sequence::Sequence(Track *trackContainer[]){
  m_counter = 0;

  for(int i = 0; i < NUM_OF_TRACKS; i++){
    m_trackContainer[i] = trackContainer[i];
  }
}

// A counter to determine when the step needs to be incremented.
void Sequence::incrementCounter(){

  if(m_counter == 0){
    Serial.println("Step Event");
    // Increment the step counter of each track.
    for(int i = 0; i < NUM_OF_TRACKS; i++){
      if(m_trackContainer[i]->getActive() == true){
        m_trackContainer[i]->incrementCounter();
      }
    }
  }

  // Increment counter if less than 3.
  if(m_counter < 3){
    m_counter++;
  } else {
    m_counter = 0;
  }
}
