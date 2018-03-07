#pragma once
#include <vector>
#include "tinyxml2.h"
#include "LevelParser.h"
class Map;
class Layer;
class Camera;
using namespace tinyxml2;

class Map
{
private:
	std::vector<Layer*> layers;
	string filename;
	Tileset* tileset;
	Camera* camera;
	void parseLevel();

	Map(string filename,Tileset* ts,Camera* camera);
	friend class LevelParser;
public:
	~Map();
	void update();
	void render();
	vector<Layer*>* getLayers() { return &layers; }
	Tileset* getTileset() { return tileset; }
	void addLayer(Layer* layer) { layers.push_back(layer); }
};

