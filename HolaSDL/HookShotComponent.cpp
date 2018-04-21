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
#include "PlayState.h"
#include "Camera.h"
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
	switch (msg->id) {
	case HOOK_ENEMY:
		hook->setHookStatus(HookStatus::MOVE_ENEMY);
		enemyHooked = static_cast<HookEnemyMessage*>(msg)->gameObject;
		break;
	case HOOK_WALL:
		//Cuando el gancho colisiona con la pared, el protagonista se mueve
		hook->setHookStatus(HookStatus::MOVE_MC);
		mc->removeCollisionLayer("Aire");
		hook->setOriginPosition(mc->getCenterPos());
		break;
	case HOOK_STOP:
		mc->addCollisionLayer("Aire");
		break;
	case HIT_WALL:
		if (hook->getHookStatus() == HookStatus::MOVE_MC) {//Cuando est� movi�ndose con el gancho y choca con la pared se detiene
			hook->setHookStatus(HookStatus::STOP);
			stop();
		}
		break;
	}
}
void HookShotComponent::update()
{
	if (hook->isActive()) {
		updateHookPos();
		Vector2D hookSize = hook->getTransform()->position - hook->getOriginPosition();//Diferencia entre la pos actual del gancho y su origen
		//cout << "ORIGEN: " << hook->getOriginPosition() << endl;
		
		if (hook->getHookStatus() == HookStatus::EXTEND) {
			if (hookSize.magnitude() < hook->getLength()) {
				mc->setMCState(MCState::HookShot);
				extend();
				
			}
			else {
				hook->setHookStatus(HookStatus::EMPTY);
				Message msg(HOOK_EMPTY);
				mc->sendMessage(&msg);
			}
		}	
		else if (hook->getHookStatus() == HookStatus::EMPTY) {
			if (!CollisionHandler::RectCollide(hook->getTransform()->body, mc->getTransform()->body)) {//10 margen de error MEJOR HACERLO POR COLISI�N CON EL PERSONAJE
				contract();
			}
			else {
				stop();
				mc->setMCState(MCState::Idle);
			}
		}
		else if (hook->getHookStatus() == HookStatus::MOVE_ENEMY) {
			if (!CollisionHandler::RectCollide(hook->getTransform()->body, mc->getTransform()->body)) {//10 margen de error MEJOR HACERLO POR COLISI�N CON EL PERSONAJE
				contract();
				moveEnemy();
				mc->setMCState(MCState::HookShot);
			}
			else {
				stop();
				mc->setMCState(MCState::Idle);
				enemyHooked->setMovable(true);
			}
		}
		else if (hook->getHookStatus() == HookStatus::MOVE_MC) {
			if (!CollisionHandler::RectCollide(hook->getTransform()->body, mc->getTransform()->body)) {//10 margen de error MEJOR HACERLO POR COLISI�N CON EL PERSONAJE
				moveMC();
				mc->setMCState(MCState::Dash);
			}
			else {
				stop();
			}
		}
	}
}

void HookShotComponent::updateHookPos()//Actualiza la posici�n del gancho
{
	mc->getHook().getTransform()->position.set(mc->getGunPosition());
	hook->getTransform()->body.x = hook->getTransform()->position.getX();
	hook->getTransform()->body.y = hook->getTransform()->position.getY();
}

void HookShotComponent::shoot(Vector2D originPos, Vector2D hookDir)//Define la direcci�n que va a tomar el gancho
{
	PlayState::getInstance()->addGameObject(hook);
	hook->setActive(true);
	hook->setOriginPosition(originPos);
	hook->getTransform()->position.set(originPos);
	hook->getTransform()->velocity.set(hookDir);
	hook->setHookStatus(HookStatus::EXTEND);
	mc->setMCState(MCState::Dash);
	mc->setMovable(false);
	Message msg(HOOK_EXTEND);
	mc->sendMessage(&msg);

	SDL_Point p;
	SDL_Rect r;
	SDL_GetMouseState(&p.x, &p.y);
	Vector2D displayPosition;//Posici�n del gancho relativa a la c�mara
	displayPosition = hook->getDisplayPos();

	float angle = (atan2(p.y - displayPosition.getY(), p.x - displayPosition.getX()));//Angulo entre el cursor y el jugador, en grados

	angle = angle * 180 / M_PI;
	if (angle < 0)
		angle += 360;
	hook->setAngle(angle);
}

void HookShotComponent::extend()//Extiende el gancho en la direcci�n de disparo
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
	//t->body.x = t->position.getX(); t->body.y = t->position.getY();

	updateHookAngle();
}

void HookShotComponent::moveEnemy()//Cambia la posici�n del enemigo seg�n la posici�n del gancho
{
	Transform* eT = enemyHooked->getTransform();
	eT->position.setX(hook->getCenterPos().getX() - eT->body.w/2);//"Sujeta" el enemy por el centro de su cuerpo
	eT->position.setY(hook->getCenterPos().getY() - eT->body.h/2);
	eT->body.x = eT->position.getX();
	eT->body.y = eT->position.getY();
}

void HookShotComponent::moveMC()//Mueve al personaje en direcci�n al gancho hasta que llega o choca con una pared
{
	hook->setOriginPosition(hook->getOriginPosition() + hook->getTransform()->velocity*hookSpeed*(Time::getInstance()->DeltaTime));

	Transform* mcT = mc->getTransform();

	Transform auxT = *mcT;
	auxT.position.setX(hook->getOriginPosition().getX() - auxT.body.w / 2);
	auxT.position.setY(hook->getOriginPosition().getY() - auxT.body.h / 2);

	Room* currRoom = LevelManager::getInstance()->getCurrentRoom();
	bool collision = false;

	*mcT = auxT;


}

void HookShotComponent::stop()
{
	hook->setHookStatus(HookStatus::STOP);
	hook->setActive(false);
	
	Message msg(HOOK_STOP);
	mc->sendMessage(&msg);
}


void HookShotComponent::updateHookAngle()
{
	//SDL_Point p;
	//SDL_Rect r;
	//SDL_GetMouseState(&p.x, &p.y);
	Vector2D displayPosition;//Posici�n del personaje relativa a la c�mara
	displayPosition = mc->getGunPosition();

	//float angle = (atan2(p.y - displayPosition.getY(), p.x - displayPosition.getX()));//Angulo entre el cursor y el jugador, en grados

	float angle = (atan2(hook->getCenterPos().getY() - displayPosition.getY(), hook->getCenterPos().getX() - displayPosition.getX()));
	angle = angle * 180 / M_PI;
	if (angle < 0)
		angle += 360;

	hook->setAngle(angle);
}


