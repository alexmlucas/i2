#ifndef LED_CONTROLLER
#define LED_CONTROLLER
#include <Arduino.h>
//#include "Led.h"
#include "Midi_Clock.h"

class Led_Controller
{
    private:
        const unsigned int FLASH_TIME_MS = 500;
        const unsigned int PULSE_LENGTH_MS = 50;
        int m_muxLatchPin = 19;
        int m_muxClockPin = 18;
        int m_muxDataPin = 21;
        int m_rhythm2LedPin = 37;
        int m_drumLedPins[4] = {30, 29, 2, 10};
        int m_rhythmLedCurrentStates[7] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW};        // perhaps better as a bool?
        int m_kitPattNumLedStates[4] = {LOW, LOW, LOW, LOW};
        bool m_drumLedPulseFlags[4] = {false, false, false, false};
        bool m_rhythmLedPulseFlags[7] = {false, false, false, false, false, false, false};
        bool m_undoLedPulseFlag = false;
        elapsedMillis m_undoLedPulseTimer;
        elapsedMillis m_drumLedPulseTimers[4] = {0, 0, 0, 0};
        elapsedMillis m_rhythmLedPulseTimers[7] = {0, 0, 0, 0, 0, 0, 0};
        elapsedMillis m_flashTimer = 0;
        bool m_kitPattLedFlashFlag = false;
        int m_kitPattLedState = true;
        int m_currentKitPatt;

        int m_kitMenuLedBit = 2;
        int m_pattMenuLedBit = 1;
        int m_kitPattNumLedBits[4] = {7, 6, 5, 4};
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

        int m_tempoMenuLedBit = 6;
        int m_volMenuLedBit = 5;
        int m_playLedBit = 4;
        int m_recordLedBit = 3;
        int m_undoLedBit = 0;
    
        //Led *m_kitPattMenuLeds[2];
        byte m_muxLedStates[3];
        bool m_playLedCurrentState;
        bool m_playStateActive;
    
        elapsedMillis m_dummyTimer;

        void writeMuxLeds();

    public:
        Led_Controller();
        void poll();
        void setTempo(int tempoBpm);
        void setKitPattMenuLeds(int state);
        void setKitPattNumLeds(int index);
        void setSpeedMenuLeds(int state);
        void setRhythmLed(int index, int state);
        void setTempoVolMenuLeds(int state);
        void setPlayLed(int state);
        void setRecordLed(int state);
        void pulseDrumLed(int ledNumber, int ledValue);
        void pulseRhythmLed(int index);
        void pulseUndoLed();
        void updatePulse();
        void setUndoLed(int state);
};

#endif
