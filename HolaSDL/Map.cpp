#include "Map.h"



void Map::parseLevel()
{
	// create a TinyXML document and load the map XML
	/*
	TiXmlDocument levelDocument;
	levelDocument.LoadFile(levelFile);*/
	XMLDocument levelDocument;
	levelDocument.LoadFile(filename.c_str());
}


Map::Map(string filename) : filename(filename)
{
	parseLevel();
}

Map::~Map()
{
}
