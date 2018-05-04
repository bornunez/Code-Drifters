#include "MasterBoss.h"
#include"BossHUDComponent.h"


MasterBoss::MasterBoss():GameObject()
{
	//Attributes.maxHP = Attributes.life;
	addComponent(new BossHUDComponent(this));
}


MasterBoss::~MasterBoss()
{
}
