#pragma once
#include "Enemy.h"
#include<map>
#include "Animation.h"
class ChargerAnimationComponent;
enum FacingDirectionC{LEFTs,RIGHTs};
class EnemyCharger : public Enemy
{
public:
	EnemyCharger(MainCharacter* mc);
	FacingDirectionC facing;
	~EnemyCharger();
	void loadAnimations();
};

