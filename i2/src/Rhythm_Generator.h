#ifndef RHYTHM_GENERATOR
#define RHYTHM_GENERATOR

#include <Arduino.h>
#include "Midi_Clock.h"
#include "Transport.h"
#include "Sample_Player.h"
#include "Led_Controller.h"
#include "Display_Controller.h"

class Rhythm_Generator
{
  private:
    const int RHYTHM_LENGTH = 8;
    byte m_rhythmValue;
    Midi_Clock *m_rhythmClock;
    Transport *m_transport;
    Sample_Player *m_samplePlayers;
    Led_Controller *m_ledController;
    Display_Controller *m_displayController;

    float m_velocity;
    int m_track;
    int m_currentStep;
    int m_lastMidiTick;
    int m_speed;
    bool m_isPlayingFlag;
    
  public:
    Rhythm_Generator(Midi_Clock* rhythmClock, Transport* transport, Sample_Player* samplePlayers);
    void poll();
    void setLedController(Led_Controller *ledController);
    void setDisplayController(Display_Controller *displayController);
    void setRhythm(int rhythmValue);
    void flipRhythmBit(int bitIndex);
    void displayRhythm();
    void advance();
    void triggerRhythm(int track, float velocity);
    int getTrigger();
    void setSpeed(int speed);
    int getSpeed();
    void decrementSpeed();
};

#endif
