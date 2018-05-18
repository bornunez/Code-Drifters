#pragma once
#include "LevelParser.h"
#include "Map.h"
#include "Base64.h"
#include "miniz.h"
#include "Game.h"
#include "PlayState.h"
#include "ResourceManager.h"
#include "EnemyManager.h"
#include "SimpleAnimationComponent.h"
#include "LevelManager.h"
#include "PressToInteract.h"
#include "SkeletonRenderer.h"
#include "Camera.h"
#include "ShopInput.h"
#include "TextTrigger.h"

void LevelParser::parseTileLayer(XMLElement* root, XMLElement* tileElement, Map* map, vector<Tileset*> tilesets)

{
	//Cargamos los datos del mapa
	int tileSize = atoi(root->Attribute("tilewidth"));
	int width = atoi(root->Attribute("width"));
	int height = atoi(root->Attribute("height"));
	string name = tileElement->Attribute("name");
	TileLayer* tileLayer = new TileLayer(tilesets, name, width, height, tileSize);
	//Vector de los datos de tiles
	vector<vector<int>> data;
	string decodedID;
	//Nodo donde estaguardado el mapa
	XMLElement* dataNode = tileElement->FirstChildElement("data");

	for (XMLNode* e = dataNode->FirstChild(); e != nullptr; e = e->NextSibling())
	{
		XMLText* text = e->ToText();
		std::string t = text->Value();
		//Quitar los espacios ( Lee la linea con espacios incluidos) Esto es un hack
		string nt;
		for (int i = 0; i < t.length(); i++) {
			if (t[i] != '\n' &&t[i] && t[i] != ' ') {
				nt.push_back(t[i]);
			}
		}
		t = nt;
		//Aqui ya esta el texto cortado y listo para decodificar
		///cout << t << endl;
		//Decodificamos el mapa
		macaron::Base64::Decode(t, decodedID);
		///cout << decodedID << endl;
		//Y descomprimimos
		uLongf numGids = width * height * sizeof(int);
		std::vector<unsigned> gids(numGids);
		uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedID.c_str(), decodedID.size());
		std::vector<int> layerRow(width);
		//Ajustamos el tamaño del vector
		for (int j = 0; j < height; j++)
		{
			data.push_back(layerRow);
		}
		//Y asignamos a cada dato de la matriz la informacion del tile
		for (int rows = 0; rows < height; rows++)
		{
			for (int cols = 0; cols < width; cols++)
			{
				data[rows][cols] = gids[rows * width + cols];
			}
		}
		//Finalmente lo asignamos a la layer y la agregamos al vector de layers
		tileLayer->seTileIDs(data);
		tileLayer->setFirstGid(map->getFirstGid());
		map->addLayer(tileLayer);
	}
}

void LevelParser::parseSpawners(XMLElement * root, XMLElement * spawnersElements, Map * map)
{
	//Nodo donde estaguardado el mapa
	for (XMLElement* e = spawnersElements->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		//Leemos los atributos 
		int width = atoi(e->Attribute("width"));
		int height = atoi(e->Attribute("height"));
		int x = atoi(e->Attribute("x"));
		int y = atoi(e->Attribute("y"));
		//Ahora leemos las propiedades 
		vector<string> enemyTypes;
		XMLElement* propElement = e->FirstChildElement("properties");
		//Por cada propiedad, si su valor es true, añadimos el enemigo al vector
		for (XMLElement* p = propElement->FirstChildElement(); p != nullptr; p = p->NextSiblingElement()) {
			if (p->Attribute("value") == string("true"))
				enemyTypes.push_back(p->Attribute("name"));
		}
		//Ahora cogemos un enemigo aleatorio
		if (enemyTypes.size() > 0) {
			int randEnemy = rand() % enemyTypes.size();
			//Lo parseamos
			EnemyType eType = parseEnemyTypes(enemyTypes[randEnemy]);
			Spawner* spawner = new Spawner(x*Game::getGame()->getScale(), y*Game::getGame()->getScale(), eType);
			map->addSpawn(spawner);
		}
	}

}

