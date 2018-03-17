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
private:
	std::map<const char*, Animation*> animations;
	StalkerAnimationComponent* animComp;//Se necesita para poder obtener un puntero a la animación actual

};

