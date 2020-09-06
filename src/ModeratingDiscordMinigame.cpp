#include "ModeratingDiscordMinigame.h"

ModeratingDiscordMinigame::ModeratingDiscordMinigame(std::string bgPath,
	std::string pfpPath,
	std::string textPath,
	std::string namePath,
	std::string reportPath) {
    bgSprite.Load(bgPath);
    pfpSprites.Load(pfpPath);
    textSprites.Load(textPath);
    nameSprites.Load(namePath);
    reportSprite.Load(reportPath);
    engine = std::mt19937(time(nullptr));
}

void ModeratingDiscordMinigame::start() {
    nextTimeCountdown = timeDistrib(engine);
    titleFadeoutTimer = 0.0f;
}

bool ModeratingDiscordMinigame::tick(olc::PixelGameEngine *pge, std::int64_t &internetPoints) {
    titleFadeoutTimer += pge->GetElapsedTime();
    if (nextTimeCountdown <= 0.0f) {
	nextTimeCountdown = timeDistrib(engine);
	if (chatEntries.size() > 20) {
	    auto last = std::move(chatEntries.back());
	    chatEntries.pop_back();
	    if (std::get<0>(last)) {
		internetPoints -= 25;
	    }
	}
	chatEntries.insert(chatEntries.begin(),
		std::make_tuple(
		    badDistrib(engine) == 0,
		    textDistrib(engine),
		    pfpDistrib(engine)
		    ));
    } else {
	nextTimeCountdown -= pge->GetElapsedTime();
    }

    if (pge->GetMouse(0).bPressed) {
	for (size_t i = 0; i < chatEntries.size(); i++) {
	    const auto mousePos = pge->GetMousePos();
	    if (mousePos.x >= pge->ScreenWidth() - 14 && mousePos.x < pge->ScreenWidth() - 3 &&
		    mousePos.y >= pge->ScreenHeight() - 75 - i * 20 &&
		    mousePos.y < pge->ScreenHeight() - 64 - i * 20) {
		const auto reported = std::move(chatEntries[i]);
		chatEntries.erase(chatEntries.begin() + i);
		if (std::get<0>(reported)) {
		    internetPoints += 150;
		} else {
		    internetPoints -= 50;
		}
	    }
	}
    }

    return true;
}

void ModeratingDiscordMinigame::drawSelf(olc::PixelGameEngine *pge) {
    pge->DrawDecal({64, 0},
	    bgSprite);
    for (size_t i = 0; i < chatEntries.size(); i++) {
	pge->DrawPartialDecal(
		{128.0f, float(pge->ScreenHeight() - 79 - i * 20)},
		pfpSprites, {float(11 * std::get<2>(chatEntries[i])), 0}, {11, 11}
		);
	pge->DrawPartialDecal(
		{140.0f, float(pge->ScreenHeight() - 79 - i * 20)},
		nameSprites, {0, float(5 * std::get<2>(chatEntries[i]))}, {165, 5}
		);
	pge->DrawPartialDecal(
		{140.0f, float(pge->ScreenHeight() - 70 - i * 20)},
		textSprites, {0, float(5 * std::get<1>(chatEntries[i]))}, {165, 5},
		{1.0f, 1.0f},
		std::get<0>(chatEntries[i]) ? olc::RED : olc::GREEN
		);
	pge->DrawDecal(
		{float(pge->ScreenWidth() - 14), float(pge->ScreenHeight() - 75 - i * 20)},
		reportSprite
		);
    }
    if (titleFadeoutTimer <= 2.0f) {
	pge->DrawStringDecal(
		olc::vf2d{pge->ScreenWidth() / 2.0f + 32, pge->ScreenHeight() / 2.0f - 32} -
		pge->GetTextSize("Moderate Discord!") / 2,
		"Moderate Discord!",
		olc::RED);
    }
}
