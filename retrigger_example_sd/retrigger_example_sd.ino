#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=490.5714416503906,660.857177734375
AudioEffectEnvelope      envelope1;      //xy=662.857063293457,654.2856769561768
AudioEffectEnvelope      envelope2;      //xy=662.8571128845215,690.0000228881836
AudioOutputI2S           i2s1;           //xy=821.5714302062988,661.6428937911987
AudioConnection          patchCord1(playSdWav1, 0, envelope1, 0);
AudioConnection          patchCord2(playSdWav1, 1, envelope2, 0);
AudioConnection          patchCord3(envelope1, 0, i2s1, 0);
AudioConnection          patchCord4(envelope2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=481.78577423095703,768.8573217391968
// GUItool: end automatically generated code

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14
#define RELEASE_TIME_MS 10

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

  envelope1.delay(0);
  envelope1.attack(40);
  envelope1.hold(0);
  envelope1.decay(0);
  envelope1.sustain(0.5);
  envelope1.release(RELEASE_TIME_MS);

  envelope2.delay(0);
  envelope2.attack(40);
  envelope2.hold(0);
  envelope2.decay(0);
  envelope2.sustain(0.5);
  envelope2.release(RELEASE_TIME_MS);
}

void loop() 
{ 
  envelope1.noteOn();
  envelope2.noteOn();
  
  playSdWav1.play(sine.c_str());
  
  delay(500);
  
  envelope1.noteOff();
  envelope2.noteOff();
  
  delay(RELEASE_TIME_MS + 2);
  delay(500);
}
