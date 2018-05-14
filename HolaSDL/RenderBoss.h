#pragma once
#include "RenderComponent.h"
#include "GameObject.h"
#include "Animation.h"
class RenderBoss : public RenderComponent
{
public:
	RenderBoss(GameObject* o);
	virtual ~RenderBoss();
protected:
	virtual void render();
private:
	GameObject* boss;
};

