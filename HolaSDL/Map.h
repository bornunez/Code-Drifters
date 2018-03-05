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

	friend class LevelParser;
	Map(string filename);
public:
	~Map();
	void update();
	void render();
};

