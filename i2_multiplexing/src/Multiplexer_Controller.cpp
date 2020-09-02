#include "Multiplexer_Controller.h"

//const int Multiplexer_Controller::UPDATE_RATE_US = 100;

Multiplexer_Controller::Multiplexer_Controller(int* pins, Multiplexer** multiplexers, int numberOfMultiplexers) : M_MAX_CHANNELS(8), M_STABILISE_US(10), M_UPDATE_RATE_US(100)
{
    m_pins = pins;

    pinMode(m_pins[0], OUTPUT);                               // set pinMode of multiplex pins to output.
    pinMode(m_pins[1], OUTPUT);
    pinMode(m_pins[2], OUTPUT);
    pinMode(m_pins[3], OUTPUT);
    
    m_multiplexers = multiplexers;
    m_numberOfMultiplexers = numberOfMultiplexers;

    m_currentChannel = 5;
    this->setChannel(m_currentChannel);                       // write the channel on initialisation.
}

void Multiplexer_Controller::incrementChannel()
{
    if(m_currentChannel < (M_MAX_CHANNELS - 1))
    {
        m_currentChannel++;
    } else
    {
        m_currentChannel = 0;
    }

    /*Serial.print("channel number =... ");
    Serial.println(m_currentChannel);*/

    this->setChannel(m_currentChannel);
}

void Multiplexer_Controller::setChannel(int channel)
{
    int bit0 = bitRead(channel, 0);
    int bit1 = bitRead(channel, 1);
    int bit2 = bitRead(channel, 2);
    int bit3 = bitRead(channel, 3);

    /*Serial.print("bits are...");
    Serial.print(bit3);
    Serial.print(bit2);
    Serial.print(bit1);
    Serial.println(bit0);*/

    /*Serial.print("pins are...");
    Serial.print(m_pins[0]);
    Serial.print(" ");
    Serial.print(m_pins[1]);
    Serial.print(" ");
    Serial.print(m_pins[2]);
    Serial.print(" ");
    Serial.println(m_pins[3]);*/

    digitalWrite(m_pins[0], bitRead(channel, 0));               // write the channel to the output pins
    digitalWrite(m_pins[1], bitRead(channel, 1));
    digitalWrite(m_pins[2], bitRead(channel, 2));
    digitalWrite(m_pins[3], bitRead(channel, 3));
    lastChannelWriteUs = 0;                                     // clock when the channel was last written.

    for(int i = 0; i < m_numberOfMultiplexers; i++)             // iterate through the multiplexers...
    {
        m_multiplexers[i]->setChannel(channel);
    }
}

void Multiplexer_Controller::update()
{
    if(lastChannelWriteUs > M_STABILISE_US)                     // once the multiplexers have had a chance to stabilise...
    {  
        for(int i = 0; i < m_numberOfMultiplexers; i++)         // ...update the interface elements.
        {
            m_multiplexers[i]->update();
        }
    }
    //this->setChannel(m_currentChannel);

    if(lastChannelWriteUs > M_UPDATE_RATE_US)                 // if the update rate is exceeded...        
    {   
        this->incrementChannel();                               // ...increrment the channel
    }
}

int Multiplexer_Controller::getNumberOfMultiplexers()
{
    return m_numberOfMultiplexers;
}