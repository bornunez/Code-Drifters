#pragma once
#include <vector>
#include "sdl_includes.h"

#include "GameObject.h"
#include "Transform.h"

class Camera :	public GameObject
{
private:

public:

	bool isInsideCamera(Transform* t);
	//Camera(Game* game);	
	Camera();
	~Camera();
	virtual void update();
	virtual void render();
};

