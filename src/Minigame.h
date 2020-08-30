#ifndef TGM_MINIGAME_H
#define TGM_MINIGAME_H

#include <memory>
#include <string>
#include <vector>
#include <tuple>
#include <random>

#include "olcPixelGameEngine.h"

class Minigame {
public:
    virtual void start() = 0;
    virtual bool tick(olc::PixelGameEngine *pge) = 0;
    virtual void drawSelf(olc::PixelGameEngine *pge) = 0;
};

class CreatingVideoMinigame : public Minigame {
public:
    void start() override;
    bool tick(olc::PixelGameEngine *pge) override;
    void drawSelf(olc::PixelGameEngine *pge) override;
};

#endif
