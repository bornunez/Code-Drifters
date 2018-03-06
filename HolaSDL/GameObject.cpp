#pragma once
#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(Game* game)
{
	this->game = game;
}

GameObject::GameObject(Game* game, Texture * tex, Transform t, bool active): texture(tex), active(active)
{
	this->game = game;
	transform = t;
}

GameObject::GameObject(Game* game, Texture * tex, Vector2D position, float bodyHeight, float bodyWidth, bool active): texture(tex), active(active)
{
	this->game = game;
	transform.position = position; transform.rotation = { 0,0 }; transform.velocity = { 0,0 };
	transform.body.h = bodyHeight; transform.body.w = bodyWidth;
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
