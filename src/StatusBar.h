#ifndef TGM_STATUSBAR_H
#define TGM_STATUSBAR_H

#include "olcPixelGameEngine.h"

#include <cstdint>

class StatusBar {
public:
    bool tick(olc::PixelGameEngine *pge);
    void drawSelf(olc::PixelGameEngine *pge) const;
    void addWork();
    bool done();
private:
    std::uint64_t progress = 0;
    std::string currentJoke = "";
    float visibilityAmount = 0.0f;
};

#endif
