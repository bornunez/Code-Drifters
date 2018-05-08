#pragma once
#include "Enemy.h"
#include<map>
#include "Animation.h"
class BomberAnimationComponent;
class EnemyBomber : public Enemy
{
public:
	EnemyBomber(MainCharacter* mc);
	~EnemyBomber();
	void loadAnimations();
	void spawn(int x, int y, Spawner* spawner = nullptr);

};

