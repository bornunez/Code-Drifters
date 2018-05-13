#pragma once
#include "RenderComponent.h"
#include "GameObject.h"
#include "Animation.h"
class Boss2;
class RenderBoss2 : public RenderComponent
{
public:
	RenderBoss2(Boss2* o);
	~RenderBoss2();
protected:
	virtual void render();
private:
	Boss2* boss;
};

