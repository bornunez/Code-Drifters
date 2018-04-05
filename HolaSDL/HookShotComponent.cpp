#include "HookShotComponent.h"
#include "GameObject.h"
#include "Hook.h"
#include <iostream>
#include "PlayState.h"
#include "MainCharacter.h"
#include "Time.h"
HookShotComponent::HookShotComponent(MainCharacter* mc, Hook* h, float hookSpeed) : UpdateComponent(static_cast<GameObject*>(h))
{
	h->setActive(false);
	hook = h;
	this->hookSpeed = hookSpeed;
	this->mc = mc;
}

HookShotComponent::~HookShotComponent()
{
}
void HookShotComponent::receiveMessage(Message* msg) {
	if (msg->id == ENEMY_HOOKED) {
		//enemyHooked = static_cast<HookedMessage*>(msg)->gameObject;
		moveEnemy();
		hook->setHookStatus(MOVE_ENEMY);
	}
	else if (msg->id == WALL_HOOKED) {
		moveMC();
		hook->setHookStatus(MOVE_MC);
	}
}
void HookShotComponent::update()
{
	if (hook->isActive()) {
		checkCollision();
		Vector2D hookSize = hook->getTransform()->position - hook->getOriginPosition();//Diferencia entre la pos actual del gancho y su origen
		
		if (hook->getHookStatus() == EXTEND) {
			if (hookSize.magnitude() < hook->getLength()) {
				extend();
			}
			else {
				hook->setHookStatus(CONTRACT);
			}
		}		
		else if (hook->getHookStatus() == CONTRACT) {
			if (hookSize.magnitude() > 10) {//10 margen de error MEJOR HACERLO POR COLISIÓN CON EL PERSONAJE
				contract();
			}
			else {
				hook->setHookStatus(STOP);
				hook->setActive(false);
			}
		}
		else if (hook->getHookStatus() == MOVE_ENEMY) {
			if (hookSize.magnitude() > 50) {//10 margen de error MEJOR HACERLO POR COLISIÓN CON EL PERSONAJE
				contract();
				moveEnemy();
			}
			else {
				hook->setHookStatus(STOP);
				hook->setActive(false);
			}
		}
	}
}

void HookShotComponent::shoot(Vector2D originPos, Vector2D hookDir)
{
	PlayState::getInstance()->addGameObject(hook);
	hook->setActive(true);
	hook->setOriginPosition(originPos);
	hook->getTransform()->position.set(originPos);
	hook->getTransform()->velocity.set(hookDir);
	hook->setHookStatus(EXTEND);
	mc->setActionState(Hooking);
}

void HookShotComponent::extend()
{
	Transform* t = hook->getTransform();
	t->position.set(t->position + t->velocity*hookSpeed*(Time::getInstance()->DeltaTime));
	t->body.x = t->position.getX(); t->body.y = t->position.getY();
}

void HookShotComponent::contract()
{
	Transform* t = hook->getTransform();
	t->position.set(t->position - t->velocity*hookSpeed*(Time::getInstance()->DeltaTime));
	t->body.x = t->position.getX(); t->body.y = t->position.getY();
}

void HookShotComponent::moveEnemy()
{
	enemyHooked->getTransform()->position.set(hook->getTransform()->position);
	enemyHooked->getTransform()->body.x = enemyHooked->getTransform()->position.getX();
	enemyHooked->getTransform()->body.y = enemyHooked->getTransform()->position.getY();
}

void HookShotComponent::moveMC()
{
}

void HookShotComponent::stop()
{
}

void HookShotComponent::checkCollision()
{
	list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();
	for (GameObject* e : enemies) {//Itera la lista de enemigos activos
		if (!e->getInvincibility()) {//Solo puede atacar si son vulnerables
			vector<SDL_Rect> enemyHurtboxes = e->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
			SDL_Rect hookColl = gameObject->getTransform()->body;
			bool hit = false;
			uint i = 0;
			while (!hit && i < enemyHurtboxes.size()) {//Itera sobre las hurtboxes del enemigo				
				if (CollisionHandler::RectCollide(enemyHurtboxes[i], hookColl)) {//Comprueba la colisión del gancho con las hurtbox
					
					hook->setHookStatus(MOVE_ENEMY);
					enemyHooked = e;
				}
				i++;
			}
		}
	}
}


