#pragma once
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
	~ComponentContainer();
	void addComponent(Component* c);

	//Definimos tres: Si tiene una instancia concreta, si tiene una clase de componente, y si tiene una clase de componente sabiendo el tipo de dicha clase

	bool hasComponent(Component* c);
	template <class T>
	bool hasComponent();
	template <class T>
	bool hasComponent(ComponentType type);

	//Para borrar un componente vamos a definir tres modos de borrarlo:  

	//Primero, si tenemos el puntero al componente a borrar
	void removeComponent(Component* c);
	//Segundo, si sabemos que clase de componente es
	template <class T>
	T* removeComponent();
	//Tercero, si sabemos que clase de componente es y de que tipo es (RenderC, InputC, etc)
	template <class T>
	T* removeComponent(ComponentType type);

	//Get component, definimos dos, uno por si se sabe el tipo del componente y otro en el que no. A ser posible usar el tipo de componente
	template <class T>
	T* GetComponent();
	template <class T>
	T* GetComponent(ComponentType type);

	//Dos tipos: 
	//El primero manda un mensaje a todos los componentes
	void sendMessage(std::string msg);
	//El segundo manda un mensaje a un grupo de componentes de un tipo
	void sendMessage(std::string msg, ComponentType type);

	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event& e);
private:
	std::list< Component*>* components;
	std::queue<Component*> garbage;
	void cleanGarbage();
};


//=================================================================================================================================================================


///<summary> Indica si el objeto tiene el componente T, de tipo type (RenderC, InputC, etc).
///Si es posible usar "hasComponent(ComponentType type)"  
///</summary>
template<class T>
inline bool ComponentContainer::hasComponent()
{
	return GetComponent<T>() != NULL;
}

///<summary> Indica si el objeto tiene el componente T, de tipo type (RenderC, InputC, etc). Usar preferiblemente </summary>
template<class T>
inline bool ComponentContainer::hasComponent(ComponentType type)
{
	return GetComponent<T>(type) != NULL;
}

///<summary> Borra una clase de componente T</summary>
template<class T>
inline T * ComponentContainer::removeComponent()
{
	//Intentamos encontrar el componente, en cuyo caso lo borraremos
	Component* c = GetComponent<T>();
	if (c !=nullptr)
		removeComponent(c);
	else
		std::cout << "No se ha encontrado el componente a borrar";
}

///<summary> Borra una clase de componente T, de tipo type (RenderC, InputC, etc) si la hay</summary>
template<class T>
inline T * ComponentContainer::removeComponent(ComponentType type)
{
	//Intentamos encontrar el componente, en cuyo caso lo borraremos
	Component* c = GetComponent<T>(type);
	if (c != nullptr)
		removeComponent(c);
	else
		std::cout << "No se ha encontrado el componente a borrar";
}

///<summary>Devuelve un puntero al componente de tipo T. Si no tiene se devolvera nullptr</summary>
template<class T>
inline T * ComponentContainer::GetComponent()
{
	bool find = false; int i = 0;
	//Vamos a ver todas las listas del array de componentes
	while(!find && i < NUMCOMP) {

		//Dentro de cada lista, la vamos a recorrer para encontrarlo
		std::list<Component*>::iterator it = components[i].begin();
		//Si el cast devuelve null no es del tipo T
		while (it != components[i].end() && dynamic_cast<T>(*it) != nullptr)
			it++;
		find = it != components[i].end();
		i++;
	}
	//Si lo hemos encontrado lo devolvemos
	return find ? *it : nullptr;
}


///*<summary>Devuelve un puntero al componente de tipo T. Si no tiene se devolvera nullptr. Type es el tipo de componente  </summary>
template<class T>
inline T * ComponentContainer::GetComponent(ComponentType type)
{
	//Sabiendo el tipo, solo recorremos una lista
	std::list<Component*>::iterator it = components[type].begin();
	//Si el cast devuelve null no es del tipo T
	while (it != components[type].end() && dynamic_cast<T>(*it) != nullptr)
		it++;
	return it != components[type].end() ? *it : nullptr;
}

//=================================================================================================================================================================
