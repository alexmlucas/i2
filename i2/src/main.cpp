// TNT: 
// ...test mux 0 and drum pad LEDs with hardware.
// ...implement flashing for play led.

#include "Constant_Parameters.h"
#include "Piezo_Trigger.h"
#include "Led_Controller.h"
#include "Led.h"
#include "Sample_Player.h"
#include "Transport.h"
#include "Midi_Clock.h"
#include "Sequencer.h"
#include "Rhythm_Generator.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
/*AudioPlaySdWav           playSdWav1;     //xy=69,182.00006103515625
AudioPlaySdWav           playSdWav2;     //xy=69,248.00006103515625
AudioPlaySdWav           playSdWav3;     //xy=71,315.00006103515625
AudioPlaySdWav           playSdWav7;     //xy=70,582.0000610351562
AudioPlaySdWav           playSdWav8;     //xy=70,648.0000610351562
AudioPlaySdWav           playSdWav6;     //xy=71,515.0000610351562
AudioPlaySdWav           playSdWav4;     //xy=72,382.00006103515625
AudioPlaySdWav           playSdWav5;     //xy=74,449.00006103515625
AudioEffectFade          fade1;          //xy=227,175.00006103515625
AudioEffectFade          fade2;          //xy=227,208.00006103515625
AudioEffectFade          fade3;          //xy=227,242.00006103515625
AudioEffectFade          fade4;          //xy=227,275.00006103515625
AudioEffectFade          fade5;          //xy=227,308.00006103515625
AudioEffectFade          fade6;          //xy=228,342.00006103515625
AudioEffectFade          fade7;          //xy=229,375.00006103515625
AudioEffectFade          fade8;          //xy=229,409.00006103515625
AudioEffectFade          fade9;          //xy=229,442.00006103515625
AudioEffectFade          fade10;         //xy=229,475.00006103515625
AudioEffectFade          fade11;         //xy=230,509.00006103515625
AudioEffectFade          fade16;         //xy=230,675.0000610351562
AudioEffectFade          fade12;         //xy=231,542.0000610351562
AudioEffectFade          fade13;         //xy=231,575.0000610351562
AudioEffectFade          fade14;         //xy=231,608.0000610351562
AudioEffectFade          fade15;         //xy=231,642.0000610351562
AudioMixer4              mixer1;         //xy=438,195.00006103515625
AudioMixer4              mixer3;         //xy=437,500.00006103515625
AudioMixer4              mixer2;         //xy=438,265.00006103515625
AudioMixer4              mixer4;         //xy=437,568.0000610351562
AudioMixer4              mixer5;         //xy=571,214.00006103515625
AudioMixer4              mixer6;         //xy=571,520.0000610351562
AudioMixer4              mixer7;         //xy=606,346
AudioFilterStateVariable filter1;        //xy=734,352
AudioEffectDelay         delay1;         //xy=859,365
AudioAmplifier           amp1;           //xy=859,447
AudioMixer4              mixer8;         //xy=996,234
AudioMixer4              mixer9;         //xy=995,539
AudioOutputI2S           i2s1;           //xy=1135,356.00006103515625
AudioConnection          patchCord1(playSdWav1, 0, fade1, 0);
AudioConnection          patchCord2(playSdWav1, 1, fade2, 0);
AudioConnection          patchCord3(playSdWav2, 0, fade3, 0);
AudioConnection          patchCord4(playSdWav2, 1, fade4, 0);
AudioConnection          patchCord5(playSdWav3, 0, fade5, 0);
AudioConnection          patchCord6(playSdWav3, 1, fade6, 0);
AudioConnection          patchCord7(playSdWav7, 0, fade13, 0);
AudioConnection          patchCord8(playSdWav7, 1, fade14, 0);
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
AudioConnection          patchCord28(fade16, 0, mixer4, 3);
AudioConnection          patchCord29(fade12, 0, mixer4, 1);
AudioConnection          patchCord30(fade13, 0, mixer2, 2);
AudioConnection          patchCord31(fade14, 0, mixer4, 2);
AudioConnection          patchCord32(fade15, 0, mixer2, 3);
AudioConnection          patchCord33(mixer1, 0, mixer5, 0);
AudioConnection          patchCord34(mixer3, 0, mixer6, 0);
AudioConnection          patchCord35(mixer2, 0, mixer5, 1);
AudioConnection          patchCord36(mixer4, 0, mixer6, 1);
AudioConnection          patchCord37(mixer5, 0, mixer7, 0);
AudioConnection          patchCord38(mixer5, 0, mixer8, 0);
AudioConnection          patchCord39(mixer6, 0, mixer7, 1);
AudioConnection          patchCord40(mixer6, 0, mixer9, 0);
AudioConnection          patchCord41(mixer7, 0, filter1, 0);
AudioConnection          patchCord42(filter1, 2, delay1, 0);
AudioConnection          patchCord43(delay1, 0, amp1, 0);
AudioConnection          patchCord44(delay1, 0, mixer8, 1);
AudioConnection          patchCord45(delay1, 0, mixer9, 1);
AudioConnection          patchCord46(amp1, 0, mixer7, 2);
AudioConnection          patchCord47(mixer8, 0, i2s1, 0);
AudioConnection          patchCord48(mixer9, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1290,4462
// GUItool: end automatically generated code

// SD card definitions
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

Midi_Clock masterClock(DEFAULT_BPM);
Midi_Clock rhythmClock(DEFAULT_BPM);
Sample_Player samplePlayers[4] = {(&playSdWav1), (&playSdWav2), (&playSdWav3), (&playSdWav4)};
Sequencer sequencer(&masterClock, samplePlayers);
Transport transport(&masterClock, &sequencer);
Rhythm_Generator rhythmGenerator(&rhythmClock, &transport, samplePlayers);

bool drumEventFlag = false;

Led drumPadLeds[2] = {0, 1};
Piezo_Trigger drumPads[2] = {A2, A3};
double drumPadReadings[2] = {0, 0};*/

