#ifndef MULTIPLEXER
#define MULTIPLEXER

#include <Arduino.h>
#include "Interface_Element.h"

class Multiplexer
{
    private:
        static const int STABILISE_US;
        int m_pin;
        int m_numberOfChannels;
        int m_channelNumber;
        elapsedMicros m_channelChangeUs;
        Interface_Element** m_interfaceElements;
        Interface_Element* m_singleElement;
    public:
        Multiplexer(int pin, int numberOfChannels, Interface_Element** interfaceElements);
        void setChannel(int channel);
        bool isValidChannel(int channel);
        void update();
};

#endif