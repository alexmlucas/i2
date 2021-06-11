#include "Output_Amplifier.h"

Output_Amplifier::Output_Amplifier(AudioAmplifier *leftAmp, AudioAmplifier *rightAmp)
{
    m_leftAmp = leftAmp;
    m_rightAmp = rightAmp;
}

void Output_Amplifier::setLevel(int level)
{
    m_level = level;
    m_leftAmp->gain(float(m_level * 0.1));         // convert value to float
    m_rightAmp->gain(float(m_level * 0.1));
}

int Output_Amplifier::getLevelAsInt()
{
    return m_level;
}

void Output_Amplifier::incrementLevel()
{
    if(m_level < 9)
    {
        m_level = m_level + 1;
    }
    m_leftAmp->gain(float(m_level * 0.1));
    m_rightAmp->gain(float(m_level * 0.1));
}

void Output_Amplifier::decrementLevel()
{
    if(m_level > 1)
    {
        m_level = m_level - 1;
    }
    m_leftAmp->gain(float(m_level * 0.1));
    m_rightAmp->gain(float(m_level * 0.1));
}