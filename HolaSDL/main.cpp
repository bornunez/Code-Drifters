#include <math.h>
#include <SDL.h>
#include "DungeonGenerator.h"
#include <iostream>
#include "Game.h"

using namespace std;

int main(int ac, char** av) {
	Game* game = new Game();
	game->run();
	return 0;
}