void LevelParser::parseDoors(XMLElement* root, XMLElement * doorsElement, Map * map, vector<bool> doors)
{
	int scale = Game::getGame()->getScale();
	SDL_Rect trigger;
	for (XMLElement* door = doorsElement->FirstChildElement(); door != nullptr; door = door->NextSiblingElement()) {
		//Casteamos la puerta y sacamos la direccion
		string direction = door->Attribute("name");
		Direction dir = stringToDir(direction);
		//Si la sala tiene puerta, la cargamos
		if (doors[dir]) {
			
			//Si hay puerta sacamos sus datos
			trigger.w = atoi(door->Attribute("width")) * scale;
			trigger.h = atoi(door->Attribute("height"))* scale;
			trigger.x = atoi(door->Attribute("x"))* scale;
			trigger.y = atoi(door->Attribute("y"))* scale;
			map->getDoor(dir)->setTrigger(trigger);
			map->getDoor(dir)->setDirection(dir);
		}
	}
}

void LevelParser::parseEntries(XMLElement* root, XMLElement * entriesElement, Map * map, vector<bool> doors)
{
	int scale = Game::getGame()->getScale();
	Vector2D entry;
	for (XMLElement* door = entriesElement->FirstChildElement(); door != nullptr; door = door->NextSiblingElement()) {
		//Casteamos la puerta y sacamos la direccion
		string direction = door->Attribute("name");
		Direction dir = stringToDir(direction);
		//Si la sala tiene puerta, la cargamos
		if (doors[dir]) {

			//Si hay puerta sacamos sus datos
			entry.setX(atoi(door->Attribute("x"))* scale);
			entry.setY( atoi(door->Attribute("y"))* scale);
			map->getDoor(dir)->setEntry(entry);
		}
	}
}

void LevelParser::parseObjects(XMLElement * root, XMLElement * objectsElement, Map * map)
{
	int scale = Game::getGame()->getScale();
	vector<GameObject*> objects;
	//Si hay puerta sacamos sus datos
	for (XMLElement* object = objectsElement->FirstChildElement(); object != nullptr; object = object->NextSiblingElement()) {
		//Casteamos la puerta y sacamos la direccion
		string objectName = object->Attribute("name");
		int x = atoi(object->Attribute("x"))* scale;
		int y = atoi(object->Attribute("y"))* scale;
		int w = atoi(object->Attribute("width"))* scale;
		int h = atoi(object->Attribute("height"))* scale;
		//Guardamos la posicion
		GameObject* go = stringToObject(objectName,object, x,y,w,h);
		objects.push_back(go);
	}
	map->setObjects(objects);
}

void LevelParser::parseEntryPoint(XMLElement * root, XMLElement * objectsElement, Map * map)
{
	int scale = Game::getGame()->getScale();
	//Si hay puerta sacamos sus datos
	for (XMLElement* object = objectsElement->FirstChildElement();object != nullptr; object = object->NextSiblingElement()) {
		//Casteamos la puerta y sacamos la direccion
		string objectName = object->Attribute("name");
		int x = atoi(object->Attribute("x"))* scale;
		int y = atoi(object->Attribute("y"))* scale;
		//Guardamos la posicion
		if (objectName == "Start") {
			GameObject* go = new GameObject(nullptr, x, y, 0, 0);
			map->setEntryPoint(go);
		}
		else if (objectName == "Boss") {
			GameObject* go = new GameObject(nullptr, x, y, 0, 0);
			map->setBossSpawn(go);
		}
	}
}

vector<Tileset*> LevelParser::parseTileSets(XMLElement * root, Map * map)
{
	vector<Tileset*> tilesets;
	for (XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == string("tileset")) {
			tilesets.push_back(ResourceManager::getInstance()->getTileset(e->Attribute("source")));
			map->setFirstGid(atoi(e->Attribute("firstgid")));
		}
	}
	map->setTilesets(tilesets);
	return tilesets;
}

EnemyType LevelParser::parseEnemyTypes(string enemyType)
{
	EnemyType eType;
	//Iba a hacer un switch, peeeero no se puede de un string, asi que hacer aqui un if/else mazo tocho
	if (enemyType == "Stalker")
		eType = Stalker;
	else if (enemyType == "Gunner")
		eType = Gunner;
	else if (enemyType == "Charger")
		eType = Charger;
	else if (enemyType == "Turret")
		eType = Turret;
	else if (enemyType == "Bomber")
		eType = Bomber;
	return eType;
}

void LevelParser::initDoors(Map* map, vector<bool> doors)
{
	for (int i = 0; i < 4; i++) {
		if (doors[i]) {
			map->addDoor(new Door(), (Direction)i);
		}
	}
}

string LevelParser::dirToString(Direction dir)
{
	string direction;
	switch (dir)
	{
	case Up:
		direction = "Up";
		break;
	case Right:
		direction = "Right";
		break;
	case Down:
		direction = "Down";
		break;
	case Left:
		direction = "Left";
		break;
	default:
		break;
	}
	return direction;
}

