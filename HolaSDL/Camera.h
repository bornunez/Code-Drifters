#pragma once
//#include "checkML.h"
#include <vector>
#include "sdl_includes.h"
#include <iostream>
#include "GameObject.h"

class PlayState;

class Camera : public GameObject
{
private:

public:
	Camera();
	virtual ~Camera();
	void load();
	bool isInsideCamera(Transform* t);
};
