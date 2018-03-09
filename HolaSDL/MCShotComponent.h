#pragma once
#include "InputComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class MCShotComponent : public InputComponent
{
private:
	Vector2D aux;
	Timer* lastReloadTime;
public:
	MCShotComponent(GameObject* o);
	void handleEvents(SDL_Event & e);
	void recieveMessage(std::string msg) {};
	virtual ~MCShotComponent();

};