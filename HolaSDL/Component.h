#pragma once
#include "sdl_includes.h"
#include <string>

class GameObject;
enum ComponentType{RenderC,InputC,UpdateC,ItemC};

class Component
{
protected: 
	GameObject* gameObject;
	ComponentType type;
public:
	virtual void recieveMessage(std::string msg) = 0;
	GameObject* getGameObject() { return gameObject; }
	ComponentType getType() { return type; }
	Component();
	~Component();
};

