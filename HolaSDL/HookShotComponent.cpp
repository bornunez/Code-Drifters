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
#include "Game.h"
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
		stop();
		break;
	case HIT_WALL:
		if (hook->getHookStatus() == HookStatus::MOVE_MC) {//Cuando está moviéndose con el gancho y choca con la pared se detiene
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
			if (!CollisionHandler::RectCollide(hook->getTransform()->body, mc->getTransform()->body)) {//10 margen de error MEJOR HACERLO POR COLISIÓN CON EL PERSONAJE
				contract();
			}
			else {
				Message msg(HOOK_STOP);
				mc->sendMessage(&msg);
				mc->setMCState(MCState::Idle);
			}
		}
		else if (hook->getHookStatus() == HookStatus::MOVE_ENEMY) {
			if (!CollisionHandler::RectCollide(hook->getTransform()->body, mc->getTransform()->body)) {//10 margen de error MEJOR HACERLO POR COLISIÓN CON EL PERSONAJE
				contract();
				moveEnemy();
				mc->setMCState(MCState::HookShot);
				enemyHooked->enemyState = EnemyState::Hooked;
			}
			else {
				Message msg(HOOK_STOP);
				mc->sendMessage(&msg);
				mc->setMCState(MCState::Idle);
				enemyHooked->setMovable(true);
				enemyHooked->enemyState = EnemyState::Idle;
			}
		}
		else if (hook->getHookStatus() == HookStatus::MOVE_MC) {
			SDL_Rect mcAux = mc->getTransform()->body;//Rectángulo auxiliar más grande que el body para la colisión con el gancho
			mcAux.w = mcAux.h = 2*mc->getTransform()->body.w;
			mcAux.x = mc->getCenterPos().getX() - mcAux.w / 2;
			mcAux.y = mc->getCenterPos().getY() - mcAux.h / 2;

			if (!CollisionHandler::RectCollide(hook->getTransform()->body, mcAux)) {//10 margen de error MEJOR HACERLO POR COLISIÓN CON EL PERSONAJE
				moveMC();
				mc->setMCState(MCState::Dash);
			}
			else {
				Message msg(HOOK_STOP);
				mc->sendMessage(&msg);
				mc->setMCState(MCState::Idle);
			}
		}
	}
}

void HookShotComponent::updateHookPos()//Actualiza la posición del gancho
{
	mc->getHook().getTransform()->position.set(mc->getGunPosition());
	hook->getTransform()->body.x = hook->getTransform()->position.getX();
	hook->getTransform()->body.y = hook->getTransform()->position.getY();
}

void HookShotComponent::shoot(Vector2D originPos, Vector2D hookDir)//Define la dirección que va a tomar el gancho
{
	PlayState::getInstance()->addGameObject(hook);
	hook->setActive(true);
	hook->setHookStatus(HookStatus::EXTEND);
	mc->setMCState(MCState::Dash);
	mc->setMovable(false);
	Message msg(HOOK_EXTEND);
	mc->sendMessage(&msg);

	SDL_Point p;
	SDL_Rect r;
	SDL_GetMouseState(&p.x, &p.y);
	Vector2D displayPosition;//Posición del gancho relativa a la cámara
	displayPosition = hook->getDisplayPos();

	float angle = (atan2(p.y - displayPosition.getY(), p.x - displayPosition.getX()));//Angulo entre el cursor y el jugador, en grados

	angle = angle * 180 / M_PI;
	if (angle < 0)
		angle += 360;

	Vector2D auxOrigin = originPos;
	int offsetY = 0;
	int offsetX = 0;
	if (angle > 45 && angle < 135) {//Abajo
		if (angle > 90) {//Abajo a la izquierda
			offsetY += 8;
			offsetX -= 7;
		}
		else {//Abajo a la derecha
			offsetY += 7;
			offsetX -= 1;
		}

	}
	else if (angle >= 135 && angle<225) {//Izquierda
		offsetX += 1;
		offsetY += 6;
	}
	else if (angle >= 225 && angle<315) {//Arriba
		if (angle>270) {//Arriba a la derecha
			offsetY -= 2;
			offsetX -= 4;
		}
		else {
			offsetY -= 2;
			offsetX -= 10;
		}
	}
	else {//Derecha
		offsetY += 4;
		offsetX += 1;
	}
	offsetX *= Game::getGame()->getScale();
	offsetY *= Game::getGame()->getScale();

	auxOrigin.setX(auxOrigin.getX() + offsetX);
	auxOrigin.setY(auxOrigin.getY() + offsetY);
	hook->setOriginPosition(auxOrigin);
	hook->getTransform()->position.set(auxOrigin);
	hook->getTransform()->velocity.set(hookDir);
	hook->setAngle(angle);
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
	//t->body.x = t->position.getX(); t->body.y = t->position.getY();

	updateHookAngle();
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
	Vector2D auxVel;//El punto de origen sigue al gancho
	auxVel.set( hook->getCenterPos() - hook->getOriginPosition());
	auxVel.normalize();
	hook->getTransform()->velocity.set(auxVel);


	hook->setOriginPosition(hook->getOriginPosition() + hook->getTransform()->velocity*hookSpeed*(Time::getInstance()->DeltaTime));

	Transform* mcT = mc->getTransform();

	Transform auxT = *mcT;
	auxT.position.setX(hook->getOriginPosition().getX() - auxT.body.w / 2);
	auxT.position.setY(hook->getOriginPosition().getY() + auxT.body.h / 2);

	Room* currRoom = LevelManager::getInstance()->getCurrentRoom();
	bool collision = false;

	*mcT = auxT;


}

void HookShotComponent::stop()
{
	hook->setHookStatus(HookStatus::STOP);
	hook->setActive(false);
	mc->setMCState(MCState::Idle);
	mc->setMovable(true);
}


void HookShotComponent::updateHookAngle()
{
	//SDL_Point p;
	//SDL_Rect r;
	//SDL_GetMouseState(&p.x, &p.y);
	Vector2D displayPosition;//Posición del personaje relativa a la cámara
	displayPosition = mc->getGunPosition();

	//float angle = (atan2(p.y - displayPosition.getY(), p.x - displayPosition.getX()));//Angulo entre el cursor y el jugador, en grados

	float angle = (atan2(hook->getCenterPos().getY() - displayPosition.getY(), hook->getCenterPos().getX() - displayPosition.getX()));
	angle = angle * 180 / M_PI;
	if (angle < 0)
		angle += 360;

	hook->setAngle(angle);
}


