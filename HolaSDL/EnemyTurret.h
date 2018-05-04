#pragma once
#include "Enemy.h"
#include<map>
#include "Animation.h"
class EnemyTurret : public Enemy
{
public:
	EnemyTurret(MainCharacter* mc);

	~EnemyTurret();
	void loadAnimations();
};

