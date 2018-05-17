#pragma once
//#include "checkML.h"
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
	bool active = true;
public:
	//virtual void receiveMessage(std::string msg) {};
	virtual void receiveMessage(Message* msg) {}
	GameObject* getGameObject() { return gameObject; }
	ComponentType getType() { return type; }
	Component(GameObject* o) : gameObject(o) {};
	bool isActive() { return active; }
	void setActive(bool set) { active = set; }
	virtual ~Component();
};

