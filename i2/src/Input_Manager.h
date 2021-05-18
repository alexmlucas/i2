#ifndef INPUT_MANAGER
#define INPUT_MANAGER
#include <Arduino.h>
#include "Sample_Player.h"
#include "Constant_Parameters.h"
#include "Led_Controller.h"
#include "Rhythm_Generator.h"
#include "Parameter_Manager.h"
#include "Transport.h"
#include "Sequencer.h"
#include "Midi_Clock.h"
#include "Display_Controller.h"
#include "Output_Amplifier.h"

class Input_Manager
{
    private:
        const unsigned int MUX_READ_DELAY_US = 1;       // the delay between changing mux channel and reading it.
        const unsigned int DEBOUNCE_MS = 20;
        const int POT_NOISE_FILTER = 7;
        const int PIEZO_THRESHOLD = 10;                 // minimum reading, avoid "noise".
        const unsigned int PIEZO_PEAK_MS = 2;                          // time to read peak value.
        const unsigned int PIEZO_AFTERSHOCK_MS = 20;
        const unsigned int PRESS_HOLD_TIMER_MS = 1000;           // time of aftershocks and vibration.

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
        elapsedMillis m_undoTimer = 0;
        bool m_undoHeld = false;

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
        int m_kitPatternMenuState = 0;  // can perhaps remove default values and set extenally?
        int m_tempoVolMenuState = 0;
        int m_lastPatternValue = -1;    // do we need to set these during setup?
        int m_lastKitValue = -1;
        bool m_kitBankState = false;
        bool m_patternBankState = false;


        Sample_Player *m_samplePlayers;
        Led_Controller *m_ledController;
        Rhythm_Generator *m_rhythmGenerator;
        Parameter_Manager *m_parameterManager;
        Transport *m_transport;
        Sequencer *m_sequencer;
        Midi_Clock *m_masterClock;
        Midi_Clock *m_rhythmClock;
        Display_Controller *m_displayController;
        Output_Amplifier *m_outputAmplifier;

    public:
        Input_Manager();
        void setSamplePlayers(Sample_Player *samplePlayers);
        void setLedController(Led_Controller *ledController);
        void setRhythmGenerator(Rhythm_Generator *rhtyhmGenerator);
        void setParameterManager(Parameter_Manager *parameterManager);
        void setTransport(Transport *transport);
        void setClocks(Midi_Clock *masterClock, Midi_Clock *rhythmClock);
        void poll();
        void readMuxs();
        int readPiezo(int index);
        void readDirectPot();
        void setKitPatternMenuState(int state);
        void setTempoVolMenuState(int state);
        void flipKitPatternMenuState();
        void setSequencer(Sequencer *sequencer);
        void setSensor(int index);
        void setDisplayController(Display_Controller *displayController);
        void setOutputAmplifier(Output_Amplifier *outputAmplifier);
};

#endif