#pragma once
//#include "checkML.h"
#include <vector>
#include "tinyxml2.h"
#include "LevelParser.h"
#include "EnemyManager.h"
#include "Door.h"
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
	std::vector<Door*> doors;
	string filename;

	GameObject* EntryPoint = nullptr;
	GameObject* BossSpawn = nullptr;
	vector<GameObject*> objects;
	vector<Tileset*> tilesets;
	vector<int> firstGids;

	Camera* camera;
	void parseLevel();

	Map(string filename,Camera* camera);
	friend class LevelParser;
public:
	~Map();
	void update();
	void render();
	void handleEvents(SDL_Event & e);
	void lateRender();
	void sendMessage(Message* msg);

	vector<Layer*>* getLayers() { return &layers; }
	vector<Tileset*> getTilesets() { return tilesets; }
	Layer * GetLayer(string LayerID);
	Door* getDoor(Direction door) { return doors[door]; }
	vector<Door*> getDoors() { return doors; }
	vector<int >getFirstGid(){ return firstGids; }

	void setTilesets(vector<Tileset*> tileSets) { tilesets = tileSets; }
	void setFirstGid(int gid) { firstGids.push_back(gid); }
	void setObjects(vector<GameObject*> go) { objects = go; }

	GameObject* getEntryPoint() { return EntryPoint; };
	void setEntryPoint(GameObject* ePoint) { EntryPoint = ePoint; }

	GameObject* getBossSpawn() { return BossSpawn; };
	void setBossSpawn(GameObject* bossSpawn) { BossSpawn = bossSpawn; }

	void addLayer(Layer* layer) { layers.push_back(layer); }
	void addSpawn(Spawner* spawn) { spawners.push_back(spawn); }
	void addDoor(Door* door, Direction dir) { doors[dir] = door; }
	void spawn();
};

