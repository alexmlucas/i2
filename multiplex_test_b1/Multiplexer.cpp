#include "Multiplexer.h"

Multiplexer::Multiplexer(int pin, int numberOfChannels, int* channelDirections)
{
  m_pin = pin;
  m_numberOfChannels = numberOfChannels;
  m_channelDirections = channelDirections;
}

bool Multiplexer::isValidChannel(int channelNumber)
{
  return channelNumber <= m_numberOfChannels;
}

int Multiplexer::getDirection(int channelNumber)
{
  return m_channelDirections[channelNumber];
}
