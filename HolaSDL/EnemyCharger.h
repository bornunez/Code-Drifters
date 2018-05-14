#pragma once
#include "Enemy.h"
#include<map>
#include "Animation.h"
class ChargerAnimationComponent;
class EnemyCharger : public Enemy
{
public:
	EnemyCharger(MainCharacter* mc);
	virtual ~EnemyCharger();
	void loadAnimations();
	void spawn(int x, int y, Spawner* spawner = nullptr);

};

