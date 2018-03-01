#include "ResourceManager.h"


//Ver si declararle un renderer propio o usar el de game
ResourceManager::ResourceManager(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	loadTextures();
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