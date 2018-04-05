#pragma once
#include "ResourceManager.h"
#include "Tileset.h"
#include "tinyxml2.h"
#include "Game.h"

using namespace tinyxml2;


//Ver si declararle un renderer propio o usar el de game
ResourceManager::ResourceManager(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	loadTextures();
	loadProtaTileset();
	loadEnemyTilesets();
}

ResourceManager::~ResourceManager()
{
}

Tileset * ResourceManager::getTileset(string path)
{
	for (size_t i = 0; i < tilesets.size(); i++)
	{
		if (tilesets[i]->getPath() == path)
			return tilesets[i];
	}

	Tileset* aux = loadTileset(path);
	return aux;
}

void ResourceManager::loadTextures()
{
	for (int i = 0; i < NUM_TEXTURES; i++) {
		const TextureAtributes atributes = TEXTURE_ATRIBUTES[i];
		textures[i] = new Texture(renderer, TEXT_PATH + atributes.filename, atributes.numRows, atributes.numCols);
	}
}

Tileset* ResourceManager::loadTileset(string path)
{
		string filename = path;
		XMLDocument doc;
		doc.LoadFile((TILESET_PATH + filename).c_str());
		//Raiz del tileset
		XMLElement* root = doc.FirstChildElement();
		string imageSrc = root->FirstChildElement("image")->Attribute("source");
		Texture* tileTex = new Texture(Game::getGame()->getRenderer(), TILESET_PATH + imageSrc);
		//Y cargamos el tileset
		Tileset* aux = new Tileset(tileTex, root);
		aux->setPath(path);
		tilesets.push_back(aux);
		return aux;
}

void ResourceManager::loadProtaTileset()
{
	string filename = protaTilesetName;
	XMLDocument doc;
	doc.LoadFile((PROTATILESET_PATH + filename).c_str());
	//Raiz del tileset
	XMLElement* root = doc.FirstChildElement();
	string imageSrc = root->FirstChildElement("image")->Attribute("source");
	Texture* tileTex = new Texture(renderer, PROTATILESET_PATH + imageSrc);
	//Y cargamos el tileset
	protaTileset = new Tileset(tileTex, root);
}

void ResourceManager::loadEnemyTilesets()
{
	for (int i = 0; i < NUM_ENEMYTILESET; i++) {
		string filename = enemyTilesetNames[i];
		XMLDocument doc;
		doc.LoadFile((ENEMY_PATH + filename).c_str());
		//Raiz del tileset
		XMLElement* root = doc.FirstChildElement();
		string imageSrc = root->FirstChildElement("image")->Attribute("source");
		Texture* tileTex = new Texture(renderer, ENEMY_PATH + imageSrc);
		//Y cargamos el tileset
		enemyTilesets.push_back(new Tileset(tileTex, root));
	}
}
