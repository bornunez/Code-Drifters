#include "Camera.h"
#include "Game.h"



Camera::Camera(Game* game): GameObject(game)
{
	transform.position.setX(0);
	transform.position.setY(0);
	transform.body.w = game->getWinW();
	transform.body.h = game->getWinH();
}

Camera::~Camera()
{
}

void Camera::update()
{
}

void Camera::render()
{
	int auxX = game->getCharacter()->getCurrentRoomX();
	int auxY = game->getCharacter()->getCurrentRoomY();
	game->getLevel()->getRoom(auxX, auxY)->render();	
	//GUI->render();//Pinta el GUI al final
}

bool Camera::isInsideCamera(Transform* t)
{
	if (t->position.getX() + t->body.w >= transform.position.getX() &&		//Si no se sale por la izquierda
		t->position.getX() - t->body.w / 2 <= transform.position.getX() + transform.body.w && //Si no se sale por la derecha
		t->position.getY() <= transform.position.getY() + transform.body.h &&  //Si no se sale por abajo
		t->position.getY() + t->body.h>= transform.position.getY())//Si no se sale por arriba
	{
		return true;
	}
	else return false;
}

