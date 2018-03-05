#pragma once
#include <string>
#include "tinyxml2.h"
#include "Tileset.h"
class Map;

using namespace tinyxml2;
class LevelParser
{
private:
	void parseTilesets(XMLElement* pTilesetRoot,
		std::vector<Tileset>* pTilesets);
	void parseTileLayer(XMLElement* pTileElement,
		std::vector<Layer*> *pLayers, const std::vector<Tileset>*
		pTilesets);
	int tileSize;
	int width;
	int height;
public:
	LevelParser();
	~LevelParser();
	Map* parseLevel(const char* levelFile);
	
};

