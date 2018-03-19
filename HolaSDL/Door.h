#pragma once
#include "sdl_includes.h"
class Door
{
private:
	bool open_;
	SDL_Rect rect;
	
public:
	Door();
	~Door();
	SDL_Rect getRect() { return rect; }
	bool isOpen() { return open_; }
	void close() { open_ = false; }
	void open() { open_ = true; }
};

