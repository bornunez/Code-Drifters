#include "RenderBoss.h"



RenderBoss::RenderBoss(GameObject* o) : RenderComponent(o)
{
	boss = o;
}


RenderBoss::~RenderBoss()
{
}

void RenderBoss::render()
{
	boss->render();
}
