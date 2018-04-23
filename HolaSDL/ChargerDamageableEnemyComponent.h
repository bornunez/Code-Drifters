#pragma once
#include "UpdateComponent.h"

class MainCharacter;
class Enemy;

class ChargerDamageableEnemyComponent : virtual public UpdateComponent
{
public:
	ChargerDamageableEnemyComponent(Enemy* o, GameObject* mc);
	~ChargerDamageableEnemyComponent();
	void receiveMessage(Message* msg);
	void update(){}
	void receiveDamage(std::string attackType, float damage);
private:
	Enemy* enemy;
	MainCharacter* mc;
};

