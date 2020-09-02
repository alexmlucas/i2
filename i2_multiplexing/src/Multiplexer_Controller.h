#ifndef MULTIPLEXER_CONTROLLER
#define MULTIPLEXER_CONTROLLER
#include <Arduino.h>
#include "Multiplexer.h"

class Multiplexer_Controller
{
    private:
        const int M_MAX_CHANNELS;
        const int M_STABILISE_US;
        const int M_UPDATE_RATE_US;
        Multiplexer** m_multiplexers;
        int* m_pins;
        int m_numberOfMultiplexers;
        int m_currentChannel;
        elapsedMicros lastChannelWriteUs;

    public:
        Multiplexer_Controller(int* pins, Multiplexer** multiplexers, int numberOfMultiplexers);
        void incrementChannel();
        void setChannel(int channel);
        void update();
        int getNumberOfMultiplexers();
};

#endif