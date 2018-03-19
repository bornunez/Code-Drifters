#pragma once
#include <string>
#include "tinyxml2.h"
#include "Tileset.h"
#include "Layer.h"
#include "TileLayer.h"
#include <vector>
class Map;
class Camera;
enum EnemyType;
using namespace tinyxml2;
using namespace std;
class LevelParser
{
private:
	static void parseTileLayer(XMLElement* root,XMLElement* tileElement, Map* map,Tileset* tileset);
	static void parseSpawners(XMLElement* root, XMLElement* spawnersElements, Map* map);
	static EnemyType parseEnemyTypes(string enemyType);
public:
	LevelParser()  {}
	~LevelParser();
	static Map* parseLevel(string levelFile);

};

