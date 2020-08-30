#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Game.h"

#include "soloud.h"
#include "soloud_wav.h"

int main() {
    Game game;
    if (game.Construct(320, 240, 2, 2)) {
	game.Start();
    }
    return 0;
}
