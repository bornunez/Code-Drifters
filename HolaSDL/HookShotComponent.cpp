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
#include "BasicMovement.h"
HookShotComponent::HookShotComponent(MainCharacter* mc, Hook* h, float hookSpeed) : UpdateComponent(static_cast<GameObject*>(h))
{
	h->setActive(false);
	hook = h;
	this->hookSpeed = hookSpeed;
	this->mc = mc;
	collisionsLayer.push_back("Paredes");
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
			if (!CollisionHandler::RectCollide(hook->getTransform()->body, mc->getTransform()->body)) {//10 margen de error MEJOR HACERLO POR COLISIÓN CON EL PERSONAJE
				contract();
			}
			else {
				stop();
			}
		}
		else if (hook->getHookStatus() == MOVE_ENEMY) {
			if (!CollisionHandler::RectCollide(hook->getTransform()->body, mc->getTransform()->body)) {//10 margen de error MEJOR HACERLO POR COLISIÓN CON EL PERSONAJE
				contract();
				moveEnemy();
			}
			else {
				stop();
				enemyHooked->setMovable(true);
			}
		}
		else if (hook->getHookStatus() == MOVE_MC) {
			if (!CollisionHandler::RectCollide(hook->getTransform()->body, mc->getTransform()->body)) {//10 margen de error MEJOR HACERLO POR COLISIÓN CON EL PERSONAJE
				moveMC();
			}
			else {
				stop();
			}
		}
	}
}

void HookShotComponent::updateHookPos()
{
	mc->getHook().getTransform()->position.set(mc->getGunPosition());
	hook->getTransform()->body.x = hook->getTransform()->position.getX();
	hook->getTransform()->body.y = hook->getTransform()->position.getY();
}

void HookShotComponent::shoot(Vector2D originPos, Vector2D hookDir)//Define la dirección que va a tomar el gancho
{
	PlayState::getInstance()->addGameObject(hook);
	hook->setActive(true);
	hook->setOriginPosition(originPos);
	hook->getTransform()->position.set(originPos);
	hook->getTransform()->velocity.set(hookDir);
	hook->setHookStatus(EXTEND);
	mc->setMCState(MCState::Hooking);
	mc->setMovable(false);
	
}

void HookShotComponent::extend()//Extiende el gancho en la dirección de disparo
{
	Transform* t = hook->getTransform();
	t->position.set(t->position + t->velocity*hookSpeed*(Time::getInstance()->DeltaTime));
	t->body.x = t->position.getX(); t->body.y = t->position.getY();
}

void HookShotComponent::contract()//Retrae la punta del gancho
{
	mc->setMovable(true);

	Transform* t = hook->getTransform();

	Vector2D auxVel;//El gancho sigue al personaje cuando se contrae
	auxVel.set(t->position - mc->getTransform()->position);
	auxVel.normalize();
	t->velocity.set(auxVel);

	t->position.set(t->position - t->velocity*hookSpeed*(Time::getInstance()->DeltaTime));
	t->body.x = t->position.getX(); t->body.y = t->position.getY();
}

void HookShotComponent::moveEnemy()//Cambia la posición del enemigo según la posición del gancho
{
	Transform* eT = enemyHooked->getTransform();
	eT->position.setX(hook->getCenterPos().getX() - eT->body.w/2);//"Sujeta" el enemy por el centro de su cuerpo
	eT->position.setY(hook->getCenterPos().getY() - eT->body.h/2);
	eT->body.x = eT->position.getX();
	eT->body.y = eT->position.getY();
}

void HookShotComponent::moveMC()//Mueve al personaje en dirección al gancho hasta que llega o choca con una pared
{
	hook->setOriginPosition(hook->getOriginPosition() + hook->getTransform()->velocity*hookSpeed*(Time::getInstance()->DeltaTime));

	Transform* mcT = mc->getTransform();

	Transform auxT = *mcT;
	auxT.position.setX(hook->getOriginPosition().getX() - auxT.body.w / 2);
	auxT.position.setY(hook->getOriginPosition().getY() - auxT.body.h / 2);
	auxT.body.x = auxT.position.getX();
	auxT.body.y = auxT.position.getY();

	Room* currRoom = LevelManager::getInstance()->getCurrentRoom();
	bool collision = false;

	vector<string>::iterator it;
	for (it = collisionsLayer.begin(); it != collisionsLayer.end() && !collision; it++) {
		TileLayer* tl = static_cast<TileLayer*>(currRoom->getMap()->GetLayer(*it));
		if (tl != nullptr) {
			if (CollisionHandler::Collide(&auxT, tl)) {
				collision = true;
			}
		}
	}
	if (!collision) {
		*mcT = auxT;
	}
	else {
		hook->setHookStatus(CONTRACT);
		contract();
	}

}

void HookShotComponent::stop()
{
	hook->setHookStatus(STOP);
	hook->setActive(false);
	mc->setMCState(MCState::Idle);
	mc->setMovable(true);	
}

void HookShotComponent::checkCollision()//Comprueba si el gancho colisiona con un enemigo y si choca contra la pared
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
					e->setMovable(false);
				}
				i++;
			}
		}
	}

	//Colisionamos
	Room* currRoom = LevelManager::getInstance()->getCurrentRoom();
	bool collision = false;
	
	vector<string>::iterator it;
	for (it = collisionsLayer.begin(); it != collisionsLayer.end() && !collision; it++) {
		TileLayer* tl = static_cast<TileLayer*>(currRoom->getMap()->GetLayer(*it));
		if (tl != nullptr) {
			if (CollisionHandler::Collide(hook->getTransform(), tl)) {
				collision = true;
				hook->setHookStatus(MOVE_MC);
			}
		}
	}
}


