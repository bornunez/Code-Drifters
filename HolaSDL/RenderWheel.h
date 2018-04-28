#pragma once
#include "RenderComponent.h"
#include "GameObject.h"
#include "Animation.h"
class RenderWheel : public RenderComponent
{
public:
	RenderWheel(GameObject* o);
	~RenderWheel();
protected:
	virtual void render();
private:
	GameObject* wheel;
};


