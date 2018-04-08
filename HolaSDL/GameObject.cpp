#pragma once
#include "GameObject.h"
#include "PlayState.h"
#include "Game.h"
#include "Camera.h"

GameObject::GameObject()
{
	this->game = Game::getGame();
	this->playState = PlayState::getInstance();
}

GameObject::GameObject(Texture * tex, bool active) : texture(tex), active(active)
{
	this->game = Game::getGame();
	this->playState = PlayState::getInstance();
}

GameObject::GameObject(Texture * tex, Transform t, bool active): texture(tex), active(active)
{
	this->game = Game::getGame();
	this->playState = PlayState::getInstance();
	transform = t;
}

GameObject::GameObject(Texture * tex, Vector2D position, float bodyHeight, float bodyWidth, bool active): texture(tex), active(active)
{
	this->game = Game::getGame();
	this->playState = PlayState::getInstance();
	transform.position = position; transform.rotation = { 0,0 }; transform.velocity = { 0,0 };
	transform.body.h = bodyHeight; transform.body.w = bodyWidth;
}

GameObject::GameObject(Texture* tex, int x, int y, int bodyWidth, int bodyHeight, bool active) : texture(tex), active(active) {
	this->game = Game::getGame();
	this->playState = PlayState::getInstance();
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
	updateCenterPosition();
	updateDisplayPosition();
	updateDisplayCenterPosition();
}

void GameObject::render()
{
	ComponentContainer::render();
}

void GameObject::handleEvents(SDL_Event & e)
{
	ComponentContainer::handleEvents(e);
}

void GameObject::updateCenterPosition()
{
	centerPosition.setX(transform.position.getX() + transform.body.w / 2);
	centerPosition.setY(transform.position.getY() + transform.body.h / 2);
}

void GameObject::updateDisplayPosition()
{
	displayPosition.setX(transform.position.getX() - playState->getCamera()->getTransform()->position.getX());
	displayPosition.setY(transform.position.getY() - playState->getCamera()->getTransform()->position.getY());
}

void GameObject::updateDisplayCenterPosition()
{
	displayCenterPosition.setX(displayPosition.getX() + transform.body.w / 2);
	displayCenterPosition.setY(displayPosition.getY() + transform.body.h / 2);
}

Animation * GameObject::getCurrentAnimation()
{
	return currentAnimation;
}

void GameObject::changeCurrentAnimation(const char * animName)
{
	currentAnimation = animations[animName];
}
