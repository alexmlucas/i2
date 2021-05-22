#include "Display_Controller.h"

Display_Controller::Display_Controller(Midi_Clock *masterClock)
{
    display.begin(ADDRESS);
    m_masterClock = masterClock;
    this->writeDots(0);
}

void Display_Controller::displayNumber(int number)
{
    int onesUnit = number % 10;
    int tensUnit = (number/10) % 10;
    int hundredsUnit = (number/100) % 10;
    
    if(number <= 9)
    {
        this->writeDigit(onesUnit);
    } else if (number <= 99)
    {
        this->writeDigit(tensUnit, onesUnit);
    } else if (number > 99)
    {
       this->writeDigit(hundredsUnit, tensUnit, onesUnit);
    }
}

void Display_Controller::poll()                 // used to clear the screen
{
    if(m_digitClearFlag == true)
    {
        if(m_timeSinceDigitWrite > DIGIT_CLEAR_TIMER)
        {
            this->clearDigits();
            display.writeDisplay();
            m_digitClearFlag = false;
        }
    }

    int currentMidiTick = m_masterClock->getMidiTick();

    if(currentMidiTick != m_lastMidiTick)
    {
        if(m_masterClock->isMidiTick4th())
        {
            this->setSegmentDotStates(m_beatIndex);
            this->writeDots(m_beatIndex);
            this->incrementBeatIndex();
            Serial.println("display tick");
        }
        m_lastMidiTick = currentMidiTick;
    }
}

void Display_Controller::clearDigits()
{
    int valueToWrite = 0x0;

    for(int i = 0; i < 4; i++)
    {
        if(m_segmentDotStates[i])
        {
            valueToWrite = 0x4000;
            display.writeDigitRaw(i, valueToWrite);
            
        } else
        {
            valueToWrite = 0x0;
            display.writeDigitRaw(i, valueToWrite);
        }
    }

    display.writeDisplay();
}

void Display_Controller::clearDots()
{
    display.clear();

    for(int i = 0; i < 4; i++)
    {
        if(m_currentDigits[i] != 0)
        {
            display.writeDigitAscii(i, m_currentDigits[i]);
        }
    }

    display.writeDisplay();
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

void Display_Controller::writeDigit(int onesDigit)
{
    char onesChar = '0' + onesDigit;            // convert int to char

    for(int i = 0; i < 4; i++)
    {
        m_currentDigits[i] = 0;                 // clear all
    }

    m_currentDigits[3] = onesChar;              // update char states

    this->clearDigits();                        // clear
    display.writeDigitAscii(3, onesChar);       // write
    display.writeDisplay();
    m_timeSinceDigitWrite = 0;
    m_digitClearFlag = true;
}

void Display_Controller::writeDigit(int tensDigit, int onesDigit)
{
    char onesChar = '0' + onesDigit;            // convert int to char
    char tensChar = '0' + tensDigit;            
    

    for(int i = 0; i < 4; i++)
    {
        m_currentDigits[i] = 0;                 // clear all
    }

    m_currentDigits[3] = onesChar;              // update char states
    m_currentDigits[2] = tensChar;              
    

    this->clearDigits();                        // clear
    display.writeDigitAscii(3, onesChar);       // write
    display.writeDigitAscii(2, tensChar);       
    display.writeDisplay();
    m_timeSinceDigitWrite = 0;
    m_digitClearFlag = true;
}

void Display_Controller::writeDigit(int hundredsDigit, int tensDigit, int onesDigit)
{
    char onesChar = '0' + onesDigit;            // convert int to char
    char tensChar = '0' + tensDigit;           
    char hundredsChar = '0' + hundredsDigit;       

    for(int i = 0; i < 4; i++)
    {
        m_currentDigits[i] = 0;                 // clear all
    }

    m_currentDigits[3] = onesChar;              // update char states
    m_currentDigits[2] = tensChar;              
    m_currentDigits[2] = hundredsChar; 

    this->clearDigits();                        // clear
    display.writeDigitAscii(3, onesChar);       // write
    display.writeDigitAscii(2, tensChar);
    display.writeDigitAscii(2, hundredsChar);      
    display.writeDisplay();
    m_timeSinceDigitWrite = 0;
    m_digitClearFlag = true;
}

void Display_Controller::writeDots(int dotOnIndex)
{
    display.clear();

    for(int i = 0; i < 4; i++)
    {
        if(m_currentDigits[i] != 0)
        {
            display.writeDigitAscii(i, m_currentDigits[i]);
        }
    }

    int valueToWrite = 0x0;

    for(int i = 0; i < 4; i++)
    {
        if(m_segmentDotStates[i])
        {
            valueToWrite = 0x4000;
            display.writeDigitRaw(i, valueToWrite);
            
        } else
        {
            valueToWrite = 0x0;
            display.writeDigitRaw(i, valueToWrite);
        }
    }

    display.writeDisplay();
}

void Display_Controller::resetBeatIndex()
{
    m_beatIndex = 0;
    this->setSegmentDotStates(0);
}