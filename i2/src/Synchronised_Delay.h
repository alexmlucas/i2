#ifndef SYNCRONISED_DELAY
#define SYNCRONISED_DELAY

#include "Arduino.h"
#include <Audio.h>

class Synchronised_Delay
{
    public:
        Synchronised_Delay(AudioEffectDelay* delayObject);
        void assignFilterObject(AudioFilterStateVariable* filterObject);
        void assignWetDryMixerObjects(AudioMixer4* leftWetDryMixer, AudioMixer4* rightWetDryMixer);
        void assignFeedbackAmplifierObject(AudioAmplifier* feedbackAmplifierObject);
        void setDelayTime(int bpm);
        void setEffectIntensity(float intensity);                   // expects a value between 0 and 1.
        
    private:
        const int MS_IN_MINUTE = 60000;
        const int DELAY_TAP_CHANNEL = 0;
        const int DRY_MIXER_CHANNEL = 0;
        const int WET_MIXER_CHANNEL = 1;
        const int FILTER_FREQUENCY_HZ = 200;
        int m_leftMixerChannelNumber;
        int m_rightMixerChannelNumber;
        int m_delayTimeMs;
        AudioEffectDelay* m_delayObject;
        AudioFilterStateVariable* m_filterObject;

        AudioMixer4* m_leftWetDryMixer;
        AudioMixer4* m_rightWetDryMixer;

        AudioAmplifier* m_feedbackAmplifierObject;
        AudioAmplifier* m_rightFeedbackAmplifier;
        
        int calculateTripletQuaverMs(int bpm);
        void setWetDryMixLevel(float level);
        void setFeedbackLevel(float level);
        void setFilterFrequency(int frequency);              
};

#endif
