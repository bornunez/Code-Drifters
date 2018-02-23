#include "GameObject.h"


GameObject::GameObject()
{
}

GameObject::GameObject(Texture * tex, Transform t, bool active): texture(tex), active(active)
{
	transform = t;
}

GameObject::GameObject(Texture * tex, Vector2D position, bool active): texture(tex), active(active)
{
	transform.position = position; transform.rotation = { 0,0 }; transform.velocity = { 0,0 };
	transform.height = texture->getHeight(); transform.width = texture->getWidth();
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	
}

void GameObject::render()
{
}

void GameObject::handleEvents(SDL_Event & e)
{
}
