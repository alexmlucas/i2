#include "Piezo_Trigger.h"
#include "Led.h"
#include "Sample_Player.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav2;     //xy=489.57141494750977,734.0000581741333
AudioPlaySdWav           playSdWav1;     //xy=490.5714416503906,660.857177734375
AudioPlaySdWav           playSdWav3;     //xy=491.4286308288574,804.2857522964478
AudioPlaySdWav           playSdWav5;     //xy=491.0000915527344,946.2858190536499
AudioPlaySdWav           playSdWav6;     //xy=492.00001525878906,1016.5715847015381
AudioPlaySdWav           playSdWav8;     //xy=491.57144927978516,1151.8573150634766
AudioPlaySdWav           playSdWav7;     //xy=493.00006103515625,1084.0001873970032
AudioPlaySdWav           playSdWav4;     //xy=493.85722732543945,875.000150680542
AudioEffectEnvelope      envelope1;      //xy=662.857063293457,654.2856769561768
AudioEffectEnvelope      envelope2;      //xy=662.8571128845215,690.0000228881836
AudioEffectEnvelope      envelope3;      //xy=664.2857208251953,725.7143430709839
AudioEffectEnvelope      envelope4;      //xy=664.2857246398926,761.4286184310913
AudioEffectEnvelope      envelope9;      //xy=664.2857360839844,938.5714807510376
AudioEffectEnvelope      envelope5;      //xy=665.7143173217773,797.1428699493408
AudioEffectEnvelope      envelope6;      //xy=665.7142524719238,832.8570938110352
AudioEffectEnvelope      envelope7;      //xy=665.7143287658691,868.5714511871338
AudioEffectEnvelope      envelope8;      //xy=665.7142677307129,904.2857341766357
AudioEffectEnvelope      envelope10;     //xy=668.5713844299316,974.2856111526489
AudioEffectEnvelope      envelope11;     //xy=668.5714530944824,1008.5714807510376
AudioEffectEnvelope      envelope12;     //xy=668.5714530944824,1042.8571767807007
AudioEffectEnvelope      envelope13;     //xy=668.5714092254639,1078.5713920593262
AudioEffectEnvelope      envelope14;     //xy=668.5714149475098,1112.8571062088013
AudioEffectEnvelope      envelope15;     //xy=668.5713958740234,1147.1429243087769
AudioEffectEnvelope      envelope16;     //xy=670.0000076293945,1181.4285154342651
AudioMixer4              mixer3;         //xy=974.2857246398926,817.142894744873
AudioMixer4              mixer4;         //xy=974.2857151031494,885.71435546875
AudioMixer4              mixer1;         //xy=975.7142868041992,677.1428375244141
AudioMixer4              mixer2;         //xy=975.7143211364746,747.1428871154785
AudioMixer4              mixer5;         //xy=1110.0001201629639,697.1428451538086
AudioMixer4              mixer6;         //xy=1112.8571586608887,837.1428861618042
AudioOutputI2S           i2s1;           //xy=1251.571460723877,704.1428623199463
AudioConnection          patchCord1(playSdWav2, 0, envelope3, 0);
AudioConnection          patchCord2(playSdWav2, 1, envelope4, 0);
AudioConnection          patchCord3(playSdWav1, 0, envelope1, 0);
AudioConnection          patchCord4(playSdWav1, 1, envelope2, 0);
AudioConnection          patchCord5(playSdWav3, 0, envelope5, 0);
AudioConnection          patchCord6(playSdWav3, 1, envelope6, 0);
AudioConnection          patchCord7(playSdWav5, 0, envelope9, 0);
AudioConnection          patchCord8(playSdWav5, 1, envelope10, 0);
AudioConnection          patchCord9(playSdWav6, 0, envelope11, 0);
AudioConnection          patchCord10(playSdWav6, 1, envelope12, 0);
AudioConnection          patchCord11(playSdWav8, 0, envelope15, 0);
AudioConnection          patchCord12(playSdWav8, 1, envelope16, 0);
AudioConnection          patchCord13(playSdWav7, 0, envelope13, 0);
AudioConnection          patchCord14(playSdWav7, 1, envelope14, 0);
AudioConnection          patchCord15(playSdWav4, 0, envelope7, 0);
AudioConnection          patchCord16(playSdWav4, 1, envelope8, 0);
AudioConnection          patchCord17(envelope1, 0, mixer1, 0);
AudioConnection          patchCord18(envelope2, 0, mixer3, 0);
AudioConnection          patchCord19(envelope3, 0, mixer1, 1);
AudioConnection          patchCord20(envelope4, 0, mixer3, 1);
AudioConnection          patchCord21(envelope9, 0, mixer2, 0);
AudioConnection          patchCord22(envelope5, 0, mixer1, 2);
AudioConnection          patchCord23(envelope6, 0, mixer3, 2);
AudioConnection          patchCord24(envelope7, 0, mixer1, 3);
AudioConnection          patchCord25(envelope8, 0, mixer3, 3);
AudioConnection          patchCord26(envelope10, 0, mixer4, 0);
AudioConnection          patchCord27(envelope11, 0, mixer2, 1);
AudioConnection          patchCord28(envelope12, 0, mixer4, 1);
AudioConnection          patchCord29(envelope13, 0, mixer2, 2);
AudioConnection          patchCord30(envelope14, 0, mixer4, 2);
AudioConnection          patchCord31(envelope15, 0, mixer2, 3);
AudioConnection          patchCord32(envelope16, 0, mixer4, 3);
AudioConnection          patchCord33(mixer3, 0, mixer6, 0);
AudioConnection          patchCord34(mixer4, 0, mixer6, 1);
AudioConnection          patchCord35(mixer1, 0, mixer5, 0);
AudioConnection          patchCord36(mixer2, 0, mixer5, 1);
AudioConnection          patchCord37(mixer5, 0, i2s1, 0);
AudioConnection          patchCord38(mixer6, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=484.28576278686523,1468.8572425842285
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

struct Step_Queue
{
  float volumeValues[8];
  int queuePositions[8];
};

Step_Queue sequenceRecordQueue[SEQUENCE_LENGTH];
float sequence[SEQUENCE_LENGTH][NUM_OF_TRACKS];

Led drumLed(0);
Piezo_Trigger drum(A2);

void setup() 
{
  Serial.begin(31250);

  // setup the audio codec
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.3);

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

  // ### setup samples ###

  // set sample names - perhaps setup sample folder as a separate string and concatinate later.
  samplePlayers[0].setSampleName(String("sine_2.wav"));
  samplePlayers[1].setSampleName(String("kit_1/1.wav"));
  samplePlayers[2].setSampleName(String("kit_1/2.wav"));
  samplePlayers[3].setSampleName(String("kit_1/3.wav"));
  samplePlayers[4].setSampleName(String("kit_1/4.wav"));
  samplePlayers[5].setSampleName(String("kit_1/5.wav"));
  samplePlayers[6].setSampleName(String("kit_1/6.wav"));
  samplePlayers[7].setSampleName(String("kit_1/7.wav"));

  samplePlayers[0].assignEnvelopeObjects(&envelope1, &envelope2);
  samplePlayers[1].assignEnvelopeObjects(&envelope3, &envelope4);
  samplePlayers[2].assignEnvelopeObjects(&envelope5, &envelope6);
  samplePlayers[3].assignEnvelopeObjects(&envelope7, &envelope8);
  samplePlayers[4].assignEnvelopeObjects(&envelope9, &envelope10);
  samplePlayers[5].assignEnvelopeObjects(&envelope11, &envelope12);
  samplePlayers[6].assignEnvelopeObjects(&envelope13, &envelope14);
  samplePlayers[7].assignEnvelopeObjects(&envelope15, &envelope16);

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

  // initialise the record queue
  for(int i = 0; i < SEQUENCE_LENGTH - 1; i++)
  {
    for(int ii = 0; ii < NUM_OF_TRACKS - 1; ii++)
    {
      sequenceRecordQueue[i].volumeValues[ii] = 0.0;
      sequenceRecordQueue[i].queuePositions[ii] = 0;
    }
  }
}

