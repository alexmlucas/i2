#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// .wav file 
#include "AudioSampleSine.h"

// GUItool: begin automatically generated code
AudioPlayMemory          playMem1;       //xy=242.44445037841797,439.666690826416
AudioEffectEnvelope      envelope1;      //xy=388,440
AudioOutputI2S           i2s1; //xy=558.6667175292969,446
AudioConnection          patchCord1(playMem1, envelope1);
AudioConnection          patchCord2(envelope1, 0, i2s1, 0);
AudioConnection          patchCord3(envelope1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=239.22220611572266,539.222225189209
// GUItool: end automatically generated code


// SD card definitions
#define RELEASE_TIME_MS 5

void setup() 
{
  Serial.begin(31250);
  // setup the audio codec
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  envelope1.delay(0);
  envelope1.attack(0);
  envelope1.hold(0);
  envelope1.decay(0);
  envelope1.sustain(0.5);
  envelope1.release(RELEASE_TIME_MS);
}

void loop() 
{ 
  envelope1.noteOn();
  playMem1.play(AudioSampleSine);
  
  delay(500);
  envelope1.noteOff();
  delay(RELEASE_TIME_MS + 1);
}
