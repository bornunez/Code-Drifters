#include "HookCollisionComponent.h"
#include "PlayState.h"
#include "EnemyManager.h"
#include <iostream>
#include "EnemyGunner.h"
#include "CollisionHandler.h"
#include "MainCharacter.h"
#include <vector>
#include "Hook.h"

HookCollisionComponent::HookCollisionComponent(GameObject * o): UpdateComponent(o)
{
}

HookCollisionComponent::~HookCollisionComponent()
{
}

void HookCollisionComponent::checkCollision()
{

	list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();
	for (GameObject* e : enemies) {//Itera la lista de enemigos activos
		if (!e->getInvincibility()) {//Solo puede atacar si son vulnerables
			vector<SDL_Rect> enemyHurtboxes = e->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
			SDL_Rect hook = static_cast<MainCharacter*>(gameObject)->getHook().getTransform()->body;
			bool hit = false;
			uint i = 0;
			while (!hit && i < enemyHurtboxes.size()) {//Itera sobre las hurtboxes del enemigo				
				if (CollisionHandler::RectCollide(enemyHurtboxes[i], hook)) {//Comprueba la colisión del gancho con las hurtbox
					//HookedMessage msg(e);
					//gameObject->sendMessage(&msg);//Le manda mensaje al MainCharacter con el enemigo que va a mover			
				}
				i++;
			}
		}
	}
}

void HookCollisionComponent::update()
{
	checkCollision();
}
