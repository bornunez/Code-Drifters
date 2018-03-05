#include "Map.h"



void Map::parseLevel()
{
	
	XMLDocument levelDocument;
	levelDocument.LoadFile( "mapa.tmx");
	cout << levelDocument.FirstChildElement("map")->FirstChildElement("layer")->FirstChildElement("data") << endl;
	XMLElement* map = levelDocument.FirstChildElement("map");
	cout << map->Attribute("width");

}


Map::Map(string filename) : filename(filename)
{
	parseLevel();
}

Map::~Map()
{
}

void Map::update()
{
	for (Layer* l : layers)
		l->update();
}

void Map::render()
{
	for (Layer* l : layers)
		l->render();
}
