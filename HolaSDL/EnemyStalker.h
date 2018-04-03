#pragma once
#include "Enemy.h"
#include<map>
#include "Animation.h"
class StalkerAnimationComponent;
enum FacingDirection{LEFT,RIGHT};
class EnemyStalker : public Enemy
{
public:
	EnemyStalker(MainCharacter* mc);
	FacingDirection facing;
	~EnemyStalker();
	void loadAnimations();
};

