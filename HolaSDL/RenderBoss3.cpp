#include "RenderBoss3.h"
#include "Boss3.h"


RenderBoss3::RenderBoss3(GameObject* o) : RenderComponent(o)
{
	boss = o;
}

RenderBoss3::~RenderBoss3()
{

}

void RenderBoss3::render()
{
	boss->getCurrentAnimation()->runAnimation();
	static_cast<Boss3*>(boss)->renderEnemies();
}
