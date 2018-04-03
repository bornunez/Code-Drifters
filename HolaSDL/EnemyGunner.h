#pragma once
#include "Enemy.h"
#include<map>
#include "Animation.h"
class GunnerAnimationComponent;
enum GunnerState{IDLE, RUN, SHOOT};
class EnemyGunner : public Enemy
{
public:
	EnemyGunner(MainCharacter* mc);

	~EnemyGunner();
	void loadAnimations();
	GunnerState currentState;
};

