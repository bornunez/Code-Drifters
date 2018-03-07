#pragma once
#include <vector>
#include "sdl_includes.h"
#include "PlayStateObject.h"
#include <iostream>

class PlayState;

class Camera : public PlayStateObject
{
private:

public:

	bool isInsideCamera(Transform* t);
	Camera(Game* game, PlayState* playState);
	void load();
	~Camera();
	virtual void render();
};
