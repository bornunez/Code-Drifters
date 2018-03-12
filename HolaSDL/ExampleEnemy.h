#pragma once
#include "Enemy.h"

class ExampleEnemy : public Enemy
{
public:
	ExampleEnemy(PlayState* playState, MainCharacter* mc);

	~ExampleEnemy();

	void render();

};

