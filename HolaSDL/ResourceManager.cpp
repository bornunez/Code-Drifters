#pragma once
#include "ResourceManager.h"
#include "Tileset.h"
#include "tinyxml2.h"

using namespace tinyxml2;


//Ver si declararle un renderer propio o usar el de game
ResourceManager::ResourceManager(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	loadTextures();
	loadTilesets();
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::loadTextures()
{
	for (int i = 0; i < NUM_TEXTURES; i++) {
		const TextureAtributes atributes = TEXTURE_ATRIBUTES[i];
		textures[i] = new Texture(renderer, TEXT_PATH + atributes.filename, atributes.numRows, atributes.numCols);
	}
}

void ResourceManager::loadTilesets()
{
	for (int i = 0; i < NUM_TILESET; i++) {
		string filename = tilesetNames[i];
		XMLDocument doc;
		doc.LoadFile((TILESET_PATH + filename).c_str());
		//Raiz del tileset
		XMLElement* root = doc.FirstChildElement();
		string imageSrc = root->FirstChildElement("image")->Attribute("source");
		Texture* tileTex = new Texture(renderer, TILESET_PATH + imageSrc);
		//Y cargamos el tileset
		tilesets.push_back(new Tileset(tileTex, root));
	}
	currentTileset = tilesets[0];
}
