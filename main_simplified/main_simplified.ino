#include "Sequence.h"
#include "Simple_Button.h"
//#include "Led.h"
#include "Ultrasonic_Trigger.h"

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

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// Use these with the ultrasonic trigger
#define TRIGGER_PIN  3
#define ECHO_PIN     2
#define MAX_DISTANCE 60
#define DEBOUNCE 20

String hiHat = String("hat_16.wav");
String snare = String("snare_16.wav");
String kick = String("kick_16.wav");

unsigned long currentMicros;
unsigned long previousMicros = 0;
const unsigned long MICROSECONDS_IN_MINUTE = 60000000;
const float MULTIPLIER_32ND = 0.125;
int crotchetInterval;
int bpm = 120;
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

// Ultrasonic trigger
Ultrasonic_Trigger sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE, DEBOUNCE);

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
  trackContainer[0].setStepFrequency(8);
  trackContainer[0].setActive(true);

  trackContainer[1].setSample(&sample1);
  // set the trigger interval.
  trackContainer[1].setStepFrequency(18);
  trackContainer[1].setActive(false);

  trackContainer[2].setSample(&sample2);
  // set the trigger interval.
  trackContainer[2].setStepFrequency(9);
  trackContainer[2].setActive(false);

  //sonar.set_track(&trackContainer[0]);
  //sonar.set_led(&beam_led);

  //beam_led.set_on(true);

}

void loop() {
  //delay(10);
  // check for activity from the ultrasonic trigger.
  //Serial.println(sonar.check_and_return());

  /*AudioNoInterrupts();
  sonar.check_activity();
  AudioInterrupts();*/

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
