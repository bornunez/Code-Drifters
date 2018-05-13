#include "RenderBoss2.h"
#include "Boss2.h"


RenderBoss2::RenderBoss2(Boss2* o) : RenderComponent(o)
{
	boss = o;
}

RenderBoss2::~RenderBoss2()
{

}

void RenderBoss2::render()
{
	boss->getCurrentAnimation()->runAnimation();
	boss->renderEnemies();
}
