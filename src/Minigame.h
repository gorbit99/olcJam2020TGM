#ifndef TGM_MINIGAME_H
#define TGM_MINIGAME_H

#include "olcPixelGameEngine.h"

class Minigame {
public:
    virtual void start() = 0;
    virtual bool tick(olc::PixelGameEngine *pge, std::int64_t &internetPoints) = 0;
    virtual void drawSelf(olc::PixelGameEngine *pge) = 0;
};

class CreatingVideoMinigame : public Minigame {
public:
    void start() override;
    bool tick(olc::PixelGameEngine *pge, std::int64_t &internetPoints) override;
    void drawSelf(olc::PixelGameEngine *pge) override;
};

#endif
