#pragma once
#include "RenderComponent.h"
#include "GameObject.h"
#include "Animation.h"
class RenderBoss3 : public RenderComponent
{
public:
	RenderBoss3(GameObject* o);
	~RenderBoss3();
protected:
	virtual void render();
private:
	GameObject* boss;
};

