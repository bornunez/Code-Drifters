#include "Room.h"
#include "DungeonGenerator.h"



Room::Room()
{
}
Room::Room(DungeonGenerator* game, SDL_Rect rect) :game_(game), rect_(rect) {
	texture = new Texture();

}
Room::~Room()
{
	delete texture;
}
void Room::loadTexture() {
	rect_.x = x_ * rect_.w;
	rect_.y = y_ * rect_.h;
	if (upDoor_ && downDoor_ && leftDoor_ && rightDoor_)//UDLR
	{
		filename_ = "..\\images\\roomUDLR.png";
	}
	else if (upDoor_ && downDoor_ && leftDoor_)//UDL
	{
		filename_ = "..\\images\\roomUDL.png";
	}
	else if (upDoor_ && downDoor_ && rightDoor_)//UDR
	{
		filename_ = "..\\images\\roomUDR.png";
	}
	else if (upDoor_ && leftDoor_ && rightDoor_)//ULR
	{
		filename_ = "..\\images\\roomULR.png";
	}
	else if (upDoor_ && downDoor_)//UD
	{
		filename_ = "..\\images\\roomUD.png";
	}
	else if (upDoor_ && leftDoor_)//UL
	{
		filename_ = "..\\images\\roomUL.png";

	}
	else if (upDoor_ && rightDoor_)//UR
	{
		filename_ = "..\\images\\roomUR.png";
	}

	else if (downDoor_ && leftDoor_ && rightDoor_)//DLR
	{
		filename_ = "..\\images\\roomDLR.png";
	}
	else if (downDoor_ && leftDoor_)//DL
	{
		filename_ = "..\\images\\roomDL.png";
	}
	else if (downDoor_ && rightDoor_)//DR
	{
		filename_ = "..\\images\\roomDR.png";
	}
	else if (leftDoor_ && rightDoor_)//LR
	{
		filename_ = "..\\images\\roomLR.png";
	}
	else if (upDoor_)//U
	{
		if (special_ == "Boss") {
			filename_ = "..\\images\\roomBossU.png";
		}
		else if (special_ == "Chest") {
			filename_ = "..\\images\\roomChestU.png";
		}
		else if (special_ == "Shop") {
			filename_ = "..\\images\\roomShopU.png";
		}
		else {
			filename_ = "..\\images\\roomU.png";
		}
	}
	else if (downDoor_)//D
	{
		if (special_ == "Boss") {
			filename_ = "..\\images\\roomBossD.png";
		}
		else if (special_ == "Chest") {
			filename_ = "..\\images\\roomChestD.png";
		}
		else if (special_ == "Shop") {
			filename_ = "..\\images\\roomShopD.png";
		}
		else if (special_ == "FirstRoom") {
			filename_ = "..\\images\\firstRoom.png";
		}
		else {
			filename_ = "..\\images\\roomD.png";
		}
	}
	else if (leftDoor_)//L
	{
		if (special_ == "Boss") {
			filename_ = "..\\images\\roomL.png";
		}
		else if (special_ == "Chest") {
			filename_ = "..\\images\\roomChestL.png";
		}
		else if (special_ == "Shop") {
			filename_ = "..\\images\\roomShopL.png";
		}
		else {
			filename_ = "..\\images\\roomL.png";
		}

	}
	else if (rightDoor_)//R
	{
		if (special_ == "Boss") {
			filename_ = "..\\images\\roomBossR.png";
		}
		else if (special_ == "Chest") {
			filename_ = "..\\images\\roomChestR.png";
		}
		else if (special_ == "Shop") {
			filename_ = "..\\images\\roomShopR.png";
		}
		else {
			filename_ = "..\\images\\roomR.png";
		}

	}
	texture->loadFromImg(game_->getRenderer(), filename_);
}
void Room::render() {
	/*

	for (Recorre los tiles de la sala) {//Pinta la sala
		if (...) {//Si está dentro de la sala
			tile->render();
		}
	}
	for (GameObject* o : characters_) {//Pinta los gameObjects
		if (o->getTransform()->position.getX() + o->getTransform()->width / 2 >= cameraX - cameraW / 2) {//Si no se sale por la izquierda
			if (o->getTransform()->position.getX() - o->getTransform()->width/2 <= cameraX + cameraW/2) {//Si no se sale por la derecha
				if (o->getTransform()->position.getY() - o->getTransform()->height / 2 <= cameraY + cameraH / 2) {//Si no se sale por abajo
					if (o->getTransform()->position.getY() + o->getTransform()->height / 2 >= cameraY - cameraH / 2) {//Si no se sale por arriba
						o->render();
					}
				}
			}
		}
	}	
	*/
}
//-----------------------------------------------------------------------------------------------
int Room::getX()
{
	return x_;
}
int Room::getY()
{
	return y_;
}
bool Room::getUpDoor()
{
	return upDoor_;
}
bool Room::getRightDoor()
{
	return rightDoor_;
}
bool Room::getLeftDoor()
{
	return leftDoor_;
}
bool Room::getDownDoor()
{
	return downDoor_;
}
bool Room::getVisited()
{
	return visited_;
}
string Room::getSpecial() {
	return special_;
}
void Room::setX(int x) {
	x_ = x;
}
void Room::setY(int y) {
	y_ = y;
}
void Room::setUpDoor(bool upDoor) {
	upDoor_ = upDoor;
}
void Room::setRightDoor(bool rightDoor) {
	rightDoor_ = rightDoor;
}
void Room::setLeftDoor(bool leftDoor) {
	leftDoor_ = leftDoor;
}
void Room::setDownDoor(bool downDoor) {
	downDoor_ = downDoor;
}
void Room::setVisited(bool visited) {
	visited_ = visited;
}
void Room::setSpecial(string special) {
	special_ = special;
}

//-------------------------------------------------------------------------------------