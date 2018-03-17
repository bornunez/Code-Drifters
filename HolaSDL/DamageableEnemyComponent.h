#pragma once
#include "UpdateComponent.h"

class Enemy;

class DamageableEnemyComponent : public UpdateComponent
{
public:
	DamageableEnemyComponent(Enemy* o);
	~DamageableEnemyComponent();
	void recieveMessage(std::string msg);
	void update(){}
private:
	Enemy* enemy;
};

