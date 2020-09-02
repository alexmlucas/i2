#ifndef INTERFACE_ELEMENT
#define INTERFACE_ELEMENT
#include <Arduino.h>

class Interface_Element
{
    protected:
        int m_direction;
        int m_pin;

    public:
        Interface_Element();
        //Interface_Element(int pin, int direction);
        int getDirection();        
        virtual void update() = 0;                      // define a pure virtual function.
        virtual void update(int pin) = 0; 
};

#endif