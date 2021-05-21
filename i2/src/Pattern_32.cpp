#include "Pattern_32.h"

Pattern_32::Pattern_32()
{
  // initialise steps to zero velocity.
  
  for(int i = 0; i < (PATTERN_LENGTH - 1); i++)
  {
    for(int ii = 0; ii < (TRACK_AMOUNT - 1); ii++)
    {
      m_steps[i][ii] = 0.0;
    }
  }
}
