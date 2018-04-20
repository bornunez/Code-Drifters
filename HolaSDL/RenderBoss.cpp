#include "RenderBoss.h"



RenderBoss::RenderBoss(GameObject* o) : RenderComponent(o)
{
	boss = o;
	boss->changeCurrentAnimation("DESVANECE");
}


RenderBoss::~RenderBoss()
{
}

void RenderBoss::render()
{
	boss->getCurrentAnimation()->runAnimation();
}
