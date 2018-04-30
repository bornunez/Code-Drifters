#pragma once
#include "Enemy.h"
#include<map>
#include "Animation.h"
class GunnerAnimationComponent;
class EnemyBomb : public Enemy
{
public:
	EnemyBomb(MainCharacter* mc);

	~EnemyBomb();
	void loadAnimations();
};

