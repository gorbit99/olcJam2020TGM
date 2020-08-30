#include "Game.h"

Game::Game() {
    sAppName = "I'm gonna make an MMO!";
}

bool Game::OnUserCreate() {
    aButtonSprite = std::make_unique<olc::Renderable>();
    aButtonPressedSprite = std::make_unique<olc::Renderable>();
    dButtonSprite = std::make_unique<olc::Renderable>();
    dButtonPressedSprite = std::make_unique<olc::Renderable>();
    aButtonSprite->Load("res/aButton.png");
    aButtonPressedSprite->Load("res/aButtonPressed.png");
    dButtonSprite->Load("res/dButton.png");
    dButtonPressedSprite->Load("res/dButtonPressed.png");

    javidBaseSprite = std::make_unique<olc::Renderable>();
    javidLArmDownSprite = std::make_unique<olc::Renderable>();
    javidLArmUpSprite = std::make_unique<olc::Renderable>();
    javidRArmDownSprite = std::make_unique<olc::Renderable>();
    javidRArmUpSprite = std::make_unique<olc::Renderable>();
    javidBaseSprite->Load("res/javidBase.png");
    javidLArmDownSprite->Load("res/javidLArmDown.png");
    javidLArmUpSprite->Load("res/javidLArmUp.png");
    javidRArmDownSprite->Load("res/javidRArmDown.png");
    javidRArmUpSprite->Load("res/javidRArmUp.png");

    robotBaseSprite0 = std::make_unique<olc::Renderable>();
    robotBaseSprite1 = std::make_unique<olc::Renderable>();
    robotLArmDownSprite = std::make_unique<olc::Renderable>();
    robotLArmUpSprite = std::make_unique<olc::Renderable>();
    robotRArmDownSprite = std::make_unique<olc::Renderable>();
    robotRArmUpSprite = std::make_unique<olc::Renderable>();
    robotBaseSprite0->Load("res/robotBase0.png");
    robotBaseSprite1->Load("res/robotBase1.png");
    robotLArmDownSprite->Load("res/robotLArmDown.png");
    robotLArmUpSprite->Load("res/robotLArmUp.png");
    robotRArmDownSprite->Load("res/robotRArmDown.png");
    robotRArmUpSprite->Load("res/robotRArmUp.png");

    speechBubbleSprite = std::make_shared<olc::Renderable>();
    speechBubbleSprite->Load("res/speechBubble.png");

    soloud.init();

    testBubble.play(soloud);
    testBubble.setBackgroundSprite(speechBubbleSprite);

    currentMinigame = std::make_unique<ModeratingDiscordMinigame>(
	    "res/minigames/discordModeration/bg.png",
	    "res/minigames/discordModeration/pfp.png",
	    "res/minigames/discordModeration/texts.png",
	    "res/minigames/discordModeration/names.png",
	    "res/minigames/discordModeration/report.png"
	    );
    return true;
}

bool Game::OnUserUpdate(float fElapsedTime) {
    switch(state) {
	case CurrentState::MENU:
	{
	    break;
	}
	case CurrentState::FIRST_PHASE:
	{
	    //Update
	    if (GetKey(olc::A).bPressed) {
		aPressed = true;
	    }
	    if (GetKey(olc::D).bPressed && aPressed) {
		statusBar.addWork();
		aPressed = false;
		pressCounter++;
	    }
	    statusBar.drawSelf(this);

	    testBubble.tick(fElapsedTime);
	    testBubble.drawSelf(this);

	    //Draw
	    DrawDecal({0, ScreenHeight() - 64.0f}, robotBaseSprite0->Decal(), {2, 2});

	    if (aPressed) {
		DrawDecal({float(ScreenWidth() / 2 - 40 - aButtonSprite->Sprite()->width),
			float(ScreenHeight() / 2 - aButtonSprite->Sprite()->height / 2)},
			aButtonPressedSprite->Decal());
		DrawDecal({float(ScreenWidth() / 2 + 40),
			float(ScreenHeight() / 2 - dButtonSprite->Sprite()->height / 2)},
			dButtonSprite->Decal());
		DrawDecal({0, ScreenHeight() - 64.0f}, javidRArmDownSprite->Decal(), {2, 2});
		DrawDecal({0, ScreenHeight() - 64.0f}, javidLArmUpSprite->Decal(), {2, 2});
	    } else {
		DrawDecal({float(ScreenWidth() / 2 - 40 - aButtonSprite->Sprite()->width),
			float(ScreenHeight() / 2 - aButtonSprite->Sprite()->height / 2)},
			aButtonSprite->Decal());
		DrawDecal({float(ScreenWidth() / 2 + 40),
			float(ScreenHeight() / 2 - dButtonSprite->Sprite()->height / 2)},
			dButtonPressedSprite->Decal());
		DrawDecal({0, ScreenHeight() - 64.0f}, javidRArmUpSprite->Decal(), {2, 2});
		DrawDecal({0, ScreenHeight() - 64.0f}, javidLArmDownSprite->Decal(), {2, 2});
	    }

	    break;
	}
	case CurrentState::MACHINE:
	{
	    //Update
	    armSwitchTimer += fElapsedTime;
	    headBobTimer += fElapsedTime;
	    //Draw
	    if (headBobTimer <= headBobPeriod / 2) {
		DrawDecal({0, ScreenHeight() - 64.0f}, robotBaseSprite0->Decal(), {2, 2});
	    } else {
		DrawDecal({0, ScreenHeight() - 64.0f}, robotBaseSprite1->Decal(), {2, 2});
	    }
	    if (headBobTimer >= headBobPeriod) {
		headBobTimer -= headBobPeriod;
	    }

	    if (armSwitchTimer <= armSwitchPeriod / 2) {
		DrawDecal({0, ScreenHeight() - 64.0f}, robotRArmDownSprite->Decal(), {2, 2});
		DrawDecal({0, ScreenHeight() - 64.0f}, robotLArmUpSprite->Decal(), {2, 2});
	    } else {
		DrawDecal({0, ScreenHeight() - 64.0f}, robotRArmUpSprite->Decal(), {2, 2});
		DrawDecal({0, ScreenHeight() - 64.0f}, robotLArmDownSprite->Decal(), {2, 2});
	    }
	    if (armSwitchTimer >= armSwitchPeriod) {
		armSwitchTimer -= armSwitchPeriod;
		statusBar.addWork();
	    }

	    currentMinigame->tick(this);
	    currentMinigame->drawSelf(this);

	    break;
	}
    }
    return true;
}

bool Game::OnUserDestroy() {
    soloud.deinit();
    return true;
}
