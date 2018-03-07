#pragma once
#include "LevelParser.h"
#include "Map.h"
#include "Base64.h"
#include "miniz.h"
#include "Game.h"
#include "PlayState.h"
#include "ResourceManager.h"


void LevelParser::parseTileLayer(XMLElement* root, XMLElement* tileElement, Map* map, Tileset* tileset)

{	
	//Cargamos los datos del mapa
	int tileSize = atoi(root->Attribute("tilewidth"));
	int width = atoi(root->Attribute("width"));
	int height = atoi(root->Attribute("height"));
	string name = tileElement->Attribute("name");
	TileLayer* tileLayer = new TileLayer(tileset,name,width,height,tileSize);
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
		for (int i = 0; i<t.length(); i++) {
			if (t[i] != '\n' &&t[i] && t[i] != ' ') {
				nt.push_back(t[i]);
			}
		}
		t = nt;
		//Aqui ya esta el texto cortado y listo para decodificar
		cout << t << endl;
		//Decodificamos el mapa
		macaron::Base64::Decode(t,decodedID);
		cout << decodedID << endl;
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
		map->addLayer(tileLayer);
	}
}


LevelParser::~LevelParser()
{
}

Map * LevelParser::parseLevel(string levelFile,Game* game,Camera* camera)
{
	Map* map = new Map(levelFile,game->getResourceManager()->getCurrTileset(),camera);
	//Carga y lectura del mapa
	XMLDocument doc;
	doc.LoadFile(levelFile.c_str());
	//Raiz del mapa
	XMLElement* root = doc.FirstChildElement();

	//Ahora cargamos las tileLayer
	for (XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if(e->Value() == string("layer"))
			parseTileLayer(root,e, map,game->getResourceManager()->getCurrTileset());
	}
	//XMLElement* mapa = levelDocument.FirstChildElement("map");
	//cout << mapa->Attribute("width");

	return map;
}

