#pragma once
class SDL_Rect;
class Room;

class Minimap
{
private:
	int width,height; //Tama�o de la "Ventana" del minimapa
	int rWidth, rHeight; //Tama�o de las celdas del mapa
	void drawDoors(SDL_Rect rect,Room* room);
public:
	Minimap(int w, int h, int rW, int rH);
	~Minimap();
	void render();
};

