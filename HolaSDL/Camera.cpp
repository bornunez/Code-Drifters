#include "Camera.h"




/*Camera::Camera(Game* game): game_(game)
{
}*/
Camera::Camera()
{
}

Camera::~Camera()
{
}
/*
void Camera::update()
{
}

void Camera::render()
{
	//getCurrentRoom(currentRoomX_, currentRoomY_)->render();//Pinta la sala
	//GUI->render();//Pinta el GUI al final
}
*/
bool Camera::isInsideCamera(Transform* t)
{
	if (t->position.getX() + t->width / 2 >= transform.position.getX() - transform.width / 2 &&		//Si no se sale por la izquierda
			t->position.getX() - t->width / 2 <= transform.position.getX() + transform.width / 2 && //Si no se sale por la derecha
				t->position.getY() - t->height / 2 <= transform.position.getY() + transform.height / 2 &&  //Si no se sale por abajo
					t->position.getY() + t->height / 2 >= transform.position.getY() - transform.height / 2)//Si no se sale por arriba
	{
		return true;
	}
	else return false;
}

