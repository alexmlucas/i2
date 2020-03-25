#include "Track.h"

Track::Track(){
  m_stepCounter = 0;
  m_stepFrequency = 8; // default value?
  m_currentlyActive = false;
}

void Track::incrementStepCounter(){
  this->playSample();
  m_stepCounter++;
}

void Track::resetStepCounter(){
  m_stepCounter = 0;
}

void Track::setActive(bool currentlyActive){
  m_currentlyActive = currentlyActive;
  this->resetStepCounter();
}

bool Track::getActive(){
  return m_currentlyActive;
}

void Track::setStepFrequency(int stepFrequency){
  m_stepFrequency = stepFrequency;
}

void Track::setSample(Sample *sample){
  m_sample = sample;
}

// Rename to check if sample needs to be played
void Track::playSample(){
  
  if(m_stepCounter % m_stepFrequency == 0){
    m_sample->playSample();
  }
}