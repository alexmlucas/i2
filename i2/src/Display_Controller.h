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
        elapsedMillis m_timeSinceDigitWrite = 0;
        bool m_digitClearFlag = false;
        Adafruit_AlphaNum4 display = Adafruit_AlphaNum4();
        int m_lastMidiTick = -1;
        int m_beatIndex = 0;
        Midi_Clock *m_masterClock;
        bool m_segmentDotStates[4] = {true, false, false, false};
        char m_currentDigits[4] = {0, 0, 0, 0};

    public:
        Display_Controller(Midi_Clock *masterClock);
        void displayNumber(int number);
        void poll();
        void clearDigits();
        void clearDots();
        void incrementBeatIndex();
        void setSegmentDotStates(int dotOnIndex);
        void writeDigit(int onesDigit);
        void writeDigit(int tensDigit, int onesDigit);
        void writeDigit(int hundredsDigit, int tensDigit, int onesDigit);
        void writeDots(int dotOnIndex);
        void resetBeatIndex();
};

#endif
