#include "Camera.h"




Camera::Camera()
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
	getCurrentRoom(currentRoomX_, currentRoomY_)->render();//Pinta la sala
	//GUI->render();//Pinta el GUI al final
}
void Camera::setCurrentRoom(int posX, int posY) {
	currentRoomX_ = posX;
	currentRoomY_ = posY;
}
Room * Camera::getCurrentRoom(int posX, int posY)
{
	return Dungeon_[posY][posX];
}
