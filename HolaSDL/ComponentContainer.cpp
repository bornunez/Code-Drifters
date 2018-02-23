#include "ComponentContainer.h"



ComponentContainer::ComponentContainer()
{
	components.clear();
}


ComponentContainer::~ComponentContainer()
{
	cleanGarbage();
	for (Component* c : components)
		delete c;
}

void ComponentContainer::addComponent(Component * c)
{
	components.push_back(c);
}

void ComponentContainer::removeComponent(Component * c)
{
	garbage.push(c);
}

bool ComponentContainer::hasComponent(Component * c)
{
	std::list<Component*>::iterator it = components.begin();
	while (it != components.end() && *it != c)
		it++;
	return it != components.end();
}

///<summary>Manda un mensaje a todos los componentes del objeto</summary>
void ComponentContainer::sendMessage(std::string msg)
{
	for (Component* c : components) {
		c->recieveMessage(msg);
	}
}

void ComponentContainer::update()
{
	for (Component* c : components)
		c->update();
	cleanGarbage();
}

void ComponentContainer::render()
{
	for (Component* c : components)
		c->update();
}

void ComponentContainer::handleEvents(SDL_Event & e)
{
	for (Component* c : components)
		c->update();
	cleanGarbage();
}

//Elimina los componentes que estan pendientes de borrar. Diseñado para evitar eliminar componentes en mitad de recorridos
void ComponentContainer::cleanGarbage()
{
	while (!garbage.empty())
	{
		Component* aux = garbage.front();
		garbage.pop();
		components.remove(aux);
	}
}
