#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=219,110
AudioMixer4              mixer1;         //xy=415,124
AudioMixer4              mixer2;         //xy=416,211
AudioOutputI2S           i2s1;           //xy=569,131
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer2, 0);
AudioConnection          patchCord3(mixer1, 0, i2s1, 0);
AudioConnection          patchCord4(mixer2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=128,405
// GUItool: end automatically generated code
const int thresholdMin = 15;  // minimum reading, avoid "noise"
const int aftershockMillis = 60; // time of aftershocks & vibration

int state=0; // 0=idle, 1=looking for peak, 2=ignore aftershocks
int peak;    // remember the highest reading
elapsedMillis msec; // timer to end states 1 and 2

float sample_volume;
float volume_boost = 0.3;

void setup() {

  Serial.begin(9600);
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
  Serial.println("Piezo Peak Capture");
}

void loop() {
  int piezo = analogRead(A1);

  if (state == 0) {
    // IDLE state: if any reading is above a threshold, begin peak
    if (piezo > thresholdMin) {
      //Serial.println("begin state 1");
      state = 1;
      peak = piezo;
      msec = 0;
    }
  } else if (state == 1) {
    // Peak Tracking state: for 10 ms, capture largest reading
    if (piezo > peak) {
      peak = piezo;
    }
    if (msec >= 10) {
      Serial.print("peak = ");
      Serial.println(peak);
      //Serial.println("begin state 2");
      sample_volume = (peak * 0.0001);
      Serial.println(sample_volume);
      state = 2;
      msec = 0;
    }
  } else {
    // Ignore Aftershock state: wait for things to be quiet again
    if (piezo > thresholdMin) {
      msec = 0; // keep resetting timer if above threshold
    } else if (msec > 10) {
      //Serial.println("begin state 0");
      state = 0; // go back to idle after 30 ms below threshold
    }
  }

  if(state == 2){
    mixer1.gain(0, sample_volume);
    mixer2.gain(0, sample_volume);
    playSdWav1.play("kick_16.wav");
  }
  
}
