#pragma once
#include "UpdateComponent.h"

class MainCharacter;
class Enemy;

class DamageableEnemyComponent : public UpdateComponent
{
public:
	DamageableEnemyComponent(Enemy* o, GameObject* mc);
	~DamageableEnemyComponent();
	void receiveMessage(std::string msg);
	void receiveMessage(Message<Vector2D> msg);
	void update(){}
	void receiveDamage(std::string attackType);
private:
	Enemy* enemy;
	MainCharacter* mc;
};

