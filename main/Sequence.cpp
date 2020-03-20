#include "Sequence.h"

Sequence::Sequence(Track *trackContainer[]){
  m_midiTickCounter = 0;

  for(int i = 0; i < NUM_OF_TRACKS; i++){
    m_trackContainer[i] = trackContainer[i];
  }
}

// A counter to determine when the step needs to be incremented.
void Sequence::updateMidiTickCounter(){

  // A 32nd step event occurs each time the midiTickCounter hits zero.
  if(m_midiTickCounter == 0){
    //Serial.println("32nd Step Event");
    
    // Increment the step counter of each track. (Perhaps a separate function for this would be beneficial?)
    for(int i = 0; i < NUM_OF_TRACKS; i++){
      if(m_trackContainer[i]->getActive() == true){
        m_trackContainer[i]->incrementStepCounter();
      }
    }
  }

  if(m_midiTickCounter < 2){
    m_midiTickCounter++;
  } else {
    m_midiTickCounter = 0;
  }
}
