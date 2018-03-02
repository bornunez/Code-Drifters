#pragma once
#include "Texture.h"
#include <string>
#include "sdl_includes.h"
class Tileset
{
private:
	Texture * tilesetImg = NULL;
	std::string srcFile;
	int firstGid = 0;
	int rows = 0;
	int cols = 0;
	int tileSize = 0;
	int spacing = 0;
	int margin = 0;
public:
	Tileset(std::string src);
	~Tileset() {};

	SDL_Rect getTileRect(int tileID);
	Texture* getTexture() { return tilesetImg; }
	void load();
	int getFirstGid() { return firstGid; }
	int getRows() { return rows; }
	int getCols() { return cols; }
	int getTileSize() { return tileSize; }
};

