#pragma once
//#include "checkML.h"
#include "Enemy.h"
#include<map>
#include "Animation.h"
class BossBombAnimationComponent;
class EnemyBossBomb : public Enemy
{
public:
	EnemyBossBomb(MainCharacter* mc);

	virtual ~EnemyBossBomb();
	void loadAnimations();

};

