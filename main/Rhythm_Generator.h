#ifndef RHYTHM_GENERATOR
#define RHYTHM_GENERATOR

#include <Arduino.h>
#include "Midi_Clock.h"
#include "Transport.h"
#include "Sample_Player.h"

class Rhythm_Generator
{
  private:
    const int RHYTHM_LENGTH = 8;
    byte m_rhythm;
    Midi_Clock* m_rhythmClock;
    Transport* m_transport;
    Sample_Player* m_samplePlayers;
    float m_velocity;
    int m_track;
    int m_currentStep;
    int m_lastMidiTick;
    int m_playbackSpeed;
    bool m_isPlayingFlag;
    
  public:
    Rhythm_Generator(Midi_Clock* rhythmClock, Transport* transport, Sample_Player* samplePlayers);
    void printRhythm();
    void poll();
    void setPlaybackSpeed(int playbackSpeed);
    void advance();
    
    void triggerRhythm(int track, float velocity);
    float getTrigger();
};

#endif