// mux 0 LEDs
Led undo(0, 0);
Led record(0, 3);
Led play(0, 4);
Led volume(0, 5);
Led tempo(0, 6);

// mux 1 LEDs

Led kit(1, 2);
Led pattern(1, 1);
Led kitPattern1(1, 7);
Led kitPattern2(1, 6);
Led kitPattern3(1, 5);
Led kitPattern4(1, 4);

// mux 2 LEDs
Led slow(2, 2);
Led fast(2, 1);
Led rhythm3(2, 7);
Led rhythm4(2, 6);
Led rhythm5(2, 5);
Led rhythm6(2, 4);
Led rhythm7(2, 3);
Led rhythm8(2, 0);

// directly wired LED
Led rhythm(37);

Led *kitPatternMenuLeds[] = {&kit, &pattern};

Led_Controller ledController;

int latchPin = 19;
int clockPin = 18;
int dataPin = 21;
int ledIndex = 0;
int ledToLight[] = {1, 2, 4, 8, 16, 32, 64, 128};
elapsedMillis ledTimer;

void setup() 
{
  Serial.begin(31250);

  // setup the audio codec
  /*AudioMemory(8);
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
  samplePlayers[0].setSampleName(String("kit_1/0.wav"));
  samplePlayers[1].setSampleName(String("kit_1/1.wav"));
  samplePlayers[2].setSampleName(String("kit_1/2.wav"));
  samplePlayers[3].setSampleName(String("kit_1/3.wav"));

  samplePlayers[0].assignFadeObjects(&fade1, &fade2);
  samplePlayers[1].assignFadeObjects(&fade3, &fade4);
  samplePlayers[2].assignFadeObjects(&fade5, &fade6);
  samplePlayers[3].assignFadeObjects(&fade7, &fade8);

  samplePlayers[0].assignMixerObjects(&mixer1, &mixer3, 0, 0);
  samplePlayers[1].assignMixerObjects(&mixer1, &mixer3, 1, 1);
  samplePlayers[2].assignMixerObjects(&mixer1, &mixer3, 2, 2);
  samplePlayers[3].assignMixerObjects(&mixer1, &mixer3, 3, 3);
  */

  while (!Serial && millis() < 2500);                                   // wait for serial monitor

  delay(2000);                                                          // an extra delay for good measure.
}

void loop() 
{ 
  delay(10);

  if(ledTimer > 500)
  {  
    ledController.setKitPattMenuLeds(1, 0);
    ledController.setKitPattNumLeds(0, 0, 0, 1);

    ledController.setSlowFastMenuLeds(1, 0);
    ledController.setRhythmNumLeds(0, 0, 0, 1, 0, 1, 0);
    

    ledTimer = 0;
  }
  




  
  /*for(int i = 0; i < 2; i++)
  {
    drumPadReadings[i] = drumPads[i].checkActivity();                   // ### Read the Drum Pads ###

    if(drumPadReadings[i] > 0)                                          // if a trigger has been detected...
    {
      drumPadReadings[i] = map(drumPadReadings[i], 0, 1023, 1, 10);     // ...scale reading to appropriate range for logarithmic curve
      drumPadReadings[i] = log(drumPadReadings[i]);                     // ...apply logarithmic curve.

      Serial.println(drumPadReadings[i]);
      rhythmGenerator.triggerRhythm(i, drumPadReadings[i]);             // ...trigger the rhythm.
      drumPadLeds[i].pulse();                                           // ...set the LED to pulse. 
    }
  }

  transport.poll();                                                     // poll the transport. manages the master clock and sequencer. 

  sequencer.poll();                                                     // ask the sequencer to check if it needs to do anything.

  rhythmGenerator.poll();

  masterClock.poll();                                                   // poll the master clock.

  rhythmClock.poll();

  for(int i = 0; i < TRACK_AMOUNT - 1; i++)                             // poll all samples. polling takes care of fades.
  {
    samplePlayers[i].poll();
  }

  for(int i = 0; i < 2; i++)                                            // refresh drum leds
  {
    drumPadLeds[i].refresh();
  }*/




}
