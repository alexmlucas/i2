#ifndef EEPROM_PARAMETER
#define EEPROM_PARAMETER

struct Eeprom_Parameter
{
    int storageIndex;
    int value;
    bool writeFlag;
};

#endif