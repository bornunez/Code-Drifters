#pragma once
#include "sdl_includes.h"
#include <string>
#include "Vector2D.h"
class GameObject;
enum ComponentType{RenderC,InputC,UpdateC,ItemC};

template<class T>
class Message {
public:
	Message(std::string msg, T params) : msg(msg), params(params) {}
	std::string msg;
	T params;
};

class Component
{
protected: 
	GameObject* gameObject;
	ComponentType type;
public:
	virtual void receiveMessage(std::string msg) {};
	virtual void receiveMessage(Message<int> msg) {}
	virtual void receiveMessage(Message<Vector2D> msg) {}
	GameObject* getGameObject() { return gameObject; }
	ComponentType getType() { return type; }
	Component(GameObject* o) : gameObject(o) {};
	~Component();
};

