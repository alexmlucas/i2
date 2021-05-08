#ifndef LED_CONTROLLER
#define LED_CONTROLLER
#include <Arduino.h>
#include "Led.h"
#include "Midi_Clock.h"


class Led_Controller
{
    private:
        int m_muxLatchPin = 19;
        int m_muxClockPin = 18;
        int m_muxDataPin = 21;
        int m_rhythm2LedPin = 37;
        int m_pulseLengthMs = 50;
        int m_drumLedPins[4] = {30, 29, 2, 10};
        bool m_drumLedPulseFlags[4] = {false, false, false, false};
        elapsedMillis m_drumLedPulseTimers[4] = {false, false, false, false};
        int m_rhythmLedCurrentStates[7] = {0, 0, 0, 0, 0, 0, 0};
        bool m_rhythmLedPulseFlags[7] = {false, false, false, false, false, false, false};
        elapsedMillis m_rhythmLedPulseTimers[7] = {false, false, false, false, false, false, false};

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

        int m_tempoMenuLedBit = 6;
        int m_volMenuLedBit = 5;
        int m_playLedBit = 4;
        int m_recordLedBit = 3;
        int m_undoLedBit = 0;
    
        Led *m_kitPattMenuLeds[2];
        byte m_muxLedStates[3];
        bool m_playLedCurrentState;
        bool m_playStateActive;
        
        Midi_Clock* m_masterClock; 

        void writeMuxLeds();

    public:
        Led_Controller(Midi_Clock* masterClock);
        void poll();
        void setTempo(int tempoBpm);
        void assignKitPattMenuLeds(Led *kitPattMenuLeds[2]);
        void setKitPattMenuLeds(int kitLedState, int pattLedState);
        void setKitPattNumLeds(int num1LedState, int num2LedState, int num3LedState, int num4LedState);
        void setSpeedMenuLeds(int state);
        void setRhythmLed(int index, int state);
        void setTempoVolMenuLeds(int tempoLedState, int volLedState);
        void setTransportLeds(int playLedState, int recordLedState, int undoLedState);
        void pulseDrumLed(int ledNumber, int ledValue);
        void pulseRhythmLed(int index);
        void updatePulse();
};

#endif
