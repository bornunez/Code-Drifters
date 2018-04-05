#include "HookShotComponent.h"
#include "GameObject.h"
#include "Hook.h"
#include <iostream>
#include "MainCharacter.h"
#include "Time.h"
#include "LevelManager.h"
#include "TileLayer.h"
#include "Map.h"
#include "Managers.h"
#include "Room.h"
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
		updateHookPos();
		checkCollision();
		Vector2D hookSize = hook->getTransform()->position - hook->getOriginPosition();//Diferencia entre la pos actual del gancho y su origen
		//cout << "ORIGEN: " << hook->getOriginPosition() << endl;
		
		if (hook->getHookStatus() == EXTEND) {
			if (hookSize.magnitude() < hook->getLength()) {
				extend();
			}
			else {
				hook->setHookStatus(CONTRACT);
			}
		}		
		else if (hook->getHookStatus() == CONTRACT) {
			cout << "c" << endl;
			if (hookSize.magnitude() > 10) {//10 margen de error MEJOR HACERLO POR COLISIÓN CON EL PERSONAJE
				contract();
			}
			else {
				stop();
			}
		}
		else if (hook->getHookStatus() == MOVE_ENEMY) {
			cout << "e" << endl;
			if (hookSize.magnitude() > 50) {//10 margen de error MEJOR HACERLO POR COLISIÓN CON EL PERSONAJE
				contract();
				moveEnemy();
			}
			else {
				stop();
			}
		}
		//else if (hook->getHookStatus() == MOVE_MC) {
		//	if (hookSize.magnitude() > 50) {//10 margen de error MEJOR HACERLO POR COLISIÓN CON EL PERSONAJE
		//		moveMC();
		//	}
		//	else {
		//		hook->setHookStatus(STOP);
		//		hook->setActive(false);
		//	}
		//}
	}
}

void HookShotComponent::updateHookPos()
{

	mc->getHook().getTransform()->position.set(mc->getGunPosition());
	hook->getTransform()->body.x = hook->getTransform()->position.getX();
	hook->getTransform()->body.y = hook->getTransform()->position.getY();
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
	mc->setMovable(false);
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
	hook->setOriginPosition(hook->getOriginPosition() + hook->getTransform()->velocity*hookSpeed*(Time::getInstance()->DeltaTime));

	mc->getTransform()->position.set(hook->getOriginPosition());
	mc->getTransform()->body.x = hook->getOriginPosition().getX();
	mc->getTransform()->body.y = hook->getOriginPosition().getY();
}

void HookShotComponent::stop()
{
	hook->setHookStatus(STOP);
	hook->setActive(false);
	mc->setActionState(Idle);
	mc->setMovable(true);
	
}

void HookShotComponent::checkCollision()
{
	list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();
	SDL_Rect hookColl = hook->getTransform()->body;
	for (GameObject* e : enemies) {//Itera la lista de enemigos activos
		if (!e->getInvincibility()) {//Solo puede atacar si son vulnerables
			vector<SDL_Rect> enemyHurtboxes = e->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();			
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

	//Colisionamos
	/*Room* currRoom = LevelManager::getInstance()->getCurrentRoom();
	bool collision = false;
	collisionsLayer.push_back("Paredes");
	vector<string>::iterator it;
	for (it = collisionsLayer.begin(); it != collisionsLayer.end() && !collision; it++) {
		TileLayer* tl = static_cast<TileLayer*>(currRoom->getMap()->GetLayer(*it));
		if (tl != nullptr) {
			if (CollisionHandler::Collide(hook->getTransform(), tl)) {
				collision = true;
				hook->setHookStatus(MOVE_MC);
			}
		}
	}*/
}


