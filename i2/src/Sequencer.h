#ifndef SEQUENCER
#define SEQUENCER

#include "Constant_Parameters.h"
#include "Pattern_32.h"
#include "Sample_Player.h"
#include "Midi_Clock.h"

class Sequencer
{
  private:
    int m_lastMidiTick;
    Midi_Clock* m_masterClock; 
    Pattern_32 patterns[PATTERN_AMOUNT];
    Sample_Player* m_samplePlayers;

  public:
    int m_currentPattern;
    int m_currentStep;
    double m_quantiseQueue[TRACK_AMOUNT];
    bool m_captureUndoData = false;
    int m_undoData[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    Sequencer(Midi_Clock* masterClock, Sample_Player* samplePlayers);
    void playStep();
    void playStep(int stepNumber);
    void advance();
    void addQueuedEvents();
    void setTriggerEvent(int trackNumber, float velocity, int quantisedStep);
    int getQuantisedStep();
    void poll();
    void setCaptureUndoData(int state);
    void logUndoData(int stepIndex, int sampleIndex);
    void removeStepData(int patternIndex, int stepIndex, int trackIndex);
    void clearCurrentPattern();
    void setPatternIndex(int patternIndex);
};

#endif
