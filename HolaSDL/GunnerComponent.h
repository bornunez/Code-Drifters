#pragma once
#include "checkML.h"
#include "UpdateComponent.h"
#include "Vector2D.h"
class MainCharacter;
class GunnerComponent :
	public UpdateComponent
{
public:
	void update();
	void receiveMessage(Message* msg);
	GunnerComponent(Enemy* o, MainCharacter* target, float dist);
	virtual ~GunnerComponent();

private:
	Enemy* eg;
	MainCharacter* targetObject;
	float velocity;
	float distancia;

};