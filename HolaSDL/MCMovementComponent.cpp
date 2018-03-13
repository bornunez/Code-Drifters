#pragma once
#include "MCMovementComponent.h"
#include "GameObject.h"
#include "MainCharacter.h"
#include <iostream>
#include "CollisionHandler.h"
#include "Room.h"
#include "Map.h"
#include "Timer.h"
#include "PlayState.h"
#include "DungeonGenerator.h"
using namespace std;


MCMovementComponent::MCMovementComponent(GameObject* o) :
	UpdateComponent(o)
{
	maxVelocity = dynamic_cast<MainCharacter*>(gameObject)->getMaxVelocity();//La velocidad máxima es la del personaje
	velocity.set(0, 0);
	direction.set(0, 1);//Empieza mirando hacia abajo
}


MCMovementComponent::~MCMovementComponent()
{
}
void MCMovementComponent::update()
{
	Transform* t = gameObject->getTransform();
	velocity.set(t->velocity);
	direction.set(t->direction);

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
	Room* currRoom = PlayState::getInstance()->getLevel()->getRoom(currRoomX, currRoomY);
	TileLayer* tl = dynamic_cast<TileLayer*>(currRoom->getMap()->GetLayer("Paredes"));
	if (tl != nullptr) {
		if (CollisionHandler::Collide(&auxT, tl)) {
			t->direction.set(0, 0); t->velocity.set(0, 0);
			return;
		}
	}
	*t = auxT;

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	SDL_PumpEvents();
	debug = keystate[debugKey];
	
	if (debug) {
		system("cls");
		cout << "Player info: \nPosition: [ X: " << t->position.getX() << " ,Y: " << t->position.getY() << " ]" << endl;
		cout << "Velocity: [ X: " << t->velocity.getX() << " ,Y: " << t->velocity.getY() << " ]" << endl;
		cout << "Direction: [ X: " << t->direction.getX() << " ,Y: " << t->direction.getY() << " ]" << endl;
		cout << "Body: [ X: " << t->body.x << " ,Y: " << t->body.y << " ,W: " << t->body.w << " H: " << t->body.h << " ]" << endl;

	}
}