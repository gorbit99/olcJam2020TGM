#include "Game.h"

Game::Game()
    : skillTree(this) {
    sAppName = "I'm gonna make an MMO!";
}

bool Game::OnUserCreate() {
    aButtonSprite.Load("res/aButton.png");
    aButtonPressedSprite.Load("res/aButtonPressed.png");
    dButtonSprite.Load("res/dButton.png");
    dButtonPressedSprite.Load("res/dButtonPressed.png");

    javidBaseSprite.Load("res/javidBase.png");
    javidLArmDownSprite.Load("res/javidLArmDown.png");
    javidLArmUpSprite.Load("res/javidLArmUp.png");
    javidRArmDownSprite.Load("res/javidRArmDown.png");
    javidRArmUpSprite.Load("res/javidRArmUp.png");

    robotBaseSprite0.Load("res/robotBase0.png");
    robotBaseSprite1.Load("res/robotBase1.png");
    robotLArmDownSprite.Load("res/robotLArmDown.png");
    robotLArmUpSprite.Load("res/robotLArmUp.png");
    robotRArmDownSprite.Load("res/robotRArmDown.png");
    robotRArmUpSprite.Load("res/robotRArmUp.png");

    speechBubbleSprite = std::make_shared<olc::Renderable>();
    speechBubbleSprite->Load("res/speechBubble.png");

    fastHandSprites.resize(3);
    fastHandSprites[0].Load("res/fastHands0.png");
    fastHandSprites[1].Load("res/fastHands1.png");
    fastHandSprites[2].Load("res/fastHands2.png");

    background.Load("res/win.png");

    ipSprite.Load("res/ip.png");

    soloud.init();

    minigames.push_back(std::make_unique<AnsweringCommentsMinigame>(
		"res/minigames/commentAnswering/bg.png",
		"res/minigames/commentAnswering/pfpMask.png",
		"res/minigames/commentAnswering/names.png",
		"res/minigames/commentAnswering/interactBar.png",
		"res/minigames/commentAnswering/reply.png",
		"res/minigames/commentAnswering/texts.png",
		"res/minigames/commentAnswering/javidPfpSmall.png",
		"res/minigames/commentAnswering/pressA.png",
		"res/minigames/commentAnswering/pressD.png"
		));
    minigames.push_back(std::make_unique<ModeratingDiscordMinigame>(
		"res/minigames/discordModeration/bg.png",
		"res/minigames/discordModeration/pfp.png",
		"res/minigames/discordModeration/texts.png",
		"res/minigames/discordModeration/names.png",
		"res/minigames/discordModeration/report.png"
		));

    skillTree.addNode("Fingers",
	    "Who thought, that actually\nhaving digits might help",
	    "res/skills/fingers.png",
	    0,
	    100);
    skillTree.addNode("Aerodynamic Arms",
	    "You added some small paper\nflaps, it could help",
	    "res/skills/aerodynamic.png",
	    0,
	    150);
    skillTree.addNode("Faster Typing",
	    "By changing the servos,\nyou can speed up the arms",
	    "res/skills/fastertyping.png",
	    0,
	    125);
    skillTree.addNode("Faster Logic",
	    "If Mr. Whatever's game has\ntaught you anything, it's\nthat you're bad at logic",
	    "res/skills/fasterlogic.png",
	    0,
	    100);
    skillTree.addNode("Touch Typing",
	    "You were told, that using\nyour eyes while typing\nslows you down a lot",
	    "res/skills/touch.png",
	    1,
	    200);
    skillTree.addNode("Lubrication",
	    "You add some WD 40, all\nthe memes say it works",
	    "res/skills/lubrication.png",
	    1,
	    250);
    skillTree.addNode("Concentration Music",
	    "Since the bot is smarter,\nit might appreciate it",
	    "res/skills/concentration.png",
	    1,
	    300);
    skillTree.addNode("Mechanical Keyboard",
	    "They say it's better,\nyou're just not sure how",
	    "res/skills/mechanical.png",
	    2,
	    350);
    skillTree.addNode("Plugged",
	    "You're not quite sure how\nit worked before, but it\nseems to stare at you more\nintensely",
	    "res/skills/plugged.png",
	    2,
	    350);
    skillTree.addNode("Agile Development",
	    "You've heard it helps\nefficiency, you also heard\nthe robot say something\nabout revolution",
	    "res/skills/agile.png",
	    2,
	    400);
    skillTree.addNode("Fidget Widgets",
	    "The bot was dozing off a\nlot, maybe this helps",
	    "res/skills/fidget.png",
	    2,
	    350);
    skillTree.addNode("Dadjokes",
	    "You tell a joke to the\nrobot, it agrees to work\nfaster if you stop",
	    "res/skills/dadjoke.png",
	    3,
	    450);
    skillTree.addNode("Tea and Flapjacks",
	    "It wanted some\nnourishments, this is the\nbest you had",
	    "res/skills/tea.png",
	    3,
	    450);
    skillTree.addNode("Visual Studio",
	    "You installed visual\nstudio, so it can work\nfaster... it proceeded to\nignore it",
	    "res/skills/vs.png",
	    3,
	    550);
    skillTree.addNode("Hungarian Notation",
	    "It apparently helps, maybe\nit will help here too",
	    "res/skills/hungarian.png",
	    4,
	    600);
    skillTree.addNode("Pylons",
	    "You heard a nagging voice\nthat just told you to\nbuild more pylons",
	    "res/skills/pylon.png",
	    4,
	    700);
    skillTree.addNode("Ducktales, Woohoo",
	    "You speedran in front of\nthe bot to get it inspired",
	    "res/skills/ducktales.png",
	    4,
	    700);
    skillTree.addNode("Vim",
	    "You also installed Vim, it\nignored that, but faster",
	    "res/skills/vim.png",
	    4,
	    650);
    skillTree.addNode("Singularity",
	    "You allow the bot to\nupdate itself, it\nquickly gives up when it\nsees your code",
	    "res/skills/singularity.png",
	    5,
	    800);
    skillTree.addNode("RTX 3090",
	    "Yes, it was a worthwhile\ninvestment, shut up",
	    "res/skills/rtx.png",
	    5,
	    800);
    skillTree.addNode("Programming Books",
	    "They are from the 80s, but\nso are you, so no worries\nthere",
	    "res/skills/patterns.png",
	    5,
	    900);
    skillTree.addNode("Workers' Union",
	    "The bot was really\ndemanding one, so you made\nit",
	    "res/skills/workers.png",
	    6,
	    1200);
    skillTree.addNode("Shorter Cables",
	    "That .1 microsecond delay\nwas starting to be\nunbearable",
	    "res/skills/shorter.png",
	    6,
	    1300);
    skillTree.addNode("The Great Machine",
	    "You did it, you made\nevery working man's worst\nfear",
	    "res/skills/tgm.png",
	    7,
	    5000);
    skillTree.addDependency("Touch Typing", "Fingers");
    skillTree.addDependency("Touch Typing", "Aerodynamic Arms");
    skillTree.addDependency("Lubrication", "Faster Typing");
    skillTree.addDependency("Concentration Music", "Faster Logic");
    skillTree.addDependency("Mechanical Keyboard", "Touch Typing");
    skillTree.addDependency("Plugged", "Lubrication");
    skillTree.addDependency("Agile Development", "Lubrication");
    skillTree.addDependency("Fidget Widgets", "Concentration Music");
    skillTree.addDependency("Dadjokes", "Mechanical Keyboard");
    skillTree.addDependency("Dadjokes", "Plugged");
    skillTree.addDependency("Tea and Flapjacks", "Plugged");
    skillTree.addDependency("Tea and Flapjacks", "Agile Development");
    skillTree.addDependency("Visual Studio", "Fidget Widgets");
    skillTree.addDependency("Hungarian Notation", "Dadjokes");
    skillTree.addDependency("Pylons", "Dadjokes");
    skillTree.addDependency("Pylons", "Tea and Flapjacks");
    skillTree.addDependency("Ducktales, Woohoo", "Visual Studio");
    skillTree.addDependency("Vim", "Visual Studio");
    skillTree.addDependency("Singularity", "Hungarian Notation");
    skillTree.addDependency("Singularity", "Pylons");
    skillTree.addDependency("RTX 3090", "Pylons");
    skillTree.addDependency("RTX 3090", "Ducktales, Woohoo");
    skillTree.addDependency("Programming Books", "Vim");
    skillTree.addDependency("Workers' Union", "Singularity");
    skillTree.addDependency("Workers' Union", "RTX 3090");
    skillTree.addDependency("Shorter Cables", "RTX 3090");
    skillTree.addDependency("Shorter Cables", "Programming Books");
    skillTree.addDependency("The Great Machine", "Workers' Union");
    skillTree.addDependency("The Great Machine", "Shorter Cables");
    
    SetPixelMode(olc::Pixel::MASK);
    return true;
}

