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
	std::vector<std::vector<int>> m_tileIDs;
	Tileset* tileSet;
public:
	TileLayer(int tileSize,Tileset* tileset);
	~TileLayer();

	virtual void update();
	virtual void render();

};

