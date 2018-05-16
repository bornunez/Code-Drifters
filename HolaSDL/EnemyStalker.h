#pragma once
#include "checkML.h"
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
	virtual ~EnemyStalker();
	void loadAnimations();
	void spawn(int x, int y, Spawner* spawner = nullptr);
};

