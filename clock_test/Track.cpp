#include "Track.h"

Track::Track(){
  m_counter = 0;
  m_stepFrequency = 8; // default value?
  m_currentlyActive = false;
}

void Track::incrementCounter(){
  m_counter++;
  this->playSample();
}

void Track::resetCounter(){
  m_counter = 0;
}

void Track::setActive(bool currentlyActive){
  m_currentlyActive = currentlyActive;
  this->resetCounter();
}

bool Track::getActive(){
  return m_currentlyActive;
}

void Track::setStepFrequency(int stepFrequency){
  m_stepFrequency = stepFrequency;
}

// Rename to check if sample needs to be played
void Track::playSample(){
  if(m_counter % m_stepFrequency == 0){
    Serial.println("hit");
  }
}
