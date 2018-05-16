#pragma once
#include "checkML.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Animation.h"
class Boss2;
class RenderBoss2 : public RenderComponent
{
public:
	RenderBoss2(Boss2* o);
	virtual ~RenderBoss2();
protected:
	virtual void render();
private:
	Boss2* boss;
};

