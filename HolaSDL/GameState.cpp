#pragma once
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
		removeGameObject(o);
	}
	cleanGarbage();
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
	for (GameObject* o : gameObjects) {
		delete o;
	}
}


