#include "RenderBoss2.h"



RenderBoss2::RenderBoss2(GameObject* o) : RenderComponent(o)
{
	boss = o;
}


RenderBoss2::~RenderBoss2()
{
}

void RenderBoss2::render()
{
	boss->getCurrentAnimation()->runAnimation();
}
