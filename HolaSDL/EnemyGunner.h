#pragma once
//#include "checkML.h"
#include "Enemy.h"
#include<map>
#include "Animation.h"
class GunnerAnimationComponent;
class EnemyGunner : public Enemy
{
public:
	EnemyGunner(MainCharacter* mc);

	virtual ~EnemyGunner();
	void loadAnimations();
};

