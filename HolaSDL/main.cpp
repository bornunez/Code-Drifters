#include <math.h>
#include <SDL.h>
#include "DungeonGenerator.h"
#include <iostream>
#include "Game.h"
#include "Map.h"
#include "LevelParser.h"
#include "ResourceManager.h"

using namespace std;

int main(int ac, char** av) {

	

	Game* game = new Game();
	game->run();
	return 0;
}


