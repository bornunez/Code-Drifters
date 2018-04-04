#include <math.h>
#include <SDL.h>
#include "DungeonGenerator.h"
#include <iostream>
#include "Game.h"
#include "Map.h"
#include "LevelParser.h"
#include "ResourceManager.h"
#include <ctime>
#include "Random.h"

using namespace std;

int main(int ac, char** av) {
	srand((unsigned)time(NULL));
	cout << Random::fraseAleatoria() << endl;
	Game::getGame()->run();
	//game->run();
	return 0;
}


