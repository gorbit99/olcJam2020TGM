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
    bgSprite = std::make_unique<olc::Renderable>();
    pfpMaskSprite = std::make_unique<olc::Renderable>();
    nameSprites = std::make_unique<olc::Renderable>();
    interactSprite = std::make_unique<olc::Renderable>();
    replySprite = std::make_unique<olc::Renderable>();
    textSprites = std::make_unique<olc::Renderable>();
    javidPfpSmallSprite = std::make_unique<olc::Renderable>();
    pressASprite = std::make_unique<olc::Renderable>();
    pressDSprite = std::make_unique<olc::Renderable>();
    bgSprite->Load(bgPath);
    pfpMaskSprite->Load(pfpMaskPath);
    nameSprites->Load(namesPath);
    interactSprite->Load(interactPath);
    replySprite->Load(replyPath);
    textSprites->Load(textsPath);
    javidPfpSmallSprite->Load(javidPfpSmallPath);
    pressASprite->Load(pressAPath);
    pressDSprite->Load(pressDPath);
    engine = std::mt19937(time(nullptr));
}

void AnsweringCommentsMinigame::start() {
    nextCommentTimer = nextCommentDistrib(engine);
}

bool AnsweringCommentsMinigame::tick(olc::PixelGameEngine *pge) {
    if (nextCommentTimer <= 0) {
	nextCommentTimer = nextCommentDistrib(engine);
	std::unique_ptr<olc::Renderable> newPfp = std::make_unique<olc::Renderable>();
	newPfp->Create(pfpMaskSprite->Sprite()->width, pfpMaskSprite->Sprite()->height);
	for (size_t y = 0; y < newPfp->Sprite()->height; y++) {
	    for (size_t x = 0; x < newPfp->Sprite()->width; x++) {
		if (pfpMaskSprite->Sprite()->GetPixel(x, y) == olc::WHITE) {
		    newPfp->Sprite()->SetPixel(x, y, olc::Pixel{
			    colorDistrib(engine),
			    colorDistrib(engine),
			    colorDistrib(engine)
			    });
		} else {
		    newPfp->Sprite()->SetPixel(x, y, olc::BLANK);
		}
	    }
	}
	newPfp->Decal()->Update();
	comments.insert(
		comments.begin(),
		std::make_tuple(std::move(newPfp),
		    nameDistrib(engine),
		    textDistrib(engine),
		    false,
		    textDistrib(engine),
		    maxId)
		);
	maxId++;
	if (comments.size() > 6) {
	    const auto &last = comments.back();
	    if (!std::get<3>(last)) {
		//TODO take away points
	    }
	    if (std::get<5>(last) == selectedId) {
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
		//TODO give points
	    }
	}
    } else {
	if (pge->GetMouse(0).bPressed) {
	    float i = 0;
	    for (auto &comment : comments) {
		if (std::get<3>(comment)) {
		    i += 0.5f;
		} else {
		    const auto mousePos = pge->GetMousePos();
		    if (mousePos.x >= 123 && mousePos.x < 141 &&
			    mousePos.y >= 83 + i * 20 && mousePos.y < 88 + i * 20 &&
			    mousePos.y <= pge->ScreenHeight() - 64) {
			selectedId = std::get<5>(comment);
			std::get<3>(comment) = true;
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
    pge->DrawDecal({64, 0}, bgSprite->Decal());
    float i = 0;
    for (const auto &comment : comments) {
	pge->DrawDecal({90.0f, 70.0f + i * 20}, std::get<0>(comment)->Decal());
	pge->DrawPartialDecal({100.0f, 70.0f + i * 20},
		nameSprites->Decal(), {0, float(std::get<1>(comment) * 5)}, {50, 5});
	pge->DrawPartialDecal({100.0f, 76.0f + i * 20},
		textSprites->Decal(), {0, float(std::get<2>(comment) * 5)}, {50, 5});
	pge->DrawDecal({100.0f, 83.0f + i * 20}, interactSprite->Decal());
	if (std::get<3>(comment)) {
	    pge->DrawDecal({100.0f, 90.0f + i * 20}, javidPfpSmallSprite->Decal());
	    pge->DrawPartialDecal({105.0f, 90.0f + i * 20},
		nameSprites->Decal(), {0, 0}, {50, 5});
	    if (std::get<5>(comment) == selectedId) {
		pge->DrawPartialDecal({105.0f, 95.0f + i * 20},
		    textSprites->Decal(),
		    {0, float(std::get<4>(comment) * 5)},
		    {50 * selectedProgress, 5});
		pge->DrawDecal(
			{150.0f, 90.0f + i * 20},
			adAnimCur == 0 ? pressASprite->Decal() : pressDSprite->Decal()
			);
	    } else {
		pge->DrawPartialDecal({105.0f, 95.0f + i * 20},
		    textSprites->Decal(),
		    {0, float(std::get<4>(comment) * 5)},
		    {50, 5});
	    }
	    i += 0.5f;
	} else if (selectedId == -1) {
	    pge->DrawDecal({100.0f, 83.0f + i * 20}, replySprite->Decal());
	}
	i += 1.0f;
    }
    pge->FillRectDecal({64, float(pge->ScreenHeight() - 64)},
	    {float(pge->ScreenWidth() - 64), 64},
	    olc::BLACK);
}
