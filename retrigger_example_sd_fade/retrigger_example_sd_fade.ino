#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=206.66665649414062,798.3333129882812
AudioEffectFade          fade2;          //xy=358.88887786865234,825.5555286407471
AudioEffectFade          fade1;          //xy=360.00000953674316,791.1110687255859
AudioOutputI2S           i2s1;           //xy=537.6666564941406,799.3333129882812
AudioConnection          patchCord1(playSdWav1, 0, fade1, 0);
AudioConnection          patchCord2(playSdWav1, 1, fade2, 0);
AudioConnection          patchCord3(fade2, 0, i2s1, 1);
AudioConnection          patchCord4(fade1, 0, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=197.66665649414062,906.3333129882812
// GUItool: end automatically generated code

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14
#define FADE_OUT_MS 5
#define FADE_IN_MS 1

String sine = String("sine_2.wav");

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
}

void loop() 
{ 
  playSdWav1.play(sine.c_str());
  
  delay(1000);
  
  //fade1.fadeOut(FADE_OUT_MS);
  //fade2.fadeOut(FADE_OUT_MS);
  
  //delay(FADE_OUT_MS + 1);

  playSdWav1.play(sine.c_str());

  //fade1.fadeIn(FADE_IN_MS);
  //fade2.fadeIn(FADE_IN_MS);
  
  //delay(FADE_IN_MS);
  delay(5000);
}
