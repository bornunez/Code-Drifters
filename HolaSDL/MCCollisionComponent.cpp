#include "MCCollisionComponent.h"
#include "PlayState.h"
#include "EnemyManager.h"
#include <iostream>
#include "EnemyGunner.h"
#include "CollisionHandler.h"
#include "MainCharacter.h"


MCCollisionComponent::MCCollisionComponent(GameObject* o) : UpdateComponent (o)
{
}


MCCollisionComponent::~MCCollisionComponent()
{
}

void MCCollisionComponent::checkCollision()
{
	list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();
	for (GameObject* e : enemies) {
		vector<SDL_Rect> enemyHurtboxes = e->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
		vector<SDL_Rect> hitboxes = static_cast<MainCharacter*>(gameObject)->getCurrentAnimation()->getCurrentFrame()->getHitboxes();
		bool hit = false;
		int i = 0;
		while (!hit && i < enemyHurtboxes.size()) {
			int j = 0;
			while (!hit && j < hitboxes.size()) {
				if (CollisionHandler::RectCollide(enemyHurtboxes[i], hitboxes[j])) {//Comprueba la colisión de las hitboxes de las espada con las hurtboxes del enemigo
					e->sendMessage("Damage");
					cout << "Toma hostia ";
					hit = true;
				}
				j++;
			}
			i++;
		}	
	}
}

void MCCollisionComponent::update()
{
	checkCollision();
}
