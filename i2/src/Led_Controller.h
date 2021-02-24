#ifndef LED_CONTROLLER
#define LED_CONTROLLER
#include <Arduino.h>
#include "Led.h"

class Led_Controller
{
    private:
        // slightly hacky implementation of constants
        int m_muxLatchPin = 19;
        int m_muxClockPin = 18;
        int m_muxDataPin = 21;
        int m_rhythm2LedPin = 37;

        int m_kitMenuLedBit = 2;
        int m_pattMenuLedBit = 1;
        int m_kitPattNum1LedBit = 7;
        int m_kitPattNum2LedBit = 6;
        int m_kitPattNum3LedBit = 5;
        int m_kitPattNum4LedBit = 4;

        int m_slowMenuLedBit = 2;
        int m_fastMenuLedBit = 1;
        int m_rhythm3Bit = 7;
        int m_rhythm4Bit = 6;
        int m_rhythm5Bit = 5;
        int m_rhythm6Bit = 4;
        int m_rhythm7Bit = 3;
        int m_rhythm8Bit = 0;
    
        Led *m_kitPattMenuLeds[2];
        byte m_muxLedStates[3];
        bool m_refreshMuxLeds;

        void writeMuxLeds();

    public:
        Led_Controller();
        void poll();
        void assignKitPattMenuLeds(Led *kitPattMenuLeds[2]);
        void setKitPattMenuLeds(int kitLedState, int pattLedState);
        void setKitPattNumLeds(int num1LedState, int num2LedState, int num3LedState, int num4LedState);
        void setSlowFastMenuLeds(int slowLedState, int fastLedState);
        void setRhythmNumLeds(int num2LedState, int num3LedState, int num4LedState, int num5LedState, int num6LedState, int num7LedState, int num8LedState);
        
        
};

#endif
