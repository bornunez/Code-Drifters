#pragma once
#include "checkML.h"
#include "GameObject.h"
#include "MainCharacter.h"
//
class CollisionsManager : public GameObject
{
private:
	static CollisionsManager* instance;
	CollisionsManager();
	void layerCollisions(GameObject* o);
	void bulletCollisions();
	void playerCollisions();
	void enemyCollisions();
	void hookCollisions();
	void enemyAttackCollision();
	bool overlapCollisions(GameObject* o);
	void bossCollisions();
	void coinCollision();
public:
	virtual ~CollisionsManager();
	static CollisionsManager* getInstance();
	virtual void handleInput(const SDL_Event& event);
	virtual void update();
	virtual void render();
};