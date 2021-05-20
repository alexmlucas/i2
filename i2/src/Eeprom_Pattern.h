#ifndef EEPROM_PATTERN
#define EEPROM_PATTERN
#include "Pattern_32.h" 


struct Eeprom_Pattern
{
    int storageZeroIndex;
    Pattern_32 pattern;
    bool writeFlag;
};

#endif