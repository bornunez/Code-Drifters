#pragma once
#include "UpdateComponent.h"

class MainCharacter;
class Enemy;

class DamageableEnemyComponent : virtual public UpdateComponent
{
public:
	DamageableEnemyComponent(Enemy* o, GameObject* mc);
	~DamageableEnemyComponent();
	void receiveMessage(Message<float> msg);
	void update(){}
	void receiveDamage(std::string attackType, float damage);
private:
	Enemy* enemy;
	MainCharacter* mc;
};

