#pragma once
#include <vector>
#include "Layer.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class Map
{
private:
	std::vector<Layer*> layers;
	string filename;

	void parseLevel();
public:
	Map(string filename);
	~Map();

};

