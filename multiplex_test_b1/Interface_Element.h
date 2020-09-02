#ifndef INTERFACE_ELEMENT
#define INTERFACE_ELEMENT

class Interface_Element
{
  public:
    int m_pin;
    int m_direction;

    Interface_Element(int pin, int _direction);
    int getDirection();
};
