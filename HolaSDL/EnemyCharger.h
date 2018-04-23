#pragma once
#include "Enemy.h"
#include<map>
#include "Animation.h"
class ChargerAnimationComponent;
class EnemyCharger : public Enemy
{
public:
	EnemyCharger(MainCharacter* mc);
	~EnemyCharger();
	void loadAnimations();
};

