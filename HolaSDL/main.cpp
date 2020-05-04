#include <math.h>
#include <SDL.h>
#include <Windows.h>
#include <WinBase.h>
#include "DungeonGenerator.h"
#include <iostream>
#include "Usabilidad/Tracker.h"
#include "Game.h"
#include "Map.h"
#define INFO_BUFFER_SIZE 32767
typedef unsigned long DWORD;
typedef char TCHAR;
TCHAR  infoBuf[INFO_BUFFER_SIZE];
DWORD  bufCharCount = INFO_BUFFER_SIZE;
#include "LevelParser.h"
#include "ResourceManager.h"
#include <ctime>
#include "Random.h"

using namespace std;

int main(int ac, char** av) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GetComputerName(infoBuf, &bufCharCount);
	Tracker::getInstance()->Init(infoBuf);
	srand((unsigned)time(NULL));
	cout << Random::fraseAleatoria() << endl;
	Game::getGame()->run();
	return 0;
}


