#include "Piezo_Trigger.h"
#include "Led.h"
#include "Sample.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=242,448
AudioPlaySdWav           playSdWav2; //xy=242,481
AudioPlaySdWav           playSdWav3; //xy=242,514
AudioPlaySdWav           playSdWav4; //xy=242,547
AudioPlaySdWav           playSdWav5; //xy=242,580
AudioPlaySdWav           playSdWav6; //xy=242,613
AudioPlaySdWav           playSdWav7; //xy=242,646
AudioPlaySdWav           playSdWav8; //xy=242,679
AudioMixer4              mixer1;         //xy=536,464
AudioMixer4              mixer3; //xy=536,590
AudioMixer4              mixer4; //xy=536,653
AudioMixer4              mixer2; //xy=537,527
AudioMixer4              mixer6; //xy=720,550
AudioMixer4              mixer5; //xy=721,483
AudioOutputI2S           i2s1; //xy=905,490
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer3, 0);
AudioConnection          patchCord3(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord4(playSdWav2, 1, mixer3, 1);
AudioConnection          patchCord5(playSdWav3, 0, mixer1, 2);
AudioConnection          patchCord6(playSdWav3, 1, mixer3, 2);
AudioConnection          patchCord7(playSdWav4, 0, mixer1, 3);
AudioConnection          patchCord8(playSdWav4, 1, mixer3, 3);
AudioConnection          patchCord9(playSdWav5, 0, mixer2, 0);
AudioConnection          patchCord10(playSdWav5, 1, mixer4, 0);
AudioConnection          patchCord11(playSdWav6, 0, mixer2, 1);
AudioConnection          patchCord12(playSdWav6, 1, mixer4, 1);
AudioConnection          patchCord13(playSdWav7, 0, mixer2, 2);
AudioConnection          patchCord14(playSdWav7, 1, mixer4, 2);
AudioConnection          patchCord15(playSdWav8, 0, mixer2, 3);
AudioConnection          patchCord16(playSdWav8, 1, mixer4, 3);
AudioConnection          patchCord17(mixer1, 0, mixer5, 0);
AudioConnection          patchCord18(mixer3, 0, mixer6, 0);
AudioConnection          patchCord19(mixer4, 0, mixer6, 1);
AudioConnection          patchCord20(mixer2, 0, mixer5, 1);
AudioConnection          patchCord21(mixer6, 0, i2s1, 1);
AudioConnection          patchCord22(mixer5, 0, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=239,783
// GUItool: end automatically generated code

// SD card definitions
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// create an array ofsample objects
Sample samples[8] = {(&playSdWav1), (&playSdWav2), (&playSdWav3), (&playSdWav4), (&playSdWav5), (&playSdWav6), (&playSdWav7), (&playSdWav8)};

// strings for loading samples

const unsigned long US_IN_MINUTE = 60000000;
const float MULTIPLIER_32ND = 0.125;
const int PPQN = 24;                  
const int SEQUENCE_LENGTH = 32;       
const int SEQUENCE_MODULO = 4;        // used when incrementing the sequenceCounter.
const int QUANTISE_MODULO = 3;        // used when incrementing the quantiseCounter.
//const int NUM_OF_QUANTISE_STEPS = 64;
const int NUM_OF_TRACKS = 8;          

bool playFlag = true;
int lastPlayFlag = false;
bool recordFlag = true;
bool drumEventFlag = false;
bool updateSequenceStepFlag = false;
int midiTickInterval = 0;
int currentMidiTick = 0;
int currentSequenceStep = 0;
int quantiseCounter = 0;
int bpm = 120;
elapsedMicros masterClockTimer = 0;

float sequence[SEQUENCE_LENGTH][NUM_OF_TRACKS];

Led drumLed(0);
Piezo_Trigger drum(A2);

void setup() {
  Serial.begin(31250);

  // setup the audio codec
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  // setup the SD card
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  // setup samples

  // set sample names - perhaps setup sample folder as a separate string and concatinate later.
  samples[0].setSampleName(String("kit_1/0.wav"));
  samples[1].setSampleName(String("kit_1/1.wav"));
  samples[2].setSampleName(String("kit_1/2.wav"));
  samples[3].setSampleName(String("kit_1/3.wav"));
  samples[4].setSampleName(String("kit_1/4.wav"));
  samples[5].setSampleName(String("kit_1/5.wav"));
  samples[6].setSampleName(String("kit_1/6.wav"));
  samples[7].setSampleName(String("kit_1/7.wav"));

  samples[0].setMixersAndChannels(&mixer1, &mixer3, 0, 0);
  samples[1].setMixersAndChannels(&mixer1, &mixer3, 1, 1);
  samples[2].setMixersAndChannels(&mixer1, &mixer3, 2, 2);
  samples[3].setMixersAndChannels(&mixer1, &mixer3, 3, 3);

  samples[4].setMixersAndChannels(&mixer2, &mixer4, 0, 0);
  samples[5].setMixersAndChannels(&mixer2, &mixer4, 1, 1);
  samples[6].setMixersAndChannels(&mixer2, &mixer4, 2, 2);
  samples[7].setMixersAndChannels(&mixer2, &mixer4, 3, 3);

  // set sample volumes
  for(int i = 0; i < (sizeof(samples) / sizeof(samples[0])); i++){    // sizeof(array) returns the number of bytes in the array.
    samples[i].setVolume(0.5);
  }
  
  midiTickInterval = calculateMidiTickInterval(bpm);

  while (!Serial && millis() < 2500);                 // wait for serial monitor

  // intialise the sequence
  for(int i = 0; i < SEQUENCE_LENGTH - 1; i++){

    for(int ii = 0; ii < NUM_OF_TRACKS - 1; ii++){
      sequence[i][ii] = 0;
    }
  }

  // plant a value in the sequencer.
  //sequence[0][0] = 0.5;
  //Serial.println(sequence[0][0]);
}

void loop() 
{

  
  if(playFlag)
  {
    if(playFlag != lastPlayFlag)                    // if the playState has just been activated...
    {                                             
      Serial.println("play button just pressed");
      Serial.println(currentSequenceStep);            // *** play the first step here ***
      masterClockTimer = 0;                           // reset the master clock timer
      lastPlayFlag = playFlag;                        // record the lastPlayState.
    }

    // everything else to occur at MIDI tick resoltion to avoid duplication of events.
    if(masterClockTimer > midiTickInterval)           // if the midiTickInterval in ms has been exceeded...
    {
      updateMidiTickCounter();

      if(playStep(3))                                 // if a 32nd step needs to be played...
      {
        updateCounter(&currentSequenceStep, SEQUENCE_LENGTH - 1);       // update the current step.
        Serial.println(currentSequenceStep);

        // *** play the step ***                                              
        for(int i = 0; i <= NUM_OF_TRACKS - 1; i++)                     // interate through tracks.       
        {                 
          float velocityValue = sequence[currentSequenceStep][i];   // get the velocity value at the index.
          Serial.println(float(velocityValue));

          if(velocityValue > 0)                                     // if velocity is above 0...
          {
            Serial.print("playing sample ");
            Serial.println(i);                            
            samples[i].playSample(velocityValue);                   // ...play the sample.
          }
        }
      }  

      masterClockTimer = 0;                                         // reset the master clock.
    }
  }

  double drumReading = drum.checkActivity();          // read and store trigger events

  if(drumReading > 0)
  {
    drumEventFlag = true;                             // flag that there has been a drum event.
    drumLed.pulse();                                  // pulse the drum LED.

    drumReading = map(drumReading, 0, 1023, 1, 10);   // scale reading to appropriate range for logarithmic curve
    drumReading = log10(drumReading);                 // apply logarithmic curve.

    samples[0].playSample(drumReading);               // perhaps play with velocity/volume?
    
  }
  
  drumLed.refresh();                                  // refresh LEDs.

  if(recordFlag && playFlag)                          // if record and play are active.
  {
    if(drumEventFlag)                                 // if a drum event has occured
    {
      int quantisedStep = getQuantisedStep();
      int selectedTrack = 0;                                    // an arbitrary value for now.
      Serial.print("recording to step ");
      Serial.println(quantisedStep);

      sequence[quantisedStep][selectedTrack] = drumReading;     // add the reading here.
      drumEventFlag = false;                                    // reset the flag. 
    }
  }
}

// check to see if a step needs to be played
bool playStep(int modulo){
  if(currentMidiTick % modulo == 0){
    return true;
  } else {
    return false;
  }
}

void updateCounter(int* counter, int maxValue){
  if(*counter < maxValue){       
    (*counter)++;
  } else {
    *counter = 0;
  }
}

// counts midi ticks.
void updateMidiTickCounter(){  
  if(currentMidiTick < PPQN - 1){
    currentMidiTick++;
  } else {
    currentMidiTick = 0;
  }
}

// get quantised step value
int getQuantisedStep(){
  // need to factor how 0 and 31 are dealt with!
  int quantiseModulo = currentMidiTick % QUANTISE_MODULO;     // There are three midi ticks per 32nd step. which one are we on?...
  float quantiseFloat = quantiseModulo * 0.333;               // Divide the value by three to get a float ready for rounding.
  int quantisedStep = round(currentSequenceStep + quantiseFloat);  // get the quantised step by adding the float to the current step, then rounding.
  
  if(quantisedStep == 32){                                    // accomodate wrap-around from 31 to 0
    quantisedStep = 0;
  }
  
  return quantisedStep;    
}

int calculateMidiTickInterval(int incomingBpm){
  int crotchetInterval = US_IN_MINUTE / incomingBpm;
  int midiTickInterval = round(crotchetInterval / 24);
  return midiTickInterval;
}
