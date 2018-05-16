#pragma once
#include "checkML.h"
#include "GameState.h"
#include "Game.h"


void GameState::cleanGarbage()
{
	while (!garbage.empty()) 
	{
		GameObject* aux=garbage.front();
		garbage.pop();
		if (aux != nullptr) 
		{
			gameObjects.remove(aux);
			delete aux;
			aux = nullptr;
		}
	}
}


GameState::GameState()
{
	game = Game::getGame();
}

GameState::~GameState()
{
	for(GameObject* o : gameObjects){
		delete o;
		o = nullptr;
	}
}

void GameState::update()
{
	for (GameObject* o : gameObjects) {
		if (o->isActive())
			o->update();
	}
}

void GameState::render()
{
	for (GameObject* o : gameObjects) {
		if (o->isActive())
			o->render();
	}
}

void GameState::lateRender()
{
	for (GameObject* o : gameObjects) {
		if (o->isActive())
			o->lateRender();
	}
}

void GameState::handleEvent(SDL_Event & e)
{
	for (GameObject* o : gameObjects) {
		if(o->isActive())
			o->handleEvents(e);
	}
}

void GameState::addGameObject(GameObject * go)
{
	gameObjects.push_back(go);
}

void GameState::removeGameObject(GameObject * go)
{
	garbage.push(go);
}

void GameState::destroyAllGameObjects()
{
	/*for (GameObject* o : gameObjects) {
		delete o;
	}
	for (list<GameObject*>::const_iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		delete *it;
	}
	gameObjects.clear();*/
}


