#ifndef INPUT_MANAGER
#define INPUT_MANAGER
#include <Arduino.h>

class Input_Manager
{
    private:
        const unsigned int MUX_READ_DELAY_US = 1;          // the delay between changing mux channel and reading it.
        const unsigned int DEBOUNCE_MS = 100;
        const int POT_NOISE_FILTER = 5;
        const int m_rhythmPotPin = A19;  
        const int m_muxAInPin = A13;
        int m_muxBInPin = A20;
        int m_muxCInPin = A17;
        int m_muxSelPin0 = 35;
        int m_muxSelPin1 = 34;
        int m_muxSelPin2 = 33;

        int m_muxAButtonStates[8];
        int m_muxBButtonStates[8];
        int m_muxCButtonStates[8];
        int m_echoPotLastValue;
        int m_rhythmPotLastValue;

        int m_muxAButtonEventTimes[8];
        int m_muxBButtonEventTimes[8];
        int m_muxCButtonEventTimes[8];

        elapsedMicros m_muxReadTimer;

        int m_muxReadIndex;
        bool m_readMuxChannel;
        bool m_changeMuxChannel;
        bool m_readMe;
        void setSensor(int index);

    public:
        Input_Manager();
        void poll();
        // void readMux1();
        void readMuxs();
        void readPiezos();
        void readDirectPot();
        
};

#endif