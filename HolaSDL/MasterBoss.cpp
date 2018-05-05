#include "MasterBoss.h"
#include"BossHUDComponent.h"


MasterBoss::MasterBoss(int type_):GameObject()
{
	type = type_;
	//Attributes.maxHP = Attributes.life;
	addComponent(new BossHUDComponent(this));
}


MasterBoss::~MasterBoss()
{
}
