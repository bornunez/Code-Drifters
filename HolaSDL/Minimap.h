#pragma once
//#include "checkML.h"
#include <vector>
#include "sdl_includes.h"
class SDL_Rect;
class Room;
class Texture;

using namespace std;

class Minimap
{
private:
	int width,height; //Tamaño de la "Ventana" del minimapa
	int rWidth, rHeight; //Tamaño de las celdas del mapa
	int marginWidth, marginHeight;
	float scale, rScale; // Escala de la ventana y de las salas. Idealmente tendria que ser 1, para evitar distorsiones
	
	//Rects de las cosas
	SDL_Rect borderRect, srcBorderRect;

	Texture* border;
	Texture* borderBase;
	Texture* base;
	vector<Texture*> closedDoors;
	vector<Texture*> openDoors;
	vector<Texture*> openNormalOn;
	vector<Texture*> openNormalOff;
	vector<Texture*> onFills;
	vector<Texture*> offFills;

	void drawDoors(SDL_Rect destRect, SDL_Rect srcRect, Room * room);
	void drawFill(SDL_Rect destRect, SDL_Rect srcRect, Room * room, bool on);
public:
	Minimap(float scale, float rScale, int mWidth,int mHeight);
	virtual ~Minimap();
	void render();
};

