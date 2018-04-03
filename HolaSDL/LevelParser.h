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
enum Direction;
using namespace tinyxml2;
using namespace std;
class LevelParser
{
private:
	static void parseTileLayer(XMLElement* root,XMLElement* tileElement, Map* map,Tileset* tileset);
	static void parseSpawners(XMLElement* root, XMLElement* spawnersElements, Map* map);
	static void parseDoors(XMLElement* root, XMLElement* doorsElement, Map* map, vector<bool> doors);
	static void parseEntries(XMLElement* root, XMLElement* entriesElement, Map* map, vector<bool> doors);
	static EnemyType parseEnemyTypes(string enemyType);
	static void initDoors(Map * map, vector<bool> doors);
	static string dirToString(Direction dir);
	static Direction stringToDir(string direction);
public:
	LevelParser()  {}
	~LevelParser();
	static Map * parseLevel(string levelFile, vector<bool> doors);

};

