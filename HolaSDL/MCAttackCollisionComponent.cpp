#include "MCAttackCollisionComponent.h"
#include "PlayState.h"
#include "EnemyManager.h"
#include <iostream>
#include "EnemyGunner.h"
#include "CollisionHandler.h"
#include "MainCharacter.h"


MCAttackCollisionComponent::MCAttackCollisionComponent(GameObject* o) : UpdateComponent (o)
{
}


MCAttackCollisionComponent::~MCAttackCollisionComponent()
{
}

void MCAttackCollisionComponent::checkCollision()
{
	list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();
	for (GameObject* e : enemies) {//Itera la lista de enemigos activos
		if (!e->getInvincibility()) {//Solo puede atacar si son vulnerables
			vector<SDL_Rect> enemyHurtboxes = e->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
			vector<SDL_Rect> hitboxes = static_cast<MainCharacter*>(gameObject)->getCurrentAnimation()->getCurrentFrame()->getHitboxes();
			bool hit = false;
			int i = 0;
			while (!hit && i < enemyHurtboxes.size()) {//Itera sobre las hurtboxes del enemigo
				int j = 0;
				while (!hit && j < hitboxes.size()) {
					if (CollisionHandler::RectCollide(enemyHurtboxes[i], hitboxes[j])) {//Comprueba la colisión de las hitboxes de las espada con las hurtboxes del enemigo
						e->sendMessage("NORMAL_ATTACK");						
						hit = true;
					}
					j++;
				}
				i++;
			}
		}
	}
}

void MCAttackCollisionComponent::update()
{
	checkCollision();
}
