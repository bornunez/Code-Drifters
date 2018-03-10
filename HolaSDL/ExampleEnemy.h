#pragma once
#include "Enemy.h"

class ExampleEnemy : public Enemy
{
public:
	ExampleEnemy(PlayState* playState, Game* game, MainCharacter* mc, Transform t);
	ExampleEnemy(PlayState* playState, Game* game, MainCharacter* mc, int x, int y, int w, int h);

	~ExampleEnemy();

	void render();

};

