#pragma once
#include <vector>
#include "sdl_includes.h"
#include "GameObject.h"
#include <iostream>

class PlayState;

class Camera : public GameObject
{
private:
	PlayState * playState;
public:

	bool isInsideCamera(Transform* t);
	Camera(Game* game, PlayState* playState);

	~Camera();
	virtual void render();
};
