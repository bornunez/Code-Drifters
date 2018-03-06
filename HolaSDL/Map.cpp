#include "Map.h"



void Map::parseLevel()
{

}


Map::Map(string filename) : filename(filename)
{
	
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
