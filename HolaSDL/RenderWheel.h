#pragma once
//#include "checkML.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Animation.h"
class RenderWheel : public RenderComponent
{
public:
	RenderWheel(GameObject* o);
	virtual ~RenderWheel();
protected:
	virtual void render();
private:
	GameObject* wheel;
};


