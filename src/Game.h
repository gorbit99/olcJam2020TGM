#ifndef TGM_GAME_H
#define TGM_GAME_H

#include "olcPixelGameEngine.h"
#include "SkillTree.h"
#include "StatusBar.h"
#include "SpeechBubble.h"
#include "Minigame.h"
#include "ModeratingDiscordMinigame.h"
#include "AnsweringCommentsMinigame.h"

enum class CurrentState {
    MENU,
    FIRST_PHASE,
    MACHINE,
    WIN
};

class Game : public olc::PixelGameEngine {
public:
    Game();
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    bool OnUserDestroy() override;
private:
    StatusBar statusBar;
    CurrentState state = CurrentState::MENU;
    SoLoud::Soloud soloud;
    std::shared_ptr<olc::Renderable> speechBubbleSprite;
    float armSwitchTimer = 0.0f;
    float headBobTimer = 0.0f;

    //Menu Variables
    bool started = false;
    float menuFadeTimer = 0.0f;
    
    //First Phase Variables
    bool aPressed = false;
    olc::Renderable aButtonSprite;
    olc::Renderable aButtonPressedSprite;
    olc::Renderable dButtonSprite;
    olc::Renderable dButtonPressedSprite;

    olc::Renderable javidBaseSprite;
    olc::Renderable javidLArmDownSprite;
    olc::Renderable javidLArmUpSprite;
    olc::Renderable javidRArmDownSprite;
    olc::Renderable javidRArmUpSprite;

    std::uint32_t pressCounter = 0;

    SpeechBubble currentSpeechBubble;
    int cutsceneState = 0;
    float fadeoutTimer = 0.0f;
    //Machine Variables
    SkillTree skillTree;
    olc::Renderable robotBaseSprite0;
    olc::Renderable robotBaseSprite1;
    olc::Renderable robotLArmDownSprite;
    olc::Renderable robotLArmUpSprite;
    olc::Renderable robotRArmDownSprite;
    olc::Renderable robotRArmUpSprite;
    olc::Renderable ipSprite;
    std::vector<olc::Renderable> fastHandSprites;
    float armSwitchPeriod = 1.0f;
    float headBobPeriod = 1.0f;
    std::int64_t internetPoints = 0;
    std::shared_ptr<Minigame> currentMinigame;
    std::vector<std::shared_ptr<Minigame>> minigames;
    float minigameTimer = 0.0f;
    int curMinigameId = -1;
    std::mt19937 engine;
    std::uniform_int_distribution<int> minigameDistrib{0, 1};
    float winFadeTimer = 0.0f;
    //Win Variables
    olc::Renderable background;
};

#endif
