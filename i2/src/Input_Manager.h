#ifndef INPUT_MANAGER
#define INPUT_MANAGER
#include <Arduino.h>
#include "Sample_Player.h"
#include "Constant_Parameters.h"
#include "Led_Controller.h"
#include "Rhythm_Generator.h"
#include "Parameter_Manager.h"

class Input_Manager
{
    private:
        const unsigned int MUX_READ_DELAY_US = 1;       // the delay between changing mux channel and reading it.
        const unsigned int DEBOUNCE_MS = 20;
        const int POT_NOISE_FILTER = 10;
        const int PIEZO_THRESHOLD = 10;                 // minimum reading, avoid "noise".
        const unsigned int PIEZO_PEAK_MS = 2;                          // time to read peak value.
        const unsigned int PIEZO_AFTERSHOCK_MS = 20;                   // time of aftershocks and vibration.

        const int m_rhythmPotPin = A19;  
        const int m_muxAInPin = A13;
        int m_muxBInPin = A20;
        int m_muxCInPin = A17;
        int m_muxSelPin0 = 35;
        int m_muxSelPin1 = 34;
        int m_muxSelPin2 = 33;
        
        int m_piezoPins[4] = {A2, A1, A0, A3};                                 // The pin the piezo is connected to.
        int m_piezoPeaks[4];                                // Remember the last peak value.
        int m_piezoStates[4];                               // Activity scan state.
        elapsedMillis m_piezoTimers[4];

        int m_muxAButtonStates[8];
        int m_muxBButtonStates[8];
        int m_muxCButtonStates[8];
        int m_echoPotLastRawValue;
        int m_rhythmPotLastRawValue;
        int m_rhythmPotLastMappedValue;

        int m_muxAButtonEventTimes[8];
        int m_muxBButtonEventTimes[8];
        int m_muxCButtonEventTimes[8];

        elapsedMicros m_muxReadTimer;

        int m_muxReadIndex;
        bool m_readMuxChannel;
        bool m_changeMuxChannel;
        bool m_readMe;

        Sample_Player *m_samplePlayers;
        Led_Controller *m_ledController;
        Rhythm_Generator *m_rhythmGenerator;
        Parameter_Manager *m_parameterManager;

        void setSensor(int index);

    public:
        Input_Manager();
        void setSamplePlayers(Sample_Player *samplePlayers);
        void setLedController(Led_Controller *ledController);
        void setRhythmGenerator(Rhythm_Generator *rhtyhmGenerator);
        void setParameterManager(Parameter_Manager *parameterManager);
        void poll();
        void readMuxs();
        int readPiezo(int index);
        void readDirectPot();
};

#endif