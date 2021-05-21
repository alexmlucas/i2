#include "Constant_Parameters.h"
#include "Parameter_Manager.h"
#include "Led_Controller.h"
#include "Sample_Player.h"
#include "Transport.h"
#include "Midi_Clock.h"
#include "Sequencer.h"
#include "Rhythm_Generator.h"
#include "Input_Manager.h"
#include "Display_Controller.h"
#include "Output_Amplifier.h"
#include "Delay_Effect.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=571,215
AudioPlaySdWav           playSdWav2;     //xy=571,281
AudioPlaySdWav           playSdWav3;     //xy=573,348
AudioPlaySdWav           playSdWav7;     //xy=572,615
AudioPlaySdWav           playSdWav8;     //xy=572,681
AudioPlaySdWav           playSdWav6;     //xy=573,548
AudioPlaySdWav           playSdWav4;     //xy=574,415
AudioPlaySdWav           playSdWav5;     //xy=576,482
AudioEffectFade          fade1;          //xy=729,208
AudioEffectFade          fade2;          //xy=729,241
AudioEffectFade          fade3;          //xy=729,275
AudioEffectFade          fade4;          //xy=729,308
AudioEffectFade          fade5;          //xy=729,341
AudioEffectFade          fade6;          //xy=730,375
AudioEffectFade          fade7;          //xy=731,408
AudioEffectFade          fade8;          //xy=731,442
AudioEffectFade          fade9;          //xy=731,475
AudioEffectFade          fade10;         //xy=731,508
AudioEffectFade          fade11;         //xy=732,542
AudioEffectFade          fade16;         //xy=732,708
AudioEffectFade          fade12;         //xy=733,575
AudioEffectFade          fade13;         //xy=733,608
AudioEffectFade          fade14;         //xy=733,641
AudioEffectFade          fade15;         //xy=733,675
AudioMixer4              mixer1;         //xy=940,228
AudioMixer4              mixer3;         //xy=939,533
AudioMixer4              mixer2;         //xy=940,298
AudioMixer4              mixer4;         //xy=939,601
AudioMixer4              mixer5;         //xy=1073,247
AudioMixer4              mixer6;         //xy=1073,553
AudioMixer4              mixer7;         //xy=1108,379
AudioFilterStateVariable filter1;        //xy=1236,385
AudioEffectDelay         delay1;         //xy=1361,398
AudioAmplifier           amp1;           //xy=1361,480
AudioMixer4              mixer8;         //xy=1498,267
AudioMixer4              mixer9;         //xy=1497,572
AudioAmplifier           amp2;           //xy=1603,377
AudioAmplifier           amp3;           //xy=1603,435
AudioOutputI2S           i2s1;           //xy=1743,394
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
AudioConnection          patchCord47(mixer8, amp2);
AudioConnection          patchCord48(mixer9, amp3);
AudioConnection          patchCord49(amp2, 0, i2s1, 0);
AudioConnection          patchCord50(amp3, 0, i2s1, 1);
// GUItool: end automatically generated code




// Test Tone
/*AudioSynthWaveform    waveform1;
AudioOutputI2S        i2s1;
AudioConnection       patchCord1(waveform1, 0, i2s1, 0);
AudioConnection       patchCord2(waveform1, 0, i2s1, 1);*/

// SD card definitions
//#define SDCARD_CS_PIN    10
//#define SDCARD_MOSI_PIN  7
//#define SDCARD_SCK_PIN   14

Midi_Clock masterClock;
Midi_Clock rhythmClock;
Display_Controller displayController;
Led_Controller ledController;
Input_Manager inputManager;

Sample_Player samplePlayers[8] =        // index, track
{
  Sample_Player(&playSdWav1, 0, 0),
  Sample_Player(&playSdWav2, 0, 1),
  Sample_Player(&playSdWav3, 0, 2),
  Sample_Player(&playSdWav4, 0, 3),
  Sample_Player(&playSdWav5, 0, 4),
  Sample_Player(&playSdWav6, 0, 5),
  Sample_Player(&playSdWav7, 0, 6),
  Sample_Player(&playSdWav8, 0, 7)
};

Sequencer sequencer(&masterClock, samplePlayers);
Transport transport(&masterClock, &sequencer, &ledController);
Rhythm_Generator rhythmGenerator(&rhythmClock, &transport, samplePlayers);
Parameter_Manager parameterManager;
Output_Amplifier outputAmplifier(&amp2, &amp3);
Delay_Effect delayEffect(&delay1, &amp1, &mixer7, &mixer8, &mixer9, &filter1, &parameterManager);

void setup() 
{
  Serial.begin(31250);

  // ### setup sample players ###
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

  // ### setup object references ###
  inputManager.setClocks(&masterClock, &rhythmClock);
  inputManager.setDisplayController(&displayController);
  inputManager.setOutputAmplifier(&outputAmplifier);
  inputManager.setSequencer(&sequencer);
  inputManager.setSamplePlayers(samplePlayers);
  inputManager.setLedController(&ledController);
  inputManager.setRhythmGenerator(&rhythmGenerator);
  inputManager.setParameterManager(&parameterManager);
  inputManager.setTransport(&transport);
  rhythmGenerator.setLedController(&ledController);
  rhythmClock.setRunFlag(true);
  rhythmGenerator.setDisplayController(&displayController);
  
  // ### setup parameters ###
  // default values not loaded from Eeprom
  inputManager.setKitPatternMenuState(0);
  inputManager.setTempoVolMenuState(0);
  rhythmGenerator.setSpeed(1);

  // ### Drum Kit ###
  int recalledKitIndex = parameterManager.getKitIndex();    // get the saved value

  if(recalledKitIndex > 3)
  {
    recalledKitIndex = recalledKitIndex - 4;                // tweak the index to account for banking
  }
  
  for(int i = 0; i < 8; i++)                                // set all sample players
  {
    samplePlayers[i].setKit(recalledKitIndex);
  }

  inputManager.setKitIndex(recalledKitIndex);

  // ### Pattern ###
  int recalledPattIndex = parameterManager.getPatternIndex();
  sequencer.setPatternIndex(recalledPattIndex);
  inputManager.setPattIndex(recalledPattIndex);

  // ### Master Tempo/BPM ###
  int recalledBpm = parameterManager.getMasterTempo();
  masterClock.setBpm(recalledBpm);

  // ### Master Volume ###
  int recalledVolume = parameterManager.getMasterVolume();
  outputAmplifier.setLevel(recalledVolume);

  AudioMemory(100);
  
  // Test Tone
  /*waveform1.begin(WAVEFORM_SINE);
  waveform1.frequency(440);
  waveform1.amplitude(0.1);*/

  // setup the SD card
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  
  if (!(SD.begin(BUILTIN_SDCARD))) 
  {
    while (1) 
    {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  
  while (!Serial && millis() < 2500); // wait for serial monitor
}

void loop() 
{ 
  masterClock.poll();
  rhythmClock.poll();
  rhythmGenerator.poll();
  sequencer.poll(); 
  transport.poll();  
  inputManager.poll();
  displayController.poll();
  parameterManager.poll();
  ledController.poll();

  for(int i = 0; i < TRACK_AMOUNT; i++) 
  {
    samplePlayers[i].poll();
  }
}
