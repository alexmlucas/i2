#include "Synchronised_Delay.h"

// ### PUBLIC ###

Synchronised_Delay::Synchronised_Delay(AudioEffectDelay* delayObject)
{
    m_delayObject = delayObject;

    for(int i = 1; i < 7; i++)                                  // iterate through the channels...
    {
        m_delayObject->disable(i);                              // ... to save audio memory, disable all channels other than the first.     
    }
}

void Synchronised_Delay::assignFilterObject(AudioFilterStateVariable* filterObject)
{
    m_filterObject = filterObject;
}

void Synchronised_Delay::assignWetDryMixerObjects(AudioMixer4* leftWetDryMixer, AudioMixer4* rightWetDryMixer)
{
    m_leftWetDryMixer = leftWetDryMixer;
    m_rightWetDryMixer = rightWetDryMixer;
}

void Synchronised_Delay::assignFeedbackAmplifierObject(AudioAmplifier* feedbackAmplifierObject)
{
    m_feedbackAmplifierObject = feedbackAmplifierObject;
}

void Synchronised_Delay::setDelayTime(int bpm)
{
    m_delayTimeMs = this->calculateTripletQuaverMs(bpm);
    m_delayObject->delay(DELAY_TAP_CHANNEL, m_delayTimeMs);
}

void Synchronised_Delay::setEffectIntensity(float intensity)
{
    float wetDryMixLevel = intensity * 0.5;                     // work the intensity value to get a pleasing result
    float feedbackLevel = intensity - 0.1;

    this->setWetDryMixLevel(wetDryMixLevel);
    this->setFeedbackLevel(feedbackLevel);
} 

// ### PRIVATE ###

int Synchronised_Delay::calculateTripletQuaverMs(int bpm)
{
    int crotchetInterval = MS_IN_MINUTE / bpm;
    int semiQuaverInterval = crotchetInterval / 4;
    int tripletQuaverMs = semiQuaverInterval * 3;
    
    return tripletQuaverMs;
}

void Synchronised_Delay::setWetDryMixLevel(float level)
{
    float invertedLevel = (level - 1);                                // invert the level
    invertedLevel = abs(invertedLevel);

    m_leftWetDryMixer->gain(DRY_MIXER_CHANNEL, invertedLevel);
    m_leftWetDryMixer->gain(WET_MIXER_CHANNEL, level);
    m_rightWetDryMixer->gain(DRY_MIXER_CHANNEL, invertedLevel);
    m_rightWetDryMixer->gain(WET_MIXER_CHANNEL, level);
}

void Synchronised_Delay::setFeedbackLevel(float level)
{
    m_feedbackAmplifierObject->gain(level);
}

void Synchronised_Delay::setFilterFrequency(int frequency)
{
    m_filterObject->frequency(FILTER_FREQUENCY_HZ);
}