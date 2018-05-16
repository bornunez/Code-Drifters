#pragma once
//#include "checkML.h"
#include "Enemy.h"
#include<map>
#include "Animation.h"
class EnemyTurret : public Enemy
{
public:
	EnemyTurret(MainCharacter* mc);

	virtual ~EnemyTurret();
	void loadAnimations();
};

