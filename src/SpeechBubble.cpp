#include "SpeechBubble.h"

SpeechBubble::SpeechBubble(std::string text,
	std::string soundPath,
	olc::vi2d position,
	olc::vi2d scale) 
    : curText{text}, position{position}, scale{scale}
{
    soundSample.load(soundPath.c_str());
}

void SpeechBubble::play(SoLoud::Soloud &soloud) {
    soloud.play(soundSample);
}

void SpeechBubble::tick(float fElapsedTime) {
    timeElapsed += fElapsedTime;
}

void SpeechBubble::drawSelf(olc::PixelGameEngine *pge) {
    //Draw Background
    pge->DrawPartialDecal(position,
	    sprite->Decal(), {0, 0}, {16, 16});
    pge->DrawPartialDecal(position + olc::vi2d{scale.x - 16, 0},
	    sprite->Decal(), {32, 0}, {16, 16});
    pge->DrawPartialDecal(position + olc::vi2d{0, scale.y - 16},
	    sprite->Decal(), {0, 32}, {16, 16});
    pge->DrawPartialDecal(position + scale - olc::vi2d{16, 16},
	    sprite->Decal(), {32, 32}, {16, 16});
    pge->DrawPartialDecal(position + olc::vi2d{16, 0},
	    sprite->Decal(), {16, 0}, {16, 16},
	    {(scale.x - 32) / 16.0f, 1});
    pge->DrawPartialDecal(position + olc::vi2d{16, scale.y - 16},
	    sprite->Decal(), {16, 32}, {16, 16},
	    {(scale.x - 32) / 16.0f, 1});
    pge->DrawPartialDecal(position + olc::vi2d{0, 16},
	    sprite->Decal(), {0, 16}, {16, 16},
	    {1, (scale.y - 32) / 16.0f});
    pge->DrawPartialDecal(position + olc::vi2d{scale.x - 16, 16},
	    sprite->Decal(), {32, 16}, {16, 16},
	    {1, (scale.y - 32) / 16.0f});
    pge->DrawPartialDecal(position + olc::vi2d{16, 16},
	    sprite->Decal(), {16, 16}, {16, 16},
	    {(scale.x - 32) / 16.0f, (scale.y - 32) / 16.0f});

    pge->DrawStringDecal(position + olc::vi2d{6, 6},
	    curText.substr(0, int(curText.size() * (timeElapsed / soundSample.getLength())))
	    );
}

float SpeechBubble::getTimePastEnd() {
    return std::max(0.0, timeElapsed - soundSample.getLength());
}

void SpeechBubble::setBackgroundSprite(std::shared_ptr<olc::Renderable> sprite) {
    this->sprite = sprite;
}
