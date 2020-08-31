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
    MACHINE
};

class Game : public olc::PixelGameEngine {
public:
    Game();
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    bool OnUserDestroy() override;
private:
    SkillTree skillTree;
    StatusBar statusBar;
    CurrentState state = CurrentState::MACHINE;
    SoLoud::Soloud soloud;
    std::shared_ptr<olc::Renderable> speechBubbleSprite;
    float armSwitchTimer = 0.0f;
    float headBobTimer = 0.0f;

    //Menu Variables
    SpeechBubble testBubble{"Hello and welcome to\npart one of a new series...", "res/javid.wav", {70, ScreenHeight() - 64}, {ScreenWidth() - 12, 64}};
    
    //First Phase Variables
    bool aPressed = false;
    std::unique_ptr<olc::Renderable> aButtonSprite;
    std::unique_ptr<olc::Renderable> aButtonPressedSprite;
    std::unique_ptr<olc::Renderable> dButtonSprite;
    std::unique_ptr<olc::Renderable> dButtonPressedSprite;

    std::unique_ptr<olc::Renderable> javidBaseSprite;
    std::unique_ptr<olc::Renderable> javidLArmDownSprite;
    std::unique_ptr<olc::Renderable> javidLArmUpSprite;
    std::unique_ptr<olc::Renderable> javidRArmDownSprite;
    std::unique_ptr<olc::Renderable> javidRArmUpSprite;

    std::uint32_t pressCounter = 0;
    //Machine Variables
    std::unique_ptr<olc::Renderable> robotBaseSprite0;
    std::unique_ptr<olc::Renderable> robotBaseSprite1;
    std::unique_ptr<olc::Renderable> robotLArmDownSprite;
    std::unique_ptr<olc::Renderable> robotLArmUpSprite;
    std::unique_ptr<olc::Renderable> robotRArmDownSprite;
    std::unique_ptr<olc::Renderable> robotRArmUpSprite;
    float armSwitchPeriod = 1.0f;
    float headBobPeriod = 1.0f;
    std::uint64_t internetPoints = 0;
    std::unique_ptr<Minigame> currentMinigame;
};

#endif
