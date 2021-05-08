#include "Display_Controller.h"

Display_Controller::Display_Controller()
{
    display.begin(ADDRESS);
}

void Display_Controller::displayNumber(int number)
{
    // features funkyness to separate digits and write to correct positions on display.
    int onesUnit = number % 10;
    int tensUnit = (number/10) % 10;
    int hundredsUnit = (number/100) % 10;

    if(number <= 9)
    {
        display.clear();
        display.writeDigitNum(3, onesUnit, false);
    } else if (number <= 99)
    {
        display.clear();
        display.writeDigitNum(3, onesUnit, false);
        display.writeDigitNum(2, tensUnit, false);
    } else if (number > 99)
    {
        display.clear();
        display.writeDigitNum(3, onesUnit, false);
        display.writeDigitNum(2, tensUnit, false);
        display.writeDigitNum(1, hundredsUnit, false);
    }

    display.writeDisplay();
    m_timeSinceWrite = 0;
    m_clearFlag = true;
}

void Display_Controller::poll()                 // used to clear the screen
{
    if(m_clearFlag == true)
    {
        if(m_timeSinceWrite > CLEAR_TIMER)
        {
            display.clear();
            display.writeDisplay();
            m_clearFlag = false;
            Serial.println("clearing");
        }
    }
}