GameObject * LevelParser::stringToObject(string objName,XMLElement* e, int x, int y,int w,int h)
{
	GameObject* obj = new GameObject(nullptr, x, y, w, h);

	//Aqui hacer el switch largo para ver cual es
	if (objName == "Turret")
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(GunnerBullet)));
	else if (objName == "Tienda") {
		obj->addComponent(new PressToInteract(obj));
		//obj->addComponent(new SkeletonRendered(obj,PlayState::getInstance()->getCamera()));
		obj->addComponent(new ShopInput(obj));
		}
	else if (objName == "ChicaFumando") {
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(GirlSmoking),0.0,200));
	}
	else if (objName == "BlackLove") {
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(BlackLove), 0.0, 200));
	}
	else if (objName == "SafeSex") {
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(SafeSex), 0.0, 200));
	}
	else if (objName == "MadamP") {
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(Madam_P_Idle), 0.0, 200));
	}
	else if (objName == "Tuto_Text") {
		XMLElement* p = e->FirstChildElement("properties")->FirstChildElement();
		obj->addComponent(new TextTrigger(obj, p->Attribute("value")));
		obj->addComponent(new SkeletonRendered(obj, PlayState::getInstance()->getCamera()));
	}
	else if (objName == "Burbujas1")
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(Burbujas1),0,300));
	else if (objName == "Burbujas2")
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(Burbujas2), 0, 300));
	else if (objName == "Burbujas3")
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(Burbujas3), 0, 300));
	else if (objName == "Burbujas4")
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(Burbujas4), 0, 300));
	else if (objName == "FetoIngeniero2")
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(FetoIngeniero2), 0, 400));
	else if (objName == "FetoIngeniero1")
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(FetoIngeniero1), 0, 400));
	else if (objName == "HologramaHaro")
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(HologramaHaro), 0, 500));
	else if (objName == "HologramaBase")
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(HologramaBase), 0, 500));
	else if (objName == "HologramaWanted")
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(HologramaWanted), 0, 500));
	else if (objName == "Prop1")
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(Prop1), 0, 400));
	else if (objName == "Prop2")
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(Prop2), 0, 400));
	else if (objName == "Prop3")
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(Prop3), 0, 400));
	else if (objName == "Prop4")
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(Prop4), 0, 400));
	else if (objName == "Prop5")
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(Prop5), 0, 400));
	else if (objName == "Prop6")
		obj->addComponent(new SimpleAnimationComponent(obj, ResourceManager::getInstance()->getTexture(Prop6), 0, 400));
	return obj;
}

Direction LevelParser::stringToDir(string direction)
{
	Direction dir;
	if (direction == "Up")
		dir = Up;
	else if (direction == "Right")
		dir = Right;
	else if (direction == "Down")
		dir = Down;
	else if (direction == "Left")
		dir = Left;
	return dir;
}

LevelParser::~LevelParser()
{

}

Map * LevelParser::parseLevel(string levelFile, vector<bool> doors)
{
	Game* game = Game::getGame();
	if (PlayState::getInstance()->getCamera() == nullptr)
		cout << "Haciendo mapa sin camara definida";
	Map* map = new Map(levelFile, PlayState::getInstance()->getCamera());
	//Carga y lectura del mapa
	XMLDocument doc;
	doc.LoadFile(levelFile.c_str());
	//Raiz del mapa
	XMLElement* root = doc.FirstChildElement();
	initDoors(map, doors);
	vector<Tileset*> tilesets = parseTileSets(root, map);
	//Ahora cargamos las tileLayer
	for (XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == string("layer"))
			parseTileLayer(root, e, map, tilesets);
		if (e->Value() == string("objectgroup")) {
			if (e->Attribute("name") == string("Spawners"))
				parseSpawners(root, e, map);
			else if (e->Attribute("name") == string("Puertas"))
				parseDoors(root, e, map, doors);
			else if (e->Attribute("name") == string("Entradas"))
				parseEntries(root, e, map, doors);
			else if (e->Attribute("name") == string("Animados"))
				parseObjects(root, e, map);
			else if (e->Attribute("name") == string("Inicio"))
				parseEntryPoint(root, e, map);
		}
	}
	//XMLElement* mapa = levelDocument.FirstChildElement("map");
	//cout << mapa->Attribute("width");

	return map;
}

