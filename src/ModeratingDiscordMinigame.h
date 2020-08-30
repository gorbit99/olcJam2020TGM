#ifndef TGM_MODERATINGDISCORDMINIGAME_H
#define TGM_MODERATINGDISCORDMINIGAME_H

#include "Minigame.h"

class ModeratingDiscordMinigame : public Minigame {
public:
    ModeratingDiscordMinigame(std::string bgPath,
	    std::string pfpPath,
	    std::string textPath,
	    std::string namePath,
	    std::string reportPath);
    void start() override;
    bool tick(olc::PixelGameEngine *pge) override;
    void drawSelf(olc::PixelGameEngine *pge) override;
private:
    std::unique_ptr<olc::Renderable> bgSprite;
    std::unique_ptr<olc::Renderable> pfpSprites;
    std::unique_ptr<olc::Renderable> textSprites;
    std::unique_ptr<olc::Renderable> nameSprites;
    std::unique_ptr<olc::Renderable> reportSprite;
    std::vector<std::tuple<bool, int, int>> chatEntries;
    std::mt19937 engine;
    std::uniform_real_distribution<float> timeDistrib{0.35f, 0.8f};
    std::uniform_int_distribution<int> badDistrib{0, 3};
    std::uniform_int_distribution<int> pfpDistrib{0, 9};
    std::uniform_int_distribution<int> textDistrib{0, 9};

    float nextTimeCountdown = 0.0f;
};

#endif
