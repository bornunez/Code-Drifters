#pragma once
#include "GameObject.h"
#include "Game.h"

GameObject::GameObject()
{
	this->game = Game::getGame();
}

GameObject::GameObject(Texture * tex, Transform t, bool active): texture(tex), active(active)
{
	this->game = Game::getGame();
	transform = t;
}

GameObject::GameObject(Texture * tex, Vector2D position, float bodyHeight, float bodyWidth, bool active): texture(tex), active(active)
{
	this->game = Game::getGame();
	transform.position = position; transform.rotation = { 0,0 }; transform.velocity = { 0,0 };
	transform.body.h = bodyHeight; transform.body.w = bodyWidth;
}

GameObject::GameObject(Texture* tex, int x, int y, int bodyWidth, int bodyHeight, bool active) : texture(tex), active(active) {
	this->game = Game::getGame();
	transform.position.setX(x); transform.position.setY(y);
	transform.rotation = { 0,0 }; transform.velocity = { 0,0 };
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
