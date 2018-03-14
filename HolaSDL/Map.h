#pragma once
#include <vector>
#include "tinyxml2.h"
#include "LevelParser.h"
#include "EnemyManager.h"
class Map;
class Layer;
class Camera;
using namespace tinyxml2;

class Spawner {
	bool active = true;
	int x;
	int y;
	EnemyType enemy;
public:

	Spawner(int x, int y, EnemyType eType, bool active = true);

	//Gets y sts
	bool isActive() const { return active; }
	void setActive(bool active) { this->active = active; }
	int getX() const { return x; }
	int getY() const { return y; }
	EnemyType getEnemy() { return enemy; }

	//Llamar para spawnear un enemigo en la posicion del spawner
	void spawn() {
		EnemyManager::getInstance()->spawn(this);
	}
};

class Map
{
private:
	//Capas de objetos / tiles
	std::vector<Layer*> layers;
	std::vector<Spawner*> spawners;
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
	void addSpawn(Spawner* spawn) { spawners.push_back(spawn); }
	Layer * GetLayer(string LayerID);
	void spawn();
};

