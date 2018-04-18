#include "UpdateBoss.h"



UpdateBoss::UpdateBoss(GameObject* o) : UpdateComponent(o)
{
	boss = o;
}


UpdateBoss::~UpdateBoss()
{
}

void UpdateBoss::update()
{
	boss->update();
}
