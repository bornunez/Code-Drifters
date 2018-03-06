#pragma once
#include "Layer.h"
#include "Tileset.h"

class TileLayer :
	public Layer
{
private:
private:
	int cols;
	int rows;
	int tileSize;
	std::vector<std::vector<int>> tileIDs;
	Tileset* tileSet;
public:
	TileLayer(int tileSize,Tileset* tileset);
	~TileLayer();
	void seTileIDs(vector<vector<int>> tileID) { tileIDs = tileID; }
	virtual void update();
	virtual void render();

};

