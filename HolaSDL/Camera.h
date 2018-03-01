#pragma once
#include <vector>
#include "sdl_includes.h"

#include "GameObject.h"
#include "Transform.h"

class Camera : public GameObject
{
private:

public:

	bool isInsideCamera(Transform* t);
	Camera(Game* game);

	~Camera();
	virtual void render();
};
