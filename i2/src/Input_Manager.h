#ifndef INPUT_MANAGER
#define INPUT_MANAGER
#include <Arduino.h>

class Input_Manager
{
    private:
        const unsigned int BUTTON_READ_INTERVAL = 10;
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

        elapsedMillis m_buttonReadTimer;
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