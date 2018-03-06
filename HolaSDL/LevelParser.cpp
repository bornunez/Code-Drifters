#pragma once
#include "LevelParser.h"
#include "Map.h"


void LevelParser::parseTilesets(XMLElement * pTilesetRoot, std::vector<Tileset>* pTilesets)
{
}

void LevelParser::parseTileLayer(XMLElement * pTileElement, std::vector<Layer*>* pLayers, const std::vector<Tileset>* pTilesets)
{
}

LevelParser::LevelParser()
{
}


LevelParser::~LevelParser()
{
}

Map * LevelParser::parseLevel(const char * levelFile)
{
	return nullptr;
}

