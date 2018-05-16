#pragma once
#include "checkML.h"
#include "Enemy.h"

class ExampleEnemy : public Enemy
{
public:
	ExampleEnemy(MainCharacter* mc);

	virtual ~ExampleEnemy();
};

