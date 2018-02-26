#include <math.h>
#include <iostream>
#include "DungeonGenerator.h"
#include "Game.h"

using namespace std;

int main(int ac, char** av) {
	Game* game = new Game();
	game->run();
	return 0;
}
