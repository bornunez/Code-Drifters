#pragma once
#include "Texture.h"
#include <string>
#include <vector>
#include "sdl_includes.h"
#include "tinyxml2.h"
using namespace tinyxml2;
class Tileset
{
private:
	Texture * tilesetImg = NULL;
	std::string name;
	int firstGid = 0;
	int tileCount = 0;
	int rows = 0;
	int cols = 0;
	int tileSize = 0;
	int spacing = 0;
	int margin = 0;
	std::vector<SDL_Rect> tileRects;
public:
	Tileset(Texture* tileImg,XMLElement* root);
	~Tileset() {};

	SDL_Rect setTileRect(int tileID);
	SDL_Rect* getTileRect(int tileID);
	Texture* getTexture() { return tilesetImg; }
	void load();
	int getFirstGid() { return firstGid; }
	int getRows() { return rows; }
	int getCols() { return cols; }
	int getTileSize() { return tileSize; }
};

struct Tile {
	int x;
	int y;
	int tileID;
};

