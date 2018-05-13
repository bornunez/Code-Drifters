#include "RenderBoss3.h"
#include "Boss3.h"


RenderBoss3::RenderBoss3(Boss3* o) : RenderComponent(o)
{
	boss = o;
}

RenderBoss3::~RenderBoss3()
{

}

void RenderBoss3::render()
{
	boss->getCurrentAnimation()->runAnimation();
	boss->renderEnemies();
}
