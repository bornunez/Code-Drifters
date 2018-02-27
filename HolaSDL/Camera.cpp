#include "Camera.h"




Camera::Camera(Game* game): GameObject(game)
{
}

Camera::~Camera()
{
}

void Camera::update()
{
}

void Camera::render()
{
	
	//getCurrentRoom(currentRoomX_, currentRoomY_)->render();//Pinta la sala
	//GUI->render();//Pinta el GUI al final
}

bool Camera::isInsideCamera(Transform* t)
{
	if (t->position.getX() + t->body.w / 2 >= transform.position.getX() - transform.body.w / 2 &&		//Si no se sale por la izquierda
			t->position.getX() - t->body.w / 2 <= transform.position.getX() + transform.body.w / 2 && //Si no se sale por la derecha
				t->position.getY() - t->body.h / 2 <= transform.position.getY() + transform.body.h / 2 &&  //Si no se sale por abajo
					t->position.getY() + t->body.h / 2 >= transform.position.getY() - transform.body.h / 2)//Si no se sale por arriba
	{
		return true;
	}
	else return false;
}

