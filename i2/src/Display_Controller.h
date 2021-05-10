#ifndef DISPLAY_CONTROLLER
#define DISPLAY_CONTROLLER
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpackWire2.h>

class Display_Controller
{
    private:
        const int ADDRESS = 0x70;
        const int CLEAR_TIMER = 2000;
        elapsedMillis m_timeSinceWrite = 0;
        bool m_clearFlag = false;
        Adafruit_7segment display = Adafruit_7segment();

    public:
        Display_Controller();
        void displayNumber(int number);
        void poll();   
};

#endif
