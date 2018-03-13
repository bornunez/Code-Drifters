#pragma once
#include "MCMovementComponent.h"
#include "GameObject.h"
#include "MainCharacter.h"
#include <iostream>
#include "CollisionHandler.h"
#include "Room.h"
#include "Map.h"
#include "Timer.h"
#include "Time.h"
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
	/*
	if (debug) {
		system("cls");
		cout << "Player info: \nPosition: [ X: " << t->position.getX() << " ,Y: " << t->position.getY() << " ]" << endl;
		cout << "Velocity: [ X: " << t->velocity.getX() << " ,Y: " << t->velocity.getY() << " ]" << endl;
		cout << "Direction: [ X: " << t->direction.getX() << " ,Y: " << t->direction.getY() << " ]" << endl;
		cout << "Body: [ X: " << t->body.x << " ,Y: " << t->body.y << " ,W: " << t->body.w << " H: " << t->body.h << " ]" << endl;
		cout << "DeltaTime: [ " << Time::getInstance()->DeltaTime << " ]" << endl;
	}*/
}