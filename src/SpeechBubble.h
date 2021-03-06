#ifndef TGM_SPEECHBUBBLE_H
#define TGM_SPEECHBUBBLE_H

#include <string>
#include <soloud.h>
#include <soloud_wav.h>
#include <cmath>

#include "olcPixelGameEngine.h"

class SpeechBubble {
public:
    SpeechBubble() = default;
    SpeechBubble(std::string text,
	    std::string soundPath,
	    olc::vi2d position,
	    olc::vi2d scale,
	    std::shared_ptr<olc::Renderable> sprite);
    void play(SoLoud::Soloud &soloud);
    void tick(float fElapsedTime);
    void drawSelf(olc::PixelGameEngine *pge);
    float getTimePastEnd();
private:
    std::string curText;
    std::shared_ptr<olc::Renderable> sprite;
    SoLoud::Wav soundSample;
    float timeElapsed = 0;
    olc::vi2d position;
    olc::vi2d scale;
};

#endif
