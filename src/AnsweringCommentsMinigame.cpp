#include "AnsweringCommentsMinigame.h"

AnsweringCommentsMinigame::AnsweringCommentsMinigame(std::string bgPath,
	std::string pfpMaskPath,
	std::string namesPath,
	std::string interactPath,
	std::string replyPath,
	std::string textsPath,
	std::string javidPfpSmallPath,
	std::string pressAPath,
	std::string pressDPath) {
    bgSprite.Load(bgPath);
    pfpMaskSprite.Load(pfpMaskPath);
    nameSprites.Load(namesPath);
    interactSprite.Load(interactPath);
    replySprite.Load(replyPath);
    textSprites.Load(textsPath);
    javidPfpSmallSprite.Load(javidPfpSmallPath);
    pressASprite.Load(pressAPath);
    pressDSprite.Load(pressDPath);
    engine = std::mt19937(time(nullptr));
}

void AnsweringCommentsMinigame::start() {
    titleFadeoutTimer = 0.0f;
    nextCommentTimer = nextCommentDistrib(engine);
}

bool AnsweringCommentsMinigame::tick(olc::PixelGameEngine *pge, std::int64_t &internetPoints) {
    titleFadeoutTimer += pge->GetElapsedTime();
    if (nextCommentTimer <= 0) {
	nextCommentTimer = nextCommentDistrib(engine);
	olc::Renderable newPfp;
	newPfp.Create(pfpMaskSprite.Sprite()->width, pfpMaskSprite.Sprite()->height);
	for (size_t y = 0; y < newPfp.Sprite()->height; y++) {
	    for (size_t x = 0; x < newPfp.Sprite()->width; x++) {
		if (pfpMaskSprite.Sprite()->GetPixel(x, y) == olc::WHITE) {
		    newPfp.Sprite()->SetPixel(x, y, olc::Pixel{
			    colorDistrib(engine),
			    colorDistrib(engine),
			    colorDistrib(engine)
			    });
		} else {
		    newPfp.Sprite()->SetPixel(x, y, olc::BLANK);
		}
	    }
	}
	newPfp.Decal()->Update();
	comments.insert(
		comments.begin(),
		Comment {std::move(newPfp),
		    nameDistrib(engine),
		    textDistrib(engine),
		    false,
		    textDistrib(engine),
		    maxId}
		);
	maxId++;
	if (comments.size() > 6) {
	    const auto &last = comments.back();
	    if (!last.answered) {
		internetPoints -= 50;
	    }
	    if (last.id == selectedId) {
		aPressed = false;
		selectedId = -1;
		selectedProgress = 0;
	    }
	    comments.pop_back();
	}
    } else {
	nextCommentTimer -= pge->GetElapsedTime();
    }
    if (selectedId != -1) {
	if (pge->GetKey(olc::A).bPressed) {
	    aPressed = true;
	}
	else if (pge->GetKey(olc::D).bPressed && aPressed) {
	    aPressed = false;
	    selectedProgress += 0.25;
	    if (selectedProgress >= 1.0f) {
		selectedProgress = 0;
		selectedId = -1;
		internetPoints += 200;
	    }
	}
    } else {
	if (pge->GetMouse(0).bPressed) {
	    float i = 0;
	    for (auto &comment : comments) {
		if (comment.answered) {
		    i += 0.5f;
		} else {
		    const auto mousePos = pge->GetMousePos();
		    if (mousePos.x >= 123 && mousePos.x < 141 &&
			    mousePos.y >= 83 + i * 20 && mousePos.y < 88 + i * 20 &&
			    mousePos.y <= pge->ScreenHeight() - 64) {
			selectedId = comment.id;
			comment.answered = true;
		    }
		}
		i += 1.0f;
	    }
	}
    }
    return true;
}

void AnsweringCommentsMinigame::drawSelf(olc::PixelGameEngine *pge) {
    adAnimTimer += pge->GetElapsedTime();
    if (adAnimTimer >= 0.25f) {
	adAnimCur = adAnimCur == 0 ? 1 : 0;
	adAnimTimer -= 0.25f;
    }
    pge->DrawSprite({64, 0}, bgSprite);
    float i = 0;
    for (const auto &comment : comments) {
	pge->DrawSprite({90, int(70 + i * 20)}, comment.sprite);
	pge->DrawPartialSprite({100, int(70 + i * 20)},
		nameSprites, {0, comment.name * 5}, {50, 5});
	pge->DrawPartialSprite({100, int(76 + i * 20)},
		textSprites, {0, comment.text * 5}, {50, 5});
	pge->DrawSprite({100, int(83 + i * 20)}, interactSprite);
	if (comment.answered) {
	    pge->DrawSprite({100, int(90 + i * 20)}, javidPfpSmallSprite);
	    pge->DrawPartialSprite({105, int(90 + i * 20)},
		nameSprites, {0, 0}, {50, 5});
	    if (comment.id == selectedId) {
		pge->DrawPartialSprite({105, int(95 + i * 20)},
		    textSprites,
		    {0, comment.answerText * 5},
		    {int(50 * selectedProgress), 5});
		pge->DrawSprite(
			{150, int(90 + i * 20)},
			adAnimCur == 0 ? pressASprite : pressDSprite
			);
	    } else {
		pge->DrawPartialSprite({105, int(95 + i * 20)},
		    textSprites,
		    {0, comment.answerText * 5},
		    {50, 5});
	    }
	    i += 0.5f;
	} else if (selectedId == -1) {
	    pge->DrawSprite({100, int(83 + i * 20)}, replySprite);
	}
	i += 1.0f;
    }
    pge->FillRect({64, pge->ScreenHeight() - 64},
	    {pge->ScreenWidth() - 64, 64},
	    olc::BLACK);
    if (titleFadeoutTimer <= 2.0f) {
	pge->DrawStringDecal(
		olc::vf2d{pge->ScreenWidth() / 2.0f + 32, pge->ScreenHeight() / 2.0f - 32} -
		pge->GetTextSize("Answer Comments!") / 2,
		"Answer Comments!",
		olc::RED);
    }
}

AnsweringCommentsMinigame::Comment::Comment(olc::Renderable sprite,
	int name,
	int text,
	bool answered,
	int answerText,
	size_t id)
    : name{name}, text{text}, answered{answered}, answerText{answerText}, id{id}
{
    this->sprite = std::move(sprite);
}
