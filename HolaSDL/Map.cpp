#include "Map.h"
#include "Layer.h"


void Map::parseLevel()
{

}


Map::Map(string filename, Camera* camera) : filename(filename),camera(camera)
{
	//Inicializamos el vector para poder acceder a el
	for (int i = 0; i < 4; i++)
		doors.push_back(nullptr);
}

Map::~Map()
{
	for (Layer* obj : layers)
		delete obj;
	layers.clear();

	for (Spawner* obj : spawners)
		delete obj;
	spawners.clear();

	for (Door* obj : doors)
		delete obj;
	doors.clear();

	delete EntryPoint;
	delete BossSpawn;

	for (GameObject* obj : objects)
		delete obj;
	objects.clear();

	//ESTE QUIZA SE BORRA EN OTRO SITIO
	/*for (Tileset* obj : tilesets)
		delete obj;
	tilesets.clear();*/
}

void Map::update()
{
	for (Layer* l : layers)
		l->update();
	for (GameObject* o : objects)
		o->update();
}

void Map::render()
{
	for (Layer* l : layers)
		l->render(camera);
	for (GameObject* o : objects) {
		if(o->isActive())
			o->render();
	}
}

void Map::handleEvents(SDL_Event & e)
{
	for (GameObject* o : objects) {
		if (o->isActive())
			o->handleEvents(e);
	}
}

void Map::lateRender()
{
	for (GameObject* o : objects) {
		if (o->isActive())
			o->lateRender();
	}
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
		if(s->isActive())
			s->spawn();
	}
}

Spawner::Spawner(int x, int y, EnemyType eType,bool active) : x(x), y(y), enemy(eType), active(active)
{

}
