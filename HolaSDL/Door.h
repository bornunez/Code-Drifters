#pragma once
//#include "checkML.h"
#include "sdl_includes.h"
#include "Vector2D.h"

enum Direction;
class Door
{
private:
	Direction dir;
	SDL_Rect trigger;
	Vector2D entry;
public:
	Door(Direction dir,SDL_Rect trigger, Vector2D entry);
	Door();
	~Door();

	//Sets
	void setDirection(Direction dir) { this->dir = dir;};
	void setTrigger(SDL_Rect trigger) { this->trigger = trigger; };
	void setEntry(Vector2D entry) { this->entry = entry; };

	//Gets
	Direction getDirection() { return dir; }
	SDL_Rect getTrigger() { return trigger; }
	Vector2D getEntry() { return entry; }
};

