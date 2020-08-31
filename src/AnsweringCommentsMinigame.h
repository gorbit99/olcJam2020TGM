#ifndef TGM_ANSWERINGCOMMENTSMINIGAME_H
#define TGM_ANSWERINGCOMMENTSMINIGAME_H

#include <vector>
#include <tuple>
#include <random>

#include "Minigame.h"

class AnsweringCommentsMinigame : public Minigame {
public:
    AnsweringCommentsMinigame(std::string bgPath,
	    std::string pfpMaskPath,
	    std::string namesPath,
	    std::string interactPath,
	    std::string replyPath,
	    std::string textsPath,
	    std::string javidPfpSmallPath,
	    std::string pressAPath,
	    std::string pressDPath);
    void start() override;
    bool tick(olc::PixelGameEngine *pge) override;
    void drawSelf(olc::PixelGameEngine *pge) override;
private:
    std::unique_ptr<olc::Renderable> bgSprite;
    std::unique_ptr<olc::Renderable> pfpMaskSprite;
    std::unique_ptr<olc::Renderable> nameSprites;
    std::unique_ptr<olc::Renderable> interactSprite;
    std::unique_ptr<olc::Renderable> replySprite;
    std::unique_ptr<olc::Renderable> textSprites;
    std::unique_ptr<olc::Renderable> javidPfpSmallSprite;
    std::unique_ptr<olc::Renderable> pressASprite;
    std::unique_ptr<olc::Renderable> pressDSprite;
    std::vector<std::tuple<std::unique_ptr<olc::Renderable>, int, int, bool, int, size_t>> comments;
    float nextCommentTimer;
    std::mt19937 engine;
    std::uniform_real_distribution<float> nextCommentDistrib{1.0f, 2.0f};
    std::uniform_int_distribution<int> nameDistrib{0, 9};
    std::uniform_int_distribution<int> textDistrib{0, 9};
    std::uniform_int_distribution<std::uint8_t> colorDistrib{0, 255};
    size_t selectedId = -1;
    float selectedProgress = 0.0f;
    int adAnimCur = 0;
    float adAnimTimer = 0.0f;
    size_t maxId = 0;
    bool aPressed = false;
};

#endif
