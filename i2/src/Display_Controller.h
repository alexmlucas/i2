#ifndef DISPLAY_CONTROLLER
#define DISPLAY_CONTROLLER
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpackWire2.h>
#include "Midi_Clock.h"

class Display_Controller
{
    private:
        const int ADDRESS = 0x70;
        const unsigned int DIGIT_CLEAR_TIMER = 2000;
        elapsedMillis m_timeSinceDigitEvent = 0;
        bool m_digitClearFlag = false;
        Adafruit_AlphaNum4 display = Adafruit_AlphaNum4();
        int m_lastMidiTick = -1;
        int m_beatIndex = 0;
        Midi_Clock *m_masterClock;
        bool m_segmentDotStates[4] = {true, false, false, false};
        int m_currentDigits[4] = {-1, -1, -1, -1};
        const uint16_t m_numbertable[10] = {
            0xC3F,  // 0
            0x6,    // 1
            0xDB,   // 2
            0x8F,   // 3
            0xE6,   // 4
            0x2069, // 5
            0xFD,   // 6
            0x7,    // 7
            0xFF,   // 8
            0xEF,   // 9
        };

    public:
        Display_Controller(Midi_Clock *masterClock);
        void displayNumber(int number);
        void poll();
        void incrementBeatIndex();
        void setSegmentDotStates(int dotOnIndex);
        void refresh();
        void resetBeatIndex();
        void clearDigitData();
};

#endif
