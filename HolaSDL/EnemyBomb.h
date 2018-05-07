#pragma once
#include "Enemy.h"
#include<map>
#include "Animation.h"
class BombAnimationComponent;
class EnemyBomb : public Enemy
{
public:
	EnemyBomb(MainCharacter* mc);

	~EnemyBomb();
	void loadAnimations();
};

