#pragma once
#include "checkML.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Animation.h"
class Boss3;
class RenderBoss3 : public RenderComponent
{
public:
	RenderBoss3(Boss3* o);
	virtual ~RenderBoss3();
protected:
	virtual void render();
private:
	Boss3* boss;
};

