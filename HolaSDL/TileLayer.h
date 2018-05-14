#pragma once
#include "Layer.h"
#include "Tileset.h"

class TileLayer : public Layer
{
private:
	int cols;
	int rows;
	int tileSize;
	std::vector<std::vector<int>> tileIDs; //Aqui almacenamos la informacion del mapa
	vector<Tileset*> tileSets; //Y aqui el tileset
	vector<int> firstGids;
public:
	TileLayer(vector<Tileset*> tileSets,string name,int cols, int rows, int tileSize);
	virtual ~TileLayer();
	void seTileIDs(vector<vector<int>> tileID) { tileIDs = tileID; }
	virtual void update();
	virtual void render(Camera* camera);
	std::vector<std::vector<int>> getTileIDs() { return tileIDs; }
	int getTileSize() { return tileSize; }
	int getCols() { return cols; }
	int getRows() { return rows; }
	void setFirstGid(vector<int> gids) { firstGids = gids; }
};

