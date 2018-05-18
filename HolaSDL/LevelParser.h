#pragma once
//#include "checkML.h"
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
	static void parseTileLayer(XMLElement * root, XMLElement * tileElement, Map * map, vector<Tileset*> tilesets);
	static void parseSpawners(XMLElement* root, XMLElement* spawnersElements, Map* map);
	static void parseDoors(XMLElement* root, XMLElement* doorsElement, Map* map, vector<bool> doors);
	static void parseEntries(XMLElement* root, XMLElement* entriesElement, Map* map, vector<bool> doors);
	static void parseObjects(XMLElement* root, XMLElement* objectsElement, Map* map);
	static void parseEntryPoint(XMLElement* root, XMLElement* objectsElement, Map* map);
	static vector<Tileset*> parseTileSets(XMLElement* root, Map* map);
	static EnemyType parseEnemyTypes(string enemyType);

	static void initDoors(Map * map, vector<bool> doors);
	static string dirToString(Direction dir);
	static GameObject * stringToObject(string objName, XMLElement* e, int x, int y, int w, int h);
	static Direction stringToDir(string direction);
public:
	LevelParser()  {}
	~LevelParser();
	static Map * parseLevel(string levelFile, vector<bool> doors);

};

