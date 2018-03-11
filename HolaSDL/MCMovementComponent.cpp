#pragma once
#include "MCMovementComponent.h"
#include "GameObject.h"
#include "MainCharacter.h"
#include <iostream>
#include "CollisionHandler.h"
#include "Room.h"
#include "Map.h"
#include "PlayState.h"
#include "DungeonGenerator.h"
using namespace std;


MCMovementComponent::MCMovementComponent(GameObject* o, SDL_Scancode up, SDL_Scancode right, SDL_Scancode down, SDL_Scancode left) :
	UpdateComponent(o), upKey(up), rightKey(right), downKey(down), leftKey(left)
{
	acceleration = 0.05;//Aceleración de la velocidad
	reductionFactor = 0.05;//Aceleración de frenado
	maxVelocity = dynamic_cast<MainCharacter*>(gameObject)->getMaxVelocity();//La velocidad máxima es la del personaje
	velocity.set(0, 0);
	direction.set(0, 1);//Empieza mirando hacia abajo
}


MCMovementComponent::~MCMovementComponent()
{
}
void MCMovementComponent::update()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	SDL_PumpEvents();
	//continuous-response keys
//#############################################################################################################
	debug = keystate[debugKey];
	if (keystate[leftKey])
	{
		direction.setX(-1);
		velocity.setX(velocity.getX() + acceleration);
		gameObject->sendMessage("WALK_LEFT");
	}
	else if (keystate[rightKey])
	{
		direction.setX(1);
		velocity.setX(velocity.getX() + acceleration);
		gameObject->sendMessage("WALK_RIGHT");
	}
	else {//Si no se mueve en horizontal entonces frena
		velocity.setX(velocity.getX()*reductionFactor);
	}
	if (keystate[upKey])
	{
		direction.setY(-1);
		velocity.setY(velocity.getY() + acceleration);
	}
	else if (keystate[downKey])
	{
		direction.setY(1);
		velocity.setY(velocity.getY() + acceleration);
	}
	else {//Si no se mueve en vertical frena
		velocity.setY(velocity.getY()*reductionFactor);
	}
	if (velocity.getX() > maxVelocity) {//Nunca se puede superar la velocidad máxima
		velocity.setX(maxVelocity);
	}
	if (velocity.getY() > maxVelocity) {
		velocity.setY(maxVelocity);
	}

//#############################################################################################################

	Transform* t = gameObject->getTransform();

	Transform auxT = *t;

	direction.normalize();
	auxT.direction = direction;//Asigna la dirección	
	auxT.velocity.setX(velocity.getX()*direction.getX());//Asigna la velocidad al personaje
	auxT.velocity.setY(velocity.getY()*direction.getY());
	auxT.position.set(t->position + auxT.velocity);
	auxT.body.x = auxT.position.getX(); auxT.body.y = auxT.position.getY();

	//Colisionamos
	MainCharacter* mc = dynamic_cast<MainCharacter*>(gameObject);
	int currRoomX = mc->getCurrentRoomX(); int currRoomY = mc->getCurrentRoomY();
	Room* currRoom = mc->getPlayState()->getLevel()->getRoom(currRoomX, currRoomY);
	TileLayer* tl = dynamic_cast<TileLayer*>(currRoom->getMap()->GetLayer("Paredes"));
	if (tl != nullptr) {
		if (CollisionHandler::Collide(&auxT, tl)) {
			t->direction.set(0, 0); t->velocity.set(0, 0);
			return;
		}
	}
	*t = auxT;


	

	//Cambia la posición de donde sala la bala, es temporal hasta que tengamos los frames de la animación definidos
	Vector2D gunPosition;
	gunPosition.setX(getGameObject()->getTransform()->position.getX() + getGameObject()->getTransform()->body.w / 2);
	gunPosition.setY(getGameObject()->getTransform()->position.getY() + getGameObject()->getTransform()->body.h / 2);
	dynamic_cast<MainCharacter*>(gameObject)->setGunPosition(gunPosition);
	
	if (debug) {
		system("cls");
		cout << "Player info: \nPosition: [ X: " << t->position.getX() << " ,Y: " << t->position.getY() << " ]" << endl;
		cout << "Velocity: [ X: " << t->velocity.getX() << " ,Y: " << t->velocity.getY() << " ]" << endl;
		cout << "Direction: [ X: " << t->direction.getX() << " ,Y: " << t->direction.getY() << " ]" << endl;
		cout << "Body: [ X: " << t->body.x << " ,Y: " << t->body.y << " ,W: " << t->body.w << " H: " << t->body.h << " ]" << endl;
	}
}