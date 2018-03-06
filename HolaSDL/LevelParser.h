#pragma once
#include <string>
#include "tinyxml2.h"
#include "Tileset.h"
#include "Layer.h"
#include "TileLayer.h"
#include <vector>
class Map;

using namespace tinyxml2;
using namespace std;
class LevelParser
{
private:
	Game * game;
	void parseTileLayer(XMLElement* root,XMLElement* tileElement, Map* map,Tileset* tileset);
public:
	LevelParser(Game* game) : game(game) {}
	~LevelParser();
	Map* parseLevel(string levelFile);

};

