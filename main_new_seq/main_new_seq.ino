const unsigned long US_IN_MINUTE = 60000000;
const float MULTIPLIER_32ND = 0.125;
const int PPQN = 24;
const int PATTERN_LENGTH = 32;

int playFlag = true;
int midiTickInterval = 0;
int midiTickCounter = 0;
int patternCounter = 0;
int bpm = 120;
elapsedMicros masterClockTimer = 0;

void setup() {
  Serial.begin(31250);
  midiTickInterval = calculateMidiTickInterval(bpm);
  while (!Serial && millis() < 2500) /* wait for serial monitor */ ;
  Serial.println(midiTickInterval);
}

void loop() {
  if(playFlag == true) {

    
    // check to see if the midi tick counter needs to be updated.
    if(masterClockTimer > midiTickInterval){
      updateMidiTickCounter();

      // check to see if the pattern counter needs to be updated.
      updatePatternCounter32();

      // reset the master clock timer
      masterClockTimer = 0;
    }
  }
}

// Counts 32nd pattern step.
void updatePatternCounter32(){
  int pattern32Modulo = 4;  // the modulo value required to identify 32nd step events.

  // if equal to zero, update value...
  if(midiTickCounter % pattern32Modulo == 0){
    if(patternCounter < PATTERN_LENGTH){
      patternCounter++;
    } else {
      patternCounter = 0;
    }
    Serial.println(patternCounter);    
  }
}

// counts midi ticks.
void updateMidiTickCounter(){  
  if(midiTickCounter < PPQN){
    midiTickCounter++;
  } else {
    midiTickCounter = 0;
  }
}

int calculateMidiTickInterval(int incomingBpm){
  int crotchetInterval = US_IN_MINUTE / incomingBpm;
  int midiTickInterval = round(crotchetInterval / 24);
  return midiTickInterval;
}
