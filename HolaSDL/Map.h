#pragma once
#include <vector>
#include "tinyxml2.h"
#include "LevelParser.h"
class Map;
class Layer;
using namespace tinyxml2;

class Map
{
private:
	std::vector<Layer*> layers;
	string filename;
	Tileset* tileset;

	friend class LevelParser;
	void parseLevel();
	Map(string filename,Tileset* ts);
public:
	~Map();
	void update();
	void render();
	vector<Layer*>* getLayers() { return &layers; }
	Tileset* getTileset() { return tileset; }
	void addLayer(Layer* layer) { layers.push_back(layer); }
};

