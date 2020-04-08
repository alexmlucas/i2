const unsigned long US_IN_MINUTE = 60000000;
const float MULTIPLIER_32ND = 0.125;
const int PPQN = 24;
const int PATTERN_LENGTH = 32;
const int PATTERN_MODULO = 4;     // used when incrementing the patternCounter.
const int QUANTISE_MODULO = 3;    // used when incrementing the quantiseCounter.
const int NUM_OF_QUANTISE_STEPS = 64;
const int NUM_OF_TRACKS = 8;

int playFlag = true;
int recordFlag = true;
int midiTickInterval = 0;
int midiTickCounter = 0;
int patternCounter = 0;
int quantiseCounter = 0;
int bpm = 120;
elapsedMicros masterClockTimer = 0;

byte sequence[PATTERN_LENGTH][NUM_OF_TRACKS];

void setup() {
  Serial.begin(31250);
  midiTickInterval = calculateMidiTickInterval(bpm);
  while (!Serial && millis() < 2500) /* wait for serial monitor */ ;
  Serial.println(midiTickInterval);

  // intialise sequence.
  for(int i = 0; i < PATTERN_LENGTH; i++){

    for(int ii = 0; ii < NUM_OF_TRACKS; ii++){
      sequence[i][ii] = 0;
    }
  }
}

void loop() {
  // read and store trigger events

  // if playing...
  if(playFlag == true) {
    // update the pattern counter if needed.
    updateCounter(&patternCounter, PATTERN_MODULO, PATTERN_LENGTH);

    // if recording...
    if(recordFlag == true){
      // add stored events to sequence if they occured previously.
    }

    // check to see if the midi tick counter needs to be updated.
    if(masterClockTimer > midiTickInterval){
      updateMidiTickCounter();

      // reset the master clock timer
      masterClockTimer = 0;
    }
  }
}

void updateCounter(int* counter, int modulo, int maxValue){
  if(midiTickCounter % modulo == 0){
    //Serial.println("32nd");
    if(*counter < maxValue){
      (*counter)++;
    } else {
      *counter = 0;
    }
    Serial.println(*counter);
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

// quantise trigger events. 
int quantise(){
  int quantiseModulo = midiTickCounter % QUANTISE_MODULO;     // There are three midi ticks per 32nd step. which one are we on?...
  float quantiseFloat = quantiseModulo * 0.333;               // Divide the vale by three to get a float ready for rounding.
  int quantisedStep = round(patternCounter + quantiseFloat);  // get the quantised step by adding the float to the current step, then rounding.
  return quantisedStep;    
}

int calculateMidiTickInterval(int incomingBpm){
  int crotchetInterval = US_IN_MINUTE / incomingBpm;
  int midiTickInterval = round(crotchetInterval / 24);
  return midiTickInterval;
}
