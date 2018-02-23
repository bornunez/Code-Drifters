#pragma once
#include <list>
#include <queue>
#include "Component.h"
#include "sdl_includes.h"
class ComponentContainer
{
protected:
	std::list<Component*> components;
public:
	ComponentContainer();
	~ComponentContainer();
	void addComponent(Component* c);
	void removeComponent(Component* c);
	bool hasComponent(Component* c);
	template <class T>
	T* GetComponent();
	void sendMessage(std::string msg);
	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event& e);
private:
	std::queue<Component*> garbage;
	void cleanGarbage();
};

///<summary>Devuelve un puntero al componente de tipo T. Si no tiene se devolver nullptr</summary>
template<class T>
inline T * ComponentContainer::GetComponent()
{
	std::list<Component*>::iterator it = components.begin();
	//If the cast is null, then the component is not the T type
	while (it != components.begin() && dynamic_cast<T>(*it) != nullptr)
		it++;
	return it != components.end() ? *it : nullptr;
}
