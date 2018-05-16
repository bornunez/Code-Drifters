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
	//_CrtDumpMemoryLeaks();
//_CrtSetBreakAlloc(4819);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand((unsigned)time(NULL));
	cout << Random::fraseAleatoria() << endl;
	Game::getGame()->run();
	//game->run();
	return 0;
}


