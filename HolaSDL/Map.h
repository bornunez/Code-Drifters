#pragma once
#include <vector>
#include "Layer.h"
#include "tinyxml2.h"
#include "LevelParser.h"

using namespace tinyxml2;

class Map
{
private:
	std::vector<Layer*> layers;
	string filename;
	Tileset* tileset;

	friend class LevelParser;
	void parseLevel();
	Map(string filename);
public:
	~Map();
	void update();
	void render();
	vector<Layer*>* getLayers() { return &layers; }
	Tileset* getTileset() { return tileset; }
};