void loop() 
{
  /*for(int i = 0; i < NUM_OF_TRACKS - 1; i++)          // poll all samples.
  {
    samplePlayers[i].pollEvents();
  }*/

  
  /*if(playFlag)
  {
    if(playFlag != lastPlayFlag)                      // if the playState has just been activated...
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
        updateCounter(&currentSequenceStep, SEQUENCE_LENGTH - 1);   // update the current step.
        //Serial.println(currentSequenceStep);

        // *** play the step ***                                              
        for(int i = 0; i <= NUM_OF_TRACKS - 1; i++)                 // interate through tracks.       
        {                 
          float velocityValue = sequence[currentSequenceStep][i];   // get the velocity value at the index.

          if(velocityValue > 0)                                     // if velocity is above 0...
          {
            Serial.print("playing sample ");
            Serial.println(i);                            
            samplePlayers[i].playSample(velocityValue);                   // ...play the sample.
            Serial.print("at step: ");
            Serial.println(currentSequenceStep);
            Serial.println("");
          }
        }

        // decrement all active steps in the record queue.
        if(currentSequenceStep == 0)
        {
          for(int stepIterator = 0; stepIterator < SEQUENCE_LENGTH - 1; stepIterator++)
          {
            for(int trackIterator = 0; trackIterator < NUM_OF_TRACKS - 1; trackIterator++)
            {
              int queuePosition = sequenceRecordQueue[stepIterator].queuePositions[trackIterator];    // get the queue position
              
              if(queuePosition > 0)                                                                   // if the queue position is above 0
              {
                sequenceRecordQueue[stepIterator].queuePositions[trackIterator] -= 1;                 // ...decrement
              }
            }
          }
        }
      }  
      masterClockTimer = 0;                                         // reset the master clock.
    }
  }*/

  double drumReading = drum.checkActivity();          // read and store trigger events

  if(drumReading > 0)
  {
    drumEventFlag = true;                             // flag that there has been a drum event.
    drumLed.pulse();                                  // pulse the drum LED.

    drumReading = map(drumReading, 0, 1023, 1, 10);   // scale reading to appropriate range for logarithmic curve
    drumReading = log10(drumReading);                 // apply logarithmic curve.

    Serial.println(drumReading);

    samplePlayers[0].processTriggerEvent(drumReading);               
  }

  samplePlayers[0].poll();
  drumLed.refresh();                                  // refresh LEDs.

  /*if(recordFlag && playFlag)                                                // if record and play are active.
  {
    if(drumEventFlag)                                                       // if a drum event has occured
    {
      int quantisedStep = getQuantisedStep();
      int selectedTrack = 0;                                                // a hard coded value for now.
      Serial.print("recording to step ");
      Serial.println(quantisedStep);                                        

      //sequence[quantisedStep][selectedTrack] = drumReading;               // add the reading here. (need to wait until the next loop before adding.)
      sequenceRecordQueue[quantisedStep].volumeValues[selectedTrack] = drumReading;
      sequenceRecordQueue[quantisedStep].queuePositions[selectedTrack] = 1;
     
      drumEventFlag = false;                                    // reset the flag. 
    }
  }

  // add record events to queue here...
  for(int stepIterator = 0; stepIterator < SEQUENCE_LENGTH - 1; stepIterator++)
  {
    for(int trackIterator = 0; trackIterator < NUM_OF_TRACKS - 1; trackIterator++)
    {
      float volumeValue = sequenceRecordQueue[stepIterator].volumeValues[trackIterator];    // get the volume value
      
      if(volumeValue > 0)                                                                   // if a volume value exists.
      {
        if(sequenceRecordQueue[stepIterator].queuePositions[trackIterator] == 0)             // if at the last queue position...
        {
           sequence[stepIterator][trackIterator] = volumeValue;                             // ...add to the sequence.
           sequenceRecordQueue[stepIterator].volumeValues[trackIterator] = 0.0;             // ...clear the value. 
        }
      }
    }
  }

  //int fadeTime = 3;

  //samplePlayers[0].playSample(0.8);
  //delay(2);
  //samplePlayers[0].playSample(0.8);

  //delay(2000);
  
  /*samplePlayers[0].playSample(0.8);
  
  samplePlayers[0].setFadeOut(fadeTime);
  
  delay(fadeTime + 1);

  samplePlayers[0].resetFadeObjects();
  samplePlayers[0].playSample(0.8);*/
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
