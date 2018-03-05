#include <math.h>
#include <SDL.h>
#include "DungeonGenerator.h"
#include <iostream>
#include "Game.h"
#include "Map.h"

using namespace std;

int main(int ac, char** av) {

	Map* mapa = new Map("./mapa.tmx");

	Game* game = new Game();
	game->run();
	return 0;
}


