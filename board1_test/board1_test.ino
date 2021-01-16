// PWM_0 = 16
// PWM_1 = 20
// PWM_2 = 29
// PWM_3 = 30

#include "Piezo_Trigger.h"
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpackWire2.h"

#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>

AudioSynthWaveform    waveform1;
AudioOutputI2S        i2s1;
AudioConnection       patchCord1(waveform1, 0, i2s1, 0);
AudioConnection       patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000  sgtl5000_1;

int led0Pin = 10;
int led1Pin = 2;
int led2Pin = 29;
int led3Pin = 30;

Piezo_Trigger drumPads[4] = {A2, A1, A0, A3};
double drumPadReadings[4] = {0, 0, 0, 0};

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

/*int pwm0Pin = 16;
int pwm1Pin = 15;
int pwm2Pin = 14;
int pwm3Pin = 17;*/


int potPin = A19;  
int muxAInPin = A13;
int muxBInPin = A20;
int muxCInPin = A17;
int muxSelPin0 = 35;
int muxSelPin1 = 34;
int muxSelPin2 = 33;
int ledIndex = 0;
int soloLedPin = 37;

int lastPotValue = 0;

//Pin connected to ST_CP of 74HC595
int latchPin = 19;
//Pin connected to SH_CP of 74HC595
int clockPin = 18;
////Pin connected to DS of 74HC595
int dataPin = 21;

int ledToLight[] = {1, 2, 4, 8, 16, 32, 64, 128};

elapsedMillis ledTimer;
elapsedMillis pwmTimer;

void setup() 
{
  AudioMemory(10);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.3);
  waveform1.begin(WAVEFORM_SINE);
  delay(1000);

  waveform1.frequency(440);
  waveform1.amplitude(0.1);

  alpha4.begin(0x70);  // pass in the address

  alpha4.writeDigitRaw(3, 0x0);
  alpha4.writeDigitRaw(0, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(0, 0x0);
  alpha4.writeDigitRaw(1, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(1, 0x0);
  alpha4.writeDigitRaw(2, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(2, 0x0);
  alpha4.writeDigitRaw(3, 0xFFFF);
  alpha4.writeDisplay();
  //delay(200);
  
  //alpha4.clear();
  //alpha4.writeDisplay();
  
  pinMode(led0Pin, OUTPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(potPin, INPUT);
  pinMode(muxAInPin, INPUT);
  pinMode(muxBInPin, INPUT);
  pinMode(muxCInPin, INPUT);
  pinMode(muxSelPin0, OUTPUT);
  pinMode(muxSelPin1, OUTPUT);
  pinMode(muxSelPin2, OUTPUT);
  pinMode(soloLedPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  analogWrite(led0Pin, 255);
  analogWrite(led1Pin, 255);
  analogWrite(led2Pin, 255);
  analogWrite(led3Pin, 255);
  
}

void loop() {
  

  for(int i = 0; i < 4; i++)
  {
    drumPadReadings[i] = drumPads[i].checkActivity();                   // ### Read the Drum Pads ###

    if(drumPadReadings[i] > 0)                                          // if a trigger has been detected...
    {
      //drumPadReadings[i] = map(drumPadReadings[i], 0, 1023, 1, 10);     // ...scale reading to appropriate range for logarithmic curve
     //drumPadReadings[i] = log(drumPadReadings[i]);                     // ...apply logarithmic curve.

      Serial.print("drum ");
      Serial.print(i);
      Serial.print(" = ");
      Serial.println(drumPadReadings[i]);
      //drumPadLeds[i].pulse();
    }
  }
  
  int currentPotValue = analogRead(potPin);

  if(currentPotValue != lastPotValue)
  {
    lastPotValue = currentPotValue;
  }

  /*Serial.print("Pot = ");
  Serial.print(currentPotValue);
  Serial.print(" ");*/
   

  if(ledTimer > 500)
  {
    if (ledIndex == 8)
    {
      ledIndex = 0;
      digitalWrite(soloLedPin, HIGH);           // abitrary lighting of the solo LED.
    } else
    {
      digitalWrite(soloLedPin, LOW);
    }
    
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, ledToLight[ledIndex]);  

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    ledIndex++;
    ledTimer = 0;
  }

  /// show all 8 sensor readings
  for (int i = 0; i < 8; i++)
  {
    setSensor(i);
    //Serial.print(i);
    //Serial.print("A");
    //Serial.print(" = ");
    
    if(digitalRead(muxAInPin))
    {
      //Serial.print("#");
    } else
    {
      //Serial.print(" ");
    }
    //Serial.print(" ");

    //Serial.print(i);
    //Serial.print("B");
    //Serial.print(" = ");

    if(i == 4)
    {
      //Serial.print(analogRead(muxBInPin));
    } else 
    {
      if(digitalRead(muxBInPin))
      {
        //Serial.print("#");
      } else
      {
        //Serial.print(" ");
      }
    }
    //Serial.print(" ");

    //Serial.print(i);
    //Serial.print("C");
    //Serial.print(" = ");

    if(digitalRead(muxCInPin))
    {
      //Serial.print("#");
    } else
    {
      //Serial.print(" ");
    }
    //Serial.print(" ");
    
    //delay(10);

    if(i == 7)
    {
      //Serial.println();
    }
  }
}


 
void setSensor(int index)
{
  int b0 = bitRead(index, 0);
  int b1 = bitRead(index, 1);
  int b2 = bitRead(index, 2);

  digitalWrite(muxSelPin0, b0);
  digitalWrite(muxSelPin1, b1);
  digitalWrite(muxSelPin2, b2);  
} 
