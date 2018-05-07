#pragma once
#include "ComponentContainer.h"



ComponentContainer::ComponentContainer()
{
	//Inicializamos el array
	components = new std::list<Component*>[NUMCOMP];
}


ComponentContainer::~ComponentContainer()
{
	cleanGarbage();
	for (int i = 0; i < NUMCOMP; i++) {
		for (Component* c : components[i]) {
			delete c;
		}
	}
	components->clear();
}


void ComponentContainer::addComponent(Component * c)
{
	components[c->getType()].push_back(c);
}

///<summary> Elimina la insancia del componente c !Ojo, hace falta tener puntero a c. Si no se tiene usar los otros metodos remove</summary>
void ComponentContainer::removeComponent(Component * c)
{
	garbage.push(c);
}

///<summary> Indica si el objeto tiene una instancia del componente c
bool ComponentContainer::hasComponent(Component * c)
{

	std::list<Component*>::iterator it = components[c->getType()].begin();
	while (it != components[c->getType()].end() && *it != c)
		it++;
	return it != components[c->getType()].end();
}

/////<summary>Manda un mensaje a todos los componentes del objeto</summary>
//void ComponentContainer::sendMessage(std::string msg)
//{
//	for (int i = 0; i < NUMCOMP;i++) {
//		for (Component* c : components[i]) {
//			c->receiveMessage(msg);
//		}
//	}
//}
//
/////<summary> Manda un mensaje al grupo de componentes de tipo <para> type </para> </summary>
//void ComponentContainer::sendMessage(std::string msg, ComponentType type)
//{
//	for (Component* c : components[type]) {
//		c->receiveMessage(msg);
//	}
//}

void ComponentContainer::sendMessage(Message * msg)
{
	for (int i = 0; i < NUMCOMP; i++) {
		for (Component* c : components[i]) {
			if(c->isActive())
				c->receiveMessage(msg);
		}
	}
}

void ComponentContainer::sendMessage(Message * msg, ComponentType type)
{
	for (Component* c : components[type]) {
		if (c->isActive())
			c->receiveMessage(msg);
	}
}

void ComponentContainer::update()
{
	for (Component* c : components[UpdateC]) {
		if (c->isActive())
			static_cast<UpdateComponent*>(c)->update();
	}
	cleanGarbage();
}

void ComponentContainer::render()
{
	for (Component* c : components[RenderC]) {
		if (c->isActive())
			static_cast<RenderComponent*>(c)->render();
	}
}

void ComponentContainer::lateRender()
{
	for (Component* c : components[RenderC]) {
		if (c->isActive())
			static_cast<RenderComponent*>(c)->lateRender();
	}
}

void ComponentContainer::handleEvents(SDL_Event & e)
{
	for (Component* c : components[InputC])
	{
		if(c->isActive())
			static_cast<InputComponent*>(c)->handleEvents(e);
	}
	cleanGarbage();
}

//Elimina los componentes que estan pendientes de borrar. Diseñado para evitar eliminar componentes en mitad de recorridos
void ComponentContainer::cleanGarbage()
{
	while (!garbage.empty())
	{
		Component* aux = garbage.front();
		garbage.pop();
		components[aux->getType()].remove(aux);
	}
}
