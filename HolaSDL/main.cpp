#include <math.h>
#include <SDL.h>
#include "DungeonGenerator.h"
#include <iostream>
#include "Game.h"
#include "Map.h"

using namespace std;

int main(int ac, char** av) {

	Map map("mapa");

	Game* game = new Game();
	game->run();
	return 0;
}


