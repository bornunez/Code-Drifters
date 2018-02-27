#include "GameObject.h"
#include "Game.h"

GameObject::GameObject()
{
}

GameObject::GameObject(Game* game, Texture * tex, Transform t, bool active): texture(tex), active(active)
{
	transform = t;
}

GameObject::GameObject(Game* game, Texture * tex, Vector2D position, bool active): texture(tex), active(active)
{
	transform.position = position; transform.rotation = { 0,0 }; transform.velocity = { 0,0 };
	transform.height = texture->getHeight(); transform.width = texture->getWidth();
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	ComponentContainer::update();
}

void GameObject::render()
{
	ComponentContainer::render();
}

void GameObject::handleEvents(SDL_Event & e)
{
	ComponentContainer::handleEvents(e);
}
