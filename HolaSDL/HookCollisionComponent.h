#pragma once
#include "UpdateComponent.h"

class MainCharacter;
class HookCollisionComponent :
	public UpdateComponent
{
public:
	HookCollisionComponent(MainCharacter* o);
	virtual ~HookCollisionComponent();
	void checkCollision();
	void receiveMessage(std::string msg) {};
	void update();
private:
	MainCharacter* mc;
};

