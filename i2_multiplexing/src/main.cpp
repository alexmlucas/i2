#include <Arduino.h>
#include "Multiplexer_Controller.h"
#include "Multiplexer.h"
#include "Interface_Element.h"
#include "Simple_Button.h"
#include "Single_Led.h"

const int BUTTON_DEBOUNCE_MS = 50;

Simple_Button volumeButton(BUTTON_DEBOUNCE_MS);
Simple_Button tempoButton(BUTTON_DEBOUNCE_MS);
Simple_Button upButton(BUTTON_DEBOUNCE_MS);
Simple_Button downButton(BUTTON_DEBOUNCE_MS);
Simple_Button patternKitButton1(BUTTON_DEBOUNCE_MS);

Single_Led volumeLed;
Single_Led tempoLed;
Single_Led patternKitLed1;

Interface_Element* interfaceElementsMux1[] = {&volumeButton, &tempoButton, &upButton, &downButton, &patternKitButton1, &volumeLed, &tempoLed, &patternKitLed1};

int multiplexPins[] = {0, 1, 2, 3};
Multiplexer mux1(4, 7, interfaceElementsMux1);
Multiplexer* multiplexers[] = {&mux1};

Multiplexer_Controller multiplexController(multiplexPins, multiplexers, 1);

int currentChannel;

// channel 0 = volume button
// channel 1 = tempo button
// channel 2 = up button
// channel 3 = down button
// channel 4 = pattern/kit 1 button
// channel 5 = volume LED
// channel 6 = tempo LED
// channel 7 = pattern/kit 1 LED.

void setup() 
{
  Serial.begin(31250);
  //volumeLed.set_on(true);
}

void loop() 
{
  multiplexController.update();
  //delay(250);
}