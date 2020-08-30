#include "StatusBar.h"

void StatusBar::drawSelf(olc::PixelGameEngine *pge) const {
    pge->FillRectDecal({float(pge->ScreenWidth() / 2 - 50), 10.0f}, 
	    {float(progress / 1000), 3.0f},
	    olc::GREEN);
}

void StatusBar::addWork() {
    if (progress < 100000) {
	progress++;
    }
}
