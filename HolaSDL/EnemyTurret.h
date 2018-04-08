#pragma once
#include "Enemy.h"
#include<map>
#include "Animation.h"
class GunnerAnimationComponent;
enum GunnerStatez{IDLEs, RUNs, SHOOTs};
class EnemyTurret : public Enemy
{
public:
	EnemyTurret(MainCharacter* mc);

	~EnemyTurret();
	void loadAnimations();
	GunnerStatez currentState;
};

