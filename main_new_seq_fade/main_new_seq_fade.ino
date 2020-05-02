#include "Piezo_Trigger.h"
#include "Led.h"
#include "Sample_Player.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=108.77777099609375,763.7777709960938
AudioPlaySdWav           playSdWav2;     //xy=108.88888549804688,829.999979019165
AudioPlaySdWav           playSdWav7;     //xy=109.55554962158203,1163.3333806991577
AudioPlaySdWav           playSdWav3;     //xy=110.88888168334961,896.6666488647461
AudioPlaySdWav           playSdWav8;     //xy=109.77777099609375,1229.2222995758057
AudioPlaySdWav           playSdWav6;     //xy=110.77776336669922,1096.4445295333862
AudioPlaySdWav           playSdWav4;     //xy=111.77777099609375,963.2222337722778
AudioPlaySdWav           playSdWav5;     //xy=113.11109924316406,1030.8889980316162
AudioEffectFade          fade1;          //xy=266.6666488647461,756.6667098999023
AudioEffectFade          fade2;          //xy=266.66667556762695,789.999997138977
AudioEffectFade          fade3;          //xy=266.66665267944336,823.3332506418228
AudioEffectFade          fade4;          //xy=266.6666564941406,856.6665922403336
AudioEffectFade          fade5;          //xy=266.6666679382324,889.9999347925186
AudioEffectFade          fade6;          //xy=267.77775955200195,923.3333368301392
AudioEffectFade          fade7;          //xy=268.7777786254883,956.6666927337646
AudioEffectFade          fade8;          //xy=268.7777976989746,990.0000276565552
AudioEffectFade          fade9;          //xy=268.88888931274414,1023.3333358764648
AudioEffectFade          fade10;         //xy=268.99998474121094,1056.6666841506958
AudioEffectFade          fade11;         //xy=269.8888931274414,1090.0001020431519
AudioEffectFade          fade12;         //xy=270.00000381469727,1123.3332595825195
AudioEffectFade          fade13;         //xy=270.00000762939453,1156.6666374206543
AudioEffectFade          fade14;         //xy=270.00000762939453,1189.9999179840088
AudioEffectFade          fade15;         //xy=270.00000762939453,1223.3332424163818
AudioEffectFade          fade16;         //xy=269.99999237060547,1256.6666870117188
AudioMixer4              mixer3;         //xy=547.2222137451172,915.2222328186035
AudioMixer4              mixer4;         //xy=547.2222137451172,983.2222328186035
AudioMixer4              mixer1;         //xy=548.2222137451172,775.2222328186035
AudioMixer4              mixer2;         //xy=548.2222137451172,845.2222328186035
AudioMixer4              mixer5;         //xy=683.2222137451172,795.2222328186035
AudioMixer4              mixer6;         //xy=685.2222137451172,935.2222328186035
AudioOutputI2S           i2s1;           //xy=824.2222137451172,802.2222328186035
AudioConnection          patchCord1(playSdWav1, 0, fade1, 0);
AudioConnection          patchCord2(playSdWav1, 1, fade2, 0);
AudioConnection          patchCord3(playSdWav2, 0, fade3, 0);
AudioConnection          patchCord4(playSdWav2, 1, fade4, 0);
AudioConnection          patchCord5(playSdWav7, 0, fade13, 0);
AudioConnection          patchCord6(playSdWav7, 1, fade14, 0);
AudioConnection          patchCord7(playSdWav3, 0, fade5, 0);
AudioConnection          patchCord8(playSdWav3, 1, fade6, 0);
AudioConnection          patchCord9(playSdWav8, 0, fade15, 0);
AudioConnection          patchCord10(playSdWav8, 1, fade16, 0);
AudioConnection          patchCord11(playSdWav6, 0, fade11, 0);
AudioConnection          patchCord12(playSdWav6, 1, fade12, 0);
AudioConnection          patchCord13(playSdWav4, 0, fade7, 0);
AudioConnection          patchCord14(playSdWav4, 1, fade8, 0);
AudioConnection          patchCord15(playSdWav5, 0, fade9, 0);
AudioConnection          patchCord16(playSdWav5, 1, fade10, 0);
AudioConnection          patchCord17(fade1, 0, mixer1, 0);
AudioConnection          patchCord18(fade2, 0, mixer3, 0);
AudioConnection          patchCord19(fade3, 0, mixer1, 1);
AudioConnection          patchCord20(fade4, 0, mixer3, 1);
AudioConnection          patchCord21(fade5, 0, mixer1, 2);
AudioConnection          patchCord22(fade6, 0, mixer3, 2);
AudioConnection          patchCord23(fade7, 0, mixer1, 3);
AudioConnection          patchCord24(fade8, 0, mixer3, 3);
AudioConnection          patchCord25(fade9, 0, mixer2, 0);
AudioConnection          patchCord26(fade10, 0, mixer4, 0);
AudioConnection          patchCord27(fade11, 0, mixer2, 1);
AudioConnection          patchCord28(fade12, 0, mixer4, 1);
AudioConnection          patchCord29(fade13, 0, mixer2, 2);
AudioConnection          patchCord30(fade14, 0, mixer4, 2);
AudioConnection          patchCord31(fade15, 0, mixer2, 3);
AudioConnection          patchCord32(fade16, 0, mixer4, 3);
AudioConnection          patchCord33(mixer3, 0, mixer6, 0);
AudioConnection          patchCord34(mixer4, 0, mixer6, 1);
AudioConnection          patchCord35(mixer1, 0, mixer5, 0);
AudioConnection          patchCord36(mixer2, 0, mixer5, 1);
AudioConnection          patchCord37(mixer5, 0, i2s1, 0);
AudioConnection          patchCord38(mixer6, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=102.77777099609375,1571.7777709960938
// GUItool: end automatically generated code

// SD card definitions
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// create an array of samplePlayer objects
Sample_Player samplePlayers[8] = {(&playSdWav1), (&playSdWav2), (&playSdWav3), (&playSdWav4), (&playSdWav5), (&playSdWav6), (&playSdWav7), (&playSdWav8)};

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
elapsedMillis testTimer = 0;

float sequence[SEQUENCE_LENGTH][NUM_OF_TRACKS];
float quantiseQueue[8];

Led drumLed(0);
Piezo_Trigger drum(A2);

void setup() 
{
  Serial.begin(31250);

  // setup the audio codec
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  // setup the SD card
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  
  if (!(SD.begin(SDCARD_CS_PIN))) 
  {
    while (1) 
    {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  // ### setup sample players ###

  // set sample names - perhaps setup sample folder as a separate string and concatinate later.
  samplePlayers[0].setSampleName(String("kit_1/0.wav"));
  samplePlayers[1].setSampleName(String("kit_1/1.wav"));
  samplePlayers[2].setSampleName(String("kit_1/2.wav"));
  samplePlayers[3].setSampleName(String("kit_1/3.wav"));
  samplePlayers[4].setSampleName(String("kit_1/4.wav"));
  samplePlayers[5].setSampleName(String("kit_1/5.wav"));
  samplePlayers[6].setSampleName(String("kit_1/6.wav"));
  samplePlayers[7].setSampleName(String("kit_1/7.wav"));

  samplePlayers[0].assignFadeObjects(&fade1, &fade2);
  samplePlayers[1].assignFadeObjects(&fade3, &fade4);
  samplePlayers[2].assignFadeObjects(&fade5, &fade6);
  samplePlayers[3].assignFadeObjects(&fade7, &fade8);
  samplePlayers[4].assignFadeObjects(&fade9, &fade10);
  samplePlayers[5].assignFadeObjects(&fade11, &fade12);
  samplePlayers[6].assignFadeObjects(&fade13, &fade14);
  samplePlayers[7].assignFadeObjects(&fade15, &fade16);

  samplePlayers[0].assignMixerObjects(&mixer1, &mixer3, 0, 0);
  samplePlayers[1].assignMixerObjects(&mixer1, &mixer3, 1, 1);
  samplePlayers[2].assignMixerObjects(&mixer1, &mixer3, 2, 2);
  samplePlayers[3].assignMixerObjects(&mixer1, &mixer3, 3, 3);

  samplePlayers[4].assignMixerObjects(&mixer2, &mixer4, 0, 0);
  samplePlayers[5].assignMixerObjects(&mixer2, &mixer4, 1, 1);
  samplePlayers[6].assignMixerObjects(&mixer2, &mixer4, 2, 2);
  samplePlayers[7].assignMixerObjects(&mixer2, &mixer4, 3, 3);
  
  midiTickInterval = calculateMidiTickInterval(bpm);

  while (!Serial && millis() < 2500);                               // wait for serial monitor

  // intialise the sequence
  for(int i = 0; i < SEQUENCE_LENGTH - 1; i++)
  {
    for(int ii = 0; ii < NUM_OF_TRACKS - 1; ii++)
    {
      sequence[i][ii] = 0;
    }
  }
}

void loop() 
{
  for(int i = 0; i < NUM_OF_TRACKS - 1; i++)                        // poll all samples.
  {
    samplePlayers[i].poll();
  }
  
  if(playFlag)
  {
    if(playFlag != lastPlayFlag)                                    // if the playState has just been activated...
    {                                             
      Serial.println("play button just pressed");
      Serial.println(currentSequenceStep);                          // *** play the first step here ***
      masterClockTimer = 0;                                         // reset the master clock timer
      lastPlayFlag = playFlag;                                      // record the lastPlayState.
    }

    // everything else to occur at MIDI tick resoltion to avoid duplication of events.
    if(masterClockTimer > midiTickInterval)                         // if the midiTickInterval in ms has been exceeded...
    {
      updateMidiTickCounter();

      if(playStep(3))                                               // if a 32nd step needs to be played...
      {
        updateCounter(&currentSequenceStep, SEQUENCE_LENGTH - 1);   // update the current step.

        // *** play the step ***                                              
        for(int i = 0; i <= NUM_OF_TRACKS - 1; i++)                 // interate through tracks.       
        {                 
          float velocity = sequence[currentSequenceStep][i];        // get the velocity value at the index.

          if(velocity > 0)                                          // if velocity is above 0...
          {                          
            samplePlayers[i].processTriggerEvent(velocity);         // ...play the sample.
          }
        }

        // add queued events to sequence...

        for(int i = 0; i <= NUM_OF_TRACKS - 1; i++)                 // interate through tracks.       
        {
          float velocity = quantiseQueue[i];
                           
          if(velocity > 0)                                          // if velocity is above 0...
          {
            sequence[currentSequenceStep][i] = velocity;            // add the value to the sequence
            quantiseQueue[i] = 0;                                   // reset the value.              
          }
        }
      }
      masterClockTimer = 0;                                         // reset the master clock.
    }
  }

  double drumReading = drum.checkActivity();                        // read and store trigger events

  if(drumReading > 0)
  {
    drumEventFlag = true;                                           // flag that there has been a drum event.
    drumLed.pulse();                                                // pulse the drum LED.

    drumReading = map(drumReading, 0, 1023, 1, 10);                 // scale reading to appropriate range for logarithmic curve
    drumReading = log10(drumReading);                               // apply logarithmic curve.
    
    samplePlayers[0].processTriggerEvent(drumReading);               
  }

  samplePlayers[0].poll();
  drumLed.refresh();                                                // refresh LEDs.

  if(recordFlag && playFlag)                                        // if record and play are active.
  {
    if(drumEventFlag)                                               // if a drum event has occured
    {
      int quantisedStep = getQuantisedStep();
      int selectedTrack = 0;                                        // a hard coded value for now. will be dependent on trigger source.

      if(quantisedStep == currentSequenceStep)                      // if quantised to the current step...
      {
        sequence[currentSequenceStep][selectedTrack] = drumReading; // ...add reading sequence immediately - this step won't play again until the next sequence iteration.
      } else                                                        // else, it has been quantised to the next step, therefore...
      {
        quantiseQueue[selectedTrack] = drumReading;                 //...add to the queue
      }                                       
    }
  }

  drumEventFlag = false;                                            // reset the flag.
}

// check to see if a step needs to be played
bool playStep(int modulo)
{
  if(currentMidiTick % modulo == 0)
  {
    return true;
  } else
  {
    return false;
  }
}

void updateCounter(int* counter, int maxValue)
{
  if(*counter < maxValue)
  {       
    (*counter)++;
  } else
  {
    *counter = 0;
  }
}

// counts midi ticks.
void updateMidiTickCounter()
{  
  if(currentMidiTick < PPQN - 1)
  {
    currentMidiTick++;
  } else 
  {
    currentMidiTick = 0;
  }
}

// get quantised step value
int getQuantisedStep()
{
  int quantiseModulo = currentMidiTick % QUANTISE_MODULO;           // There are three midi ticks per 32nd step. which one are we on?...
  float quantiseFloat = quantiseModulo * 0.333;                     // Divide the value by three to get a float ready for rounding.
  int quantisedStep = round(currentSequenceStep + quantiseFloat);   // get the quantised step by adding the float to the current step, then rounding.
  
  if(quantisedStep == 32)                                           // accomodate wrap-around from 31 to 0
  {                                          
    quantisedStep = 0;
  }
  
  return quantisedStep;    
}

int calculateMidiTickInterval(int incomingBpm)
{
  int crotchetInterval = US_IN_MINUTE / incomingBpm;
  int midiTickInterval = round(crotchetInterval / 24);
  return midiTickInterval;
}
