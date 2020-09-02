#include "Multiplexer.h"

const int Multiplexer::STABILISE_US = 50;

Multiplexer::Multiplexer(int pin, int numberOfChannels, Interface_Element** interfaceElements)
{
    m_pin = pin;
    m_numberOfChannels = numberOfChannels;
    m_channelNumber = 0;
    m_singleElement = interfaceElements[0];
    m_interfaceElements = interfaceElements;
}

void Multiplexer::setChannel(int channelNumber)
{
    if(this->isValidChannel(channelNumber))                                     // if the channel number is valid...
    {   
        m_channelNumber = channelNumber;                                        // ...update the member variable
        /*Serial.print("direction is... ");
        Serial.println(m_interfaceElements[m_channelNumber]->getDirection());*/
        pinMode(m_pin, m_interfaceElements[m_channelNumber]->getDirection());     // ...set the pinMode based on the interface element type
    }
}

bool Multiplexer::isValidChannel(int channelNumber)
{
    return channelNumber <= m_numberOfChannels;
} 

void Multiplexer::update()
{
    /*Serial.print("updating on channel...");
    Serial.println(m_channelNumber);*/
    m_interfaceElements[m_channelNumber]->update(m_pin);                        // ...update the interface element.
}