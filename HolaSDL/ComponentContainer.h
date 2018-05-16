#pragma once
#include "checkML.h"
#include <list>
#include <vector>
#include <queue>
#include "Component.h"
#include "UpdateComponent.h"
#include "RenderComponent.h"
#include "InputComponent.h"



class ComponentContainer
{
protected:
	int NUMCOMP = ItemC - RenderC;
public:
	ComponentContainer();
	virtual ~ComponentContainer();
	void addComponent(Component* c);

	//Definimos tres: Si tiene una instancia concreta, si tiene una clase de componente, y si tiene una clase de componente sabiendo el tipo de dicha clase

	bool hasComponent(Component* c);
	//Para borrar un componente vamos a definir tres modos de borrarlo:  

	//Primero, si tenemos el puntero al componente a borrar
	void removeComponent(Component* c);
	//Dos tipos: 
	//El primero manda un mensaje a todos los componentes
	//void sendMessage(std::string msg);
	////El segundo manda un mensaje a un grupo de componentes de un tipo
	//void sendMessage(std::string msg, ComponentType type);
	virtual void sendMessage(Message* msg);
	void sendMessage(Message* msg, ComponentType type);

	virtual void update();
	virtual void render();
	virtual void lateRender();
	virtual void handleEvents(SDL_Event& e);
private:
	std::list< Component*>* components;
	std::queue<Component*> garbage;
	void cleanGarbage();
};


//-----------------------------------------------------------------------------------------------------------------