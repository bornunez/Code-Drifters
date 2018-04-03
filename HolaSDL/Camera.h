#pragma once
#include <vector>
#include "sdl_includes.h"
#include <iostream>
#include "GameObject.h"

class PlayState;

class Camera : public GameObject
{
private:

public:

	bool isInsideCamera(Transform* t);
	Camera();
	void load();
	~Camera();
};
