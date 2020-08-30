#ifndef TGM_ANSWERINGCOMMENTSMINIGAME_H
#define TGM_ANSWERINGCOMMENTSMINIGAME_H

#include "Minigame.h"

class AnsweringCommentsMinigame : public Minigame {
public:
    AnsweringCommentsMinigame();
    void start() override;
    bool tick(olc::PixelGameEngine *pge) override;
    void drawSelf(olc::PixelGameEngine *pge) override;
private:
};

#endif
