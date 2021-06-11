#include "Display_Controller.h"

Display_Controller::Display_Controller(Midi_Clock *masterClock)
{
    display.begin(ADDRESS);
    m_masterClock = masterClock;
}

void Display_Controller::displayNumber(int number)
{
    int onesUnit = number % 10;
    int tensUnit = (number/10) % 10;
    int hundredsUnit = (number/100) % 10;

    m_currentDigits[3] = onesUnit;

    if(number > 99)
    {
        m_currentDigits[3] = onesUnit;
        m_currentDigits[2] = tensUnit;
        m_currentDigits[1] = hundredsUnit;
        m_currentDigits[0] = -1;
    } else if(number > 9)
    {
        m_currentDigits[3] = onesUnit;
        m_currentDigits[2] = tensUnit;
        m_currentDigits[1] = -1;
        m_currentDigits[0] = -1;

    } else 
    {
        m_currentDigits[3] = onesUnit;
        m_currentDigits[2] = -1;
        m_currentDigits[1] = -1;
        m_currentDigits[0] = -1;
    }

    this->refresh();
    m_digitClearFlag = true;
    m_timeSinceDigitEvent = 0;
}

void Display_Controller::poll()                 // used to clear the screen
{
    if(m_digitClearFlag == true)
    {
        if(m_timeSinceDigitEvent > DIGIT_CLEAR_TIMER)
        {
            this->clearDigitData();
            this->refresh();
            m_digitClearFlag = false;
        }
    }

    if(m_masterClock->m_runFlag)
    {
        int currentMidiTick = m_masterClock->getMidiTick();

        if(currentMidiTick != m_lastMidiTick)
        {
            if(m_masterClock->isMidiTick4th())
            {
                this->refresh();
                this->incrementBeatIndex();
                Serial.println("display tick");
            }
            m_lastMidiTick = currentMidiTick;
        }
    }
}

void Display_Controller::incrementBeatIndex()
{
    if(m_beatIndex < 3)
    {
        m_beatIndex++;
    } else
    {
        m_beatIndex = 0;
    }
}

void Display_Controller::setSegmentDotStates(int dotOnIndex)
{
    for(int i = 0; i < 4; i++)
    {
        m_segmentDotStates[i] = false;              // reset all
    }

    m_segmentDotStates[dotOnIndex] = true;
}

void Display_Controller::refresh()
{
    display.clear();                                     // clear display
    uint16_t valuesToWrite[4] = {0x0, 0x0, 0x0, 0x0};    // initialise value to display

    for(int i = 0; i < 4; i++)                           // capture the dot
    {
        if(m_beatIndex == i)
        {
            valuesToWrite[i] = 0x4000;
        }
    }

    for(int i = 0; i < 4; i++)             
    {         
        if(m_currentDigits[i] != -1)                     
        {
            valuesToWrite[i] = valuesToWrite[i] | m_numbertable[m_currentDigits[i]];        // combine character and dot
        }
        display.writeDigitRaw(i, valuesToWrite[i]);
    }
    
    display.writeDisplay();
}

void Display_Controller::resetBeatIndex()
{
    m_beatIndex = 0;
    this->setSegmentDotStates(0);
}

void Display_Controller::clearDigitData()
{
    for(int i = 0; i < 4; i++)
    {
        m_currentDigits[i] = -1;
    }
}