bool Game::OnUserUpdate(float fElapsedTime) {
    switch(state) {
	case CurrentState::MENU:
	    {
		const auto mousePos = GetMousePos();
		if (mousePos.x >= ScreenWidth() / 2 - 50 && mousePos.x <= ScreenWidth() / 2 + 50 &&
			mousePos.y >= ScreenHeight() / 2 - 10 && mousePos.y <= ScreenHeight() / 2 + 10 &&
			GetMouse(0).bPressed &&
			!started) {
		    started = true;
		}
		if (started) {
		    menuFadeTimer += fElapsedTime;
		}
		if (menuFadeTimer >= 2.0f) {
		    state = CurrentState::FIRST_PHASE;
		}
		DrawStringDecal(
			olc::vf2d{float(ScreenWidth() / 2), 40.0f} -
			GetTextSize("The Great\n   MMO  \n Machine "),
			"The Great\n   MMO  \n Machine ",
			olc::BLUE,
			{2.0f, 2.0f});
		FillRectDecal(
			{ScreenWidth() / 2 - 50.0f, ScreenHeight() / 2 - 10.0f},
			{100.0f, 20.0f},
			olc::WHITE);
		DrawStringDecal(
			olc::vf2d{float(ScreenWidth() / 2), float(ScreenHeight() / 2)} -
			GetTextSize("Play") / 2,
			"Play",
			olc::BLUE);
		FillRectDecal({0.0f, 0.0f},
			{float(ScreenWidth()), float(ScreenHeight())},
			olc::PixelF(0.0f, 0.0f, 0.0f, menuFadeTimer / 2));
		break;
	    }
	case CurrentState::FIRST_PHASE:
	    {
		//Update
		switch (cutsceneState) {
		    case 0:
			currentSpeechBubble = SpeechBubble{
			    "Hmm, I really need a new\nvideo idea...",
			    "res/sounds/hmm.wav",
			    {70, ScreenHeight() - 64},
			    {ScreenWidth() - 76, 64},
			    speechBubbleSprite
			};
			currentSpeechBubble.play(soloud);
			cutsceneState = 1;
			break;
		    case 1:
			if (currentSpeechBubble.getTimePastEnd() >= 3) {
			    currentSpeechBubble = SpeechBubble{
				"I know, I'm gonna make an mmo",
				"res/sounds/iknow.wav",
				{70, ScreenHeight() - 64},
				{ScreenWidth() - 76, 64},
				speechBubbleSprite
			    };
			    currentSpeechBubble.play(soloud);
			    cutsceneState = 2;
			}
			break;
		    case 2:
			if (currentSpeechBubble.getTimePastEnd() >= 3) {
			    cutsceneState = 3;
			}
			break;
		    case 3:
			if (GetKey(olc::A).bPressed) {
			    aPressed = true;
			}
			if (GetKey(olc::D).bPressed && aPressed) {
			    statusBar.addWork();
			    aPressed = false;
			    pressCounter++;
			}
			if (pressCounter == 30) {
			    cutsceneState = 4;
			}
			break;
		    case 4:
			currentSpeechBubble = SpeechBubble{
			    "Eugh, this is going slowly",
			    "res/sounds/eughh.wav",
			    {70, ScreenHeight() - 64},
			    {ScreenWidth() - 76, 64},
			    speechBubbleSprite
			};
			currentSpeechBubble.play(soloud);
			cutsceneState = 5;
			break;
		    case 5:
			if (currentSpeechBubble.getTimePastEnd() >= 3) {
			    currentSpeechBubble = SpeechBubble{
				"I know, I'm gonna make an mmo\nmaking machine, there's no\nway that goes wrong",
				"res/sounds/mmo.wav",
				{70, ScreenHeight() - 64},
				{ScreenWidth() - 76, 64},
				speechBubbleSprite
			    };
			    currentSpeechBubble.play(soloud);
			    cutsceneState = 6;
			}
			break;
		    case 6:
			if (currentSpeechBubble.getTimePastEnd() >= 3) {
			    cutsceneState = 7;
			}
			break;
		    case 7:
			fadeoutTimer += fElapsedTime;
			if (fadeoutTimer >= 4.0f) {
			    state = CurrentState::MACHINE;
			}
			break;
		}
		currentSpeechBubble.tick(fElapsedTime);

		//Draw
		DrawDecal({0, ScreenHeight() - 64.0f}, javidBaseSprite, {2, 2});

		if (cutsceneState == 3) {
		    if (aPressed) {
			DrawDecal({float(ScreenWidth() / 2 - 40 - aButtonSprite.Sprite()->width),
				float(ScreenHeight() / 2 - aButtonSprite.Sprite()->height / 2)},
				aButtonPressedSprite);
			DrawDecal({float(ScreenWidth() / 2 + 40),
				float(ScreenHeight() / 2 - dButtonSprite.Sprite()->height / 2)},
				dButtonSprite);
			DrawDecal({0, ScreenHeight() - 64.0f}, javidRArmDownSprite, {2, 2});
			DrawDecal({0, ScreenHeight() - 64.0f}, javidLArmUpSprite, {2, 2});
		    } else {
			DrawDecal({float(ScreenWidth() / 2 - 40 - aButtonSprite.Sprite()->width),
				float(ScreenHeight() / 2 - aButtonSprite.Sprite()->height / 2)},
				aButtonSprite);
			DrawDecal({float(ScreenWidth() / 2 + 40),
				float(ScreenHeight() / 2 - dButtonSprite.Sprite()->height / 2)},
				dButtonPressedSprite);
			DrawDecal({0, ScreenHeight() - 64.0f}, javidRArmUpSprite, {2, 2});
			DrawDecal({0, ScreenHeight() - 64.0f}, javidLArmDownSprite, {2, 2});
		    }
		} else {
		    DrawDecal({0, ScreenHeight() - 64.0f}, javidRArmDownSprite, {2, 2});
		    DrawDecal({0, ScreenHeight() - 64.0f}, javidLArmDownSprite, {2, 2});
		    currentSpeechBubble.drawSelf(this);
		}

		statusBar.drawSelf(this);

		float fadeoutColor = std::min(3.0f, fadeoutTimer) / 3.0f;

		FillRectDecal({0.0f, 0.0f},
			{float(ScreenWidth()), float(ScreenHeight())},
			olc::PixelF(0.0f, 0.0f, 0.0f, fadeoutColor));

		break;
	    }
	case CurrentState::MACHINE:
	    {
		//Update
		minigameTimer -= fElapsedTime;
		if (minigameTimer <= 0.0f) {
		    minigameTimer = 10.0f;
		    int nextMinigame = minigameDistrib(engine);
		    while (nextMinigame == curMinigameId) {
			nextMinigame = minigameDistrib(engine);
		    }
		    currentMinigame = minigames[nextMinigame];
		    curMinigameId = nextMinigame;
		    currentMinigame->start();
		}
		armSwitchTimer += fElapsedTime;
		headBobTimer += fElapsedTime;
		currentMinigame->tick(this, internetPoints);
		if (internetPoints < 0) {
		    internetPoints = 0;
		}
		if (skillTree.tick(this, internetPoints)) {
		    armSwitchPeriod *= 0.7f;
		}
		statusBar.tick(this);
		//Draw
		if (headBobTimer <= headBobPeriod / 2) {
		    DrawDecal({0, ScreenHeight() - 64.0f}, robotBaseSprite0, {2, 2});
		} else {
		    DrawDecal({0, ScreenHeight() - 64.0f}, robotBaseSprite1, {2, 2});
		}
		if (headBobTimer >= headBobPeriod) {
		    headBobTimer -= headBobPeriod;
		}

		if (armSwitchPeriod >= 0.016) {
		    if (armSwitchTimer <= armSwitchPeriod / 2) {
			DrawDecal({0, ScreenHeight() - 64.0f}, robotRArmDownSprite, {2, 2});
			DrawDecal({0, ScreenHeight() - 64.0f}, robotLArmUpSprite, {2, 2});
		    } else {
			DrawDecal({0, ScreenHeight() - 64.0f}, robotRArmUpSprite, {2, 2});
			DrawDecal({0, ScreenHeight() - 64.0f}, robotLArmDownSprite, {2, 2});
		    }
		} else {
		    DrawDecal({0, ScreenHeight() - 64.0f}, fastHandSprites[rand() % 3], {2, 2});
		}
		while (armSwitchTimer >= armSwitchPeriod) {
		    armSwitchTimer -= armSwitchPeriod;
		    statusBar.addWork();
		}

		currentMinigame->drawSelf(this);

		DrawDecal({0, 5}, ipSprite);
		DrawStringDecal({16, 9}, std::to_string(internetPoints));
		
		skillTree.drawSelf(this, internetPoints);
		statusBar.drawSelf(this);

		if (statusBar.done()) {
		    winFadeTimer += fElapsedTime;
		}

		FillRectDecal({0, 0},
			{float(ScreenWidth()), float(ScreenHeight())},
			olc::PixelF(0, 0, 0, winFadeTimer / 2));

		if (winFadeTimer >= 2.0f) {
		    state = CurrentState::WIN;
		}
		break;
	    }
	case CurrentState::WIN:
	    {
		DrawDecal({0, 0}, background);
		break;
	    }
    }
    return true;
}

bool Game::OnUserDestroy() {
    soloud.deinit();
    return true;
}
