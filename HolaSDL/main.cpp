#include <math.h>
#include <SDL.h>
#include "DungeonGenerator.h"
#include <iostream>
#include "Game.h"
#include "Map.h"
#include "LevelParser.h"

using namespace std;

int main(int ac, char** av) {

	LevelParser lp;
	Tileset* ts = new Tileset("../Mapas/Tileset");
	Map* mapa  = lp.parseLevel("../Mapas/mapa.tmx",nullptr);

	Game* game = new Game();
	game->run();
	return 0;
}


