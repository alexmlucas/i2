#ifndef MULTIPLEXER
#define MULTIPLEXER

class Multiplexer
{
  public:
    int m_pin;
    int m_numberOfChannels;
    int* m_channelDirections;

    Multiplexer(int pin, int numberOfChannels, int* channelDirections);
    bool isValidChannel(int channel);                                         // filter channels that are out of range.
    int getDirection(int channel);                                            // input = 0, output = 1.
};

#endif
