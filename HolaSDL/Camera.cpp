#pragma once
#include "Camera.h"
#include "Game.h"
#include "MainCharacter.h"
#include "DungeonGenerator.h"
#include "Room.h"
#include "CameraMovementComponent.h"
#include "PlayState.h"

Camera::Camera(Game* game, PlayState* playState) : PlayStateObject(playState, game)
{
	transform.position.setX(0);
	transform.position.setY(0);
	transform.body.w = game->getWinW();
	transform.body.h = game->getWinH();

	CameraMovementComponent* cameraMovement = new CameraMovementComponent(this, playState->getMainCharacter());
	this->addComponent(cameraMovement);
}

Camera::~Camera()
{
}


void Camera::render()
{
	int auxX = getPlayState()->getMainCharacter()->getCurrentRoomX();
	int auxY = getPlayState()->getMainCharacter()->getCurrentRoomY();
	getPlayState()->getLevel()->getRoom(auxX, auxY)->render();

	//GUI->render();//Pinta el GUI al final
}

bool Camera::isInsideCamera(Transform* t)
{
	if (t->position.getX() + t->body.w >= transform.position.getX() &&		//Si no se sale por la izquierda
		t->position.getX() - t->body.w / 2 <= transform.position.getX() + transform.body.w && //Si no se sale por la derecha
		t->position.getY() <= transform.position.getY() + transform.body.h &&  //Si no se sale por abajo
		t->position.getY() + t->body.h >= transform.position.getY())//Si no se sale por arriba
	{
		return true;
	}
	else return false;
}

