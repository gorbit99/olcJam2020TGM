#ifndef TGM_STATUSBAR_H
#define TGM_STATUSBAR_H

#include "olcPixelGameEngine.h"

#include <cstdint>

class StatusBar {
public:
    void drawSelf(olc::PixelGameEngine *pge) const;
    void addWork();
private:
    std::uint64_t progress = 0;
};

#endif
