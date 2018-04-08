#pragma once
#include "InputComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class BulletManager;

class MCShotComponent : public InputComponent
{
private:
	Vector2D aux;
	Timer* lastReloadTime;
	BulletManager* bulletManager;			//Puntero a BulletManager necesario para enviar mensaje
public:
	MCShotComponent(GameObject * o);
	void handleEvents(SDL_Event & e);
	void receiveMessage(std::string msg) {};
	virtual ~MCShotComponent();

};