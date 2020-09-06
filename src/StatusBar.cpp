#include "StatusBar.h"

bool StatusBar::tick(olc::PixelGameEngine *pge) {
    if (progress == 100000) {
	currentJoke = "Feature Creep! +20%";
	visibilityAmount = 2.0f;
    }
    if (progress == 120000) {
	currentJoke = "Server Debugging! +20%";
	visibilityAmount = 2.0f;
    }
    if (progress == 140000) {
	currentJoke = "Redesign! +20%";
	visibilityAmount = 2.0f;
    }
    if (progress == 160000) {
	currentJoke = "Boredom! +20%";
	visibilityAmount = 2.0f;
    }
    if (progress == 180000) {
	currentJoke = "Development Hell! +20%";
	visibilityAmount = 2.0f;
    }
    if (progress == 200000) {
	currentJoke = "Side Projects! +300%";
	visibilityAmount = 2.0f;
    }

    visibilityAmount -= pge->GetElapsedTime() / 2;
    return false;
}

void StatusBar::drawSelf(olc::PixelGameEngine *pge) const {
    pge->FillRectDecal({pge->ScreenWidth() / 2 - 18.0f, 4}, {36, 12}, olc::BLUE);
    pge->DrawStringDecal({pge->ScreenWidth() / 2 - 16.0f, 6}, std::to_string(progress / 1000) + "%");
    pge->DrawStringDecal(
	    {pge->ScreenWidth() / 2.0f - pge->GetTextSize(currentJoke).x / 2, 30},
	    currentJoke,
	    olc::PixelF(1.0f, 0.0f, 0.0f, std::min(1.0f, std::max(0.0f, visibilityAmount)))
	    );
}

void StatusBar::addWork() {
    if (progress < 500000) {
	progress++;
    }
}

bool StatusBar::done() {
    return progress == 500000;
}
