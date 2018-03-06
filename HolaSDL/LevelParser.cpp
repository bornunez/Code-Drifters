#pragma once
#include "LevelParser.h"
#include "Map.h"
#include "Base64.h"
#include "miniz.h"


void LevelParser::parseTileset(XMLElement* tilesetRoot,Tileset* tileset)
{
}

void LevelParser::parseTileLayer(XMLElement* tileElement, vector<Layer*>* layers, Tileset* tileset)
{
	TileLayer* tileLayer = new TileLayer(tileSize, tileset);
	//Tile data
	vector<vector<int>> data;
	string decodedID;
	XMLElement* dataNode = tileElement->FirstChildElement("data");
	for (XMLNode* e = dataNode->FirstChild(); e != NULL; e =
		e->NextSibling())
	{
		XMLText* text = e->ToText();
		std::string t = text->Value();
		//Quitar los espacios
		string nt;
		for (int i = 0; i<t.length(); i++) {
			if (t[i] != '\n' &&t[i] && t[i] != ' ') {
				nt.push_back(t[i]);
			}
		}
		t = nt;
		cout << t << endl;
		macaron::Base64::Decode(t,decodedID);
		cout << decodedID << endl;
		// uncompress zlib compression
		uLongf numGids = width * height * sizeof(int);
		std::vector<unsigned> gids(numGids);
		uncompress((Bytef*)&gids[0], &numGids, (const
			Bytef*)decodedID.c_str(), decodedID.size());
		std::vector<int> layerRow(width);
		for (int j = 0; j < height; j++)
		{
			data.push_back(layerRow);
		}
		for (int rows = 0; rows < height; rows++)
		{
			for (int cols = 0; cols < width; cols++)
			{
				data[rows][cols] = gids[rows * width + cols];
			}
		}
		tileLayer->seTileIDs(data);
		layers->push_back(tileLayer);
	}
}

LevelParser::LevelParser()
{
}


LevelParser::~LevelParser()
{
}

Map * LevelParser::parseLevel(string levelFile,Tileset* tileset)
{
	Map* map = new Map(levelFile);
	//Carga y lectura del mapa
	XMLDocument doc;
	doc.LoadFile(levelFile.c_str());
	//Raiz del mapa
	XMLElement* root = doc.FirstChildElement();
	//Cargamos los datos del mapa
	tileSize = atoi( root->Attribute("tilewidth"));
	width = atoi(root->Attribute("width"));
	height = atoi( root->Attribute("height"));
	//Ahora cargamos las tileLayer
	for (XMLElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if(e->Value() == string("layer"))
			parseTileLayer(e, map->getLayers(), tileset);
	}
	//XMLElement* mapa = levelDocument.FirstChildElement("map");
	//cout << mapa->Attribute("width");

	return map;
}

