#pragma once
#include "RenderComponent.h"
#include "GameObject.h"
#include "Animation.h"
class RenderBoss2 : public RenderComponent
{
public:
	RenderBoss2(GameObject* o);
	~RenderBoss2();
protected:
	virtual void render();
private:
	GameObject* boss;
};

