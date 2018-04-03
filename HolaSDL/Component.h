#pragma once
#include "sdl_includes.h"
#include <string>
#include "Vector2D.h"
#include "Message.h"

class GameObject;
enum ComponentType{RenderC,InputC,UpdateC,ItemC};

class Component
{
protected: 
	GameObject* gameObject;
	ComponentType type;
public:
	virtual void receiveMessage(std::string msg) {};
	virtual void receiveMessage(Message* msg) {}
	GameObject* getGameObject() { return gameObject; }
	ComponentType getType() { return type; }
	Component(GameObject* o) : gameObject(o) {};
	~Component();
};

