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
	void parseTileset(XMLElement* tilesetRoot, Tileset* tileset);
	void parseTileLayer(XMLElement* tileElement, vector<Layer*>* layers,Tileset* tileset);
	int tileSize;
	int width;
	int height;
public:
	LevelParser();
	~LevelParser();
	Map* parseLevel(string levelFile, Tileset* tileset);

};

