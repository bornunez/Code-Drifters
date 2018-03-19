#include "Map.h"
#include "Layer.h"
#include "GameManager.h"
#include "PlayState.h"
#include "Managers.h"

void Map::parseLevel()
{

}


Map::Map(string filename, Tileset* ts) : filename(filename), tileset(ts)
{
	camera = GameManager::getInstance()->getCamera();
}

Map::~Map()
{
}

void Map::update()
{
	for (Layer* l : layers)
		l->update();

}

void Map::render()
{
	for (Layer* l : layers)
		l->render(camera);
}

Layer * Map::GetLayer(string LayerID)
{
	for (Layer* l : layers) {
		if (l->getLayerID() == LayerID)
			return l;
	}
}

void Map::spawn()
{
	for (Spawner* s : spawners) {
		s->spawn();
	}
}

Spawner::Spawner(int x, int y, EnemyType eType,bool active) : x(x), y(y), enemy(eType), active(active)
{

}
