#include <math.h>
#include <SDL.h>
#include "DungeonGenerator.h"
#include <iostream>
#include "Game.h"
#include "Map.h"
#include "LevelParser.h"
#include "ResourceManager.h"
#include <ctime>

using namespace std;

int main(int ac, char** av) {
	srand((unsigned)time(NULL));
	

	Game::getGame()->run();
	//game->run();
	return 0;
}


