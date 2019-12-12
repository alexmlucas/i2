#include "Sequence.h"

unsigned long currentMillis;
unsigned long previousMillis = 0;
const int SECONDS_IN_MINUTE = 60000;
const float MULTIPLIER_32ND = 0.125;
int crotchetInterval;
int bpm = 120;
int play_flag = true;
int midiTickInterval;

Track trackContainer[8];
Track *p_trackContainer[] = {&trackContainer[0], &trackContainer[1], &trackContainer[2], &trackContainer[3], &trackContainer[4], &trackContainer[5], &trackContainer[6], &trackContainer[7]};

Sequence sequence(p_trackContainer);

void setup() {
  Serial.begin(31250);
  midiTickInterval = calculateMidiTickInterval(bpm);
  trackContainer[0].setActive(true);
}

void loop() {
  
  if(play_flag == true){
    currentMillis = millis();

    if(currentMillis - previousMillis > midiTickInterval){
      sequence.incrementCounter();
      previousMillis = currentMillis;
    }
  }
}

int calculateMidiTickInterval(int incomingBpm){
  float crotchetInterval = SECONDS_IN_MINUTE / incomingBpm;
  int midiTickInterval = crotchetInterval / 24;
  return midiTickInterval;
}
