#pragma once
//#include "checkML.h"
#include "Enemy.h"
#include<map>
#include "Animation.h"
class BomberAnimationComponent;
class EnemyBomber : public Enemy
{
public:
	EnemyBomber(MainCharacter* mc);
	virtual ~EnemyBomber();
	void loadAnimations();
	void spawn(int x, int y, Spawner* spawner = nullptr);

};

