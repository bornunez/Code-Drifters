#include "MCAttackCollisionComponent.h"
#include "PlayState.h"
#include "EnemyManager.h"
#include <iostream>
#include "EnemyGunner.h"
#include "CollisionHandler.h"
#include "MainCharacter.h"
#include <vector>

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
			uint i = 0;
			while (!hit && i < enemyHurtboxes.size()) {//Itera sobre las hurtboxes del enemigo
				uint j = 0;
				while (!hit && j < hitboxes.size()) {
					if (CollisionHandler::RectCollide(enemyHurtboxes[i], hitboxes[j])) {//Comprueba la colisión de las hitboxes de las espada con las hurtboxes del enemigo
						Vector2D empuje = Vector2D(gameObject->getTransform()->direction.getX(), gameObject->getTransform()->direction.getY());
						empuje.normalize();
						Message<Vector2D> msg1("NORMAL_ATTACK", empuje);
						e->sendMessage(msg1);		
						float damage = static_cast<MainCharacter*>(gameObject)->getAttackDamage("NORMAL_ATTACK");//El valor de ataque del jugador
						Message<float> msg2("NORMAL_ATTACK", damage);
						e->sendMessage(msg2);
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
