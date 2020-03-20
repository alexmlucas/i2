#include "Sequence.h"
#include "Simple_Button.h"
#include "Led.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav8;     //xy=389,517
AudioPlaySdWav           playSdWav5;     //xy=390,397
AudioPlaySdWav           playSdWav6;     //xy=390,438
AudioPlaySdWav           playSdWav7;     //xy=390,478
AudioPlaySdWav           playSdWav1;     //xy=391,231
AudioPlaySdWav           playSdWav2;     //xy=391,272
AudioPlaySdWav           playSdWav3;     //xy=391,314
AudioPlaySdWav           playSdWav4;     //xy=391,355
AudioMixer4              mixer1;         //xy=789,248
AudioMixer4              mixer2;         //xy=789,316
AudioMixer4              mixer3;         //xy=789,384
AudioMixer4              mixer4;         //xy=789,452
AudioMixer4              mixer5;         //xy=953,245
AudioMixer4              mixer6;         //xy=955,382
AudioOutputI2S           i2s1;           //xy=1125,252
AudioConnection          patchCord1(playSdWav8, 0, mixer2, 3);
AudioConnection          patchCord2(playSdWav8, 1, mixer4, 3);
AudioConnection          patchCord3(playSdWav5, 0, mixer2, 0);
AudioConnection          patchCord4(playSdWav5, 1, mixer4, 0);
AudioConnection          patchCord5(playSdWav6, 0, mixer2, 1);
AudioConnection          patchCord6(playSdWav6, 1, mixer4, 1);
AudioConnection          patchCord7(playSdWav7, 0, mixer2, 2);
AudioConnection          patchCord8(playSdWav7, 1, mixer4, 2);
AudioConnection          patchCord9(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord10(playSdWav1, 1, mixer3, 0);
AudioConnection          patchCord11(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord12(playSdWav2, 1, mixer3, 1);
AudioConnection          patchCord13(playSdWav3, 0, mixer1, 2);
AudioConnection          patchCord14(playSdWav3, 1, mixer3, 2);
AudioConnection          patchCord15(playSdWav4, 0, mixer1, 3);
AudioConnection          patchCord16(playSdWav4, 1, mixer3, 3);
AudioConnection          patchCord17(mixer1, 0, mixer5, 0);
AudioConnection          patchCord18(mixer2, 0, mixer5, 1);
AudioConnection          patchCord19(mixer3, 0, mixer6, 0);
AudioConnection          patchCord20(mixer4, 0, mixer6, 1);
AudioConnection          patchCord21(mixer5, 0, i2s1, 0);
AudioConnection          patchCord22(mixer6, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=384,634
// GUItool: end automatically generated code

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

String hiHat = String("hat_16.wav");
String snare = String("snare_16.wav");
String kick = String("kick_16.wav");

unsigned long currentMicros;
unsigned long previousMicros = 0;
const unsigned long MICROSECONDS_IN_MINUTE = 60000000;
const float MULTIPLIER_32ND = 0.125;
int crotchetInterval;
int bpm = 120; // Seems more like 119.
int play_flag = true;
int midiTickInterval;

Sample sample0(&playSdWav1);
Sample sample1(&playSdWav2);
Sample sample2(&playSdWav3);
Sample sample3(&playSdWav4); 
Sample sample4(&playSdWav5);
Sample sample5(&playSdWav6);
Sample sample6(&playSdWav7);
Sample sample7(&playSdWav8);

Track trackContainer[8];
Track *p_trackContainer[] = {&trackContainer[0], &trackContainer[1], &trackContainer[2], &trackContainer[3], &trackContainer[4], &trackContainer[5], &trackContainer[6], &trackContainer[7]};

Sequence sequence(p_trackContainer);

// create a structure that holds a pointer to a sample and a velocity value to use as a trigger event.
struct _trigger {
   Sample *sample;
   byte velocity;
};

// create a structure for a single step that holds eight triggers (8 note polyphony)
struct _step {
  _trigger triggers[8]; 
};

// create a 32 step sequence.
struct _sequence {
  _step steps[32];
} mySequence;

// create switch triggers
Simple_Button switch_trigger_0(A6, 10);
Simple_Button switch_trigger_1(A7, 10);

// variables for tracking button state.
bool switch_0_last_state = false;
bool switch_0_current_state = false;
bool switch_1_last_state = false;
bool switch_1_current_state = false;

// LEDs
Led drum_led_0(0);
Led drum_led_1(1);

void setup() {
  Serial.begin(31250);
  
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  while (!Serial && millis() < 2500) /* wait for serial monitor */ ;
  
  midiTickInterval = calculateMidiTickInterval(bpm);
  
  mixer1.gain(0, 0.5);
  mixer3.gain(0, 0.5);

  sample0.setMixersAndChannels(&mixer1, &mixer3, 0, 0);
  sample0.setVolume(0.5);
  sample0.setSampleName(hiHat);

  sample1.setMixersAndChannels(&mixer1, &mixer3, 1, 1);
  sample1.setVolume(0.9);
  sample1.setSampleName(snare);

  sample2.setMixersAndChannels(&mixer1, &mixer3, 2, 2);
  sample2.setVolume(0.8);
  sample2.setSampleName(kick);

  trackContainer[0].setSample(&sample0);
  // set the trigger interval.
  trackContainer[0].setStepFrequency(3);
  trackContainer[0].setActive(false);

  trackContainer[1].setSample(&sample1);
  // set the trigger interval.
  trackContainer[1].setStepFrequency(18);
  trackContainer[1].setActive(false);

  trackContainer[2].setSample(&sample2);
  // set the trigger interval.
  trackContainer[2].setStepFrequency(9);
  trackContainer[2].setActive(false);

  // test setting a value in the sequence struct.

  mySequence.steps[0].triggers[0].sample = &sample0;
  mySequence.steps[0].triggers[0].velocity = 31;

  Serial.print("Velocity value = ");
  Serial.println(mySequence.steps[0].triggers[0].velocity);

  mySequence.steps[0].triggers[0].sample->playSample();

}

void loop() {

  // read switch 0
  int switch_0_current_state = switch_trigger_0.check_pressed();
  // has the switch state changed?...
  if(switch_0_current_state != switch_0_last_state){
    
    if(switch_0_current_state){ // if switch is pressed...
      // ...play the sample.
      sample2.playSample();
      // ...pulse the LED
      drum_led_0.pulse();
    }

    // update the last state.
    switch_0_last_state = switch_0_current_state;
    
  }

  

  int switch_1 = switch_trigger_1.check_pressed();
  if(switch_trigger_1.check_pressed()){
    drum_led_1.pulse();
  }

  // LED refresh
  drum_led_0.refresh();
  drum_led_1.refresh();

  //Serial.println(AudioMemoryUsage());

  // This is the clock... (currently)
  if(play_flag == true){
    currentMicros = micros();

    if(currentMicros - previousMicros > midiTickInterval){
      sequence.updateMidiTickCounter();
      previousMicros = currentMicros;
    }
  }
}

int calculateMidiTickInterval(int incomingBpm){
  int crotchetInterval = MICROSECONDS_IN_MINUTE / incomingBpm;
  int midiTickInterval = round(crotchetInterval / 24);
  return midiTickInterval;
}
