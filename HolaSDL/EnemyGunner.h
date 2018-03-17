#pragma once
#include "Enemy.h"
#include<map>
#include "Animation.h"
class GunnerAnimationComponent;
class EnemyGunner : public Enemy
{
public:
	EnemyGunner(MainCharacter* mc);

	~EnemyGunner();
	void loadAnimations();

private:
	std::map<const char*, Animation*> animations;
	GunnerAnimationComponent* animComp;//Se necesita para poder obtener un puntero a la animación actual

};

