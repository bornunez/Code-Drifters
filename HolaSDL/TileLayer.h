#pragma once
#include "Layer.h"
#include "Tileset.h"

class TileLayer :
	public Layer
{
private:
	int cols;
	int rows;
	int tileSize;
	std::vector<std::vector<int>> tileIDs; //Aqui almacenamos la informacion del mapa
	Tileset* tileSet; //Y aqui el tileset
public:
	TileLayer(Tileset* tileset,int cols, int rows, int tileSize);
	~TileLayer();
	void seTileIDs(vector<vector<int>> tileID) { tileIDs = tileID; }
	virtual void update();
	virtual void render();

};

