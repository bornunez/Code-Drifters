#pragma once
//#include "checkML.h"
#include "sdl_includes.h"
#include <string>

class Texture;
class Game;
using namespace std;

class MouseIcon {

private:
	Texture * texture;
	Game* game;
	int mouseX, mouseY;

	

public:
	MouseIcon(string iconFileName);
	virtual ~MouseIcon();
	//Dibuja el icono del mouse teniendo en cuenta la x y la y que recibe por el evento de movimiento
	void drawIcon(SDL_Event & e);
};