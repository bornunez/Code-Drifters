#pragma once
#include "Enemy.h"
#include<map>
#include "Animation.h"
class StalkerAnimationComponent;
class EnemyStalker : public Enemy
{
public:
	EnemyStalker(MainCharacter* mc);

	~EnemyStalker();
	void loadAnimations();
};

