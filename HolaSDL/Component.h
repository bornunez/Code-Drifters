#pragma once
#include "sdl_includes.h"
#include <string>

class GameObject;

class Component
{
protected: 
	GameObject* gameObject;
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void handleInput(SDL_Event& e) = 0;
	virtual void recieveMessage(std::string msg) = 0;
	GameObject* getGameObject() { return gameObject; }
	Component();
	~Component();
};

