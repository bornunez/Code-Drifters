#pragma once
#include "Room.h"
#include "Camera.h"
#include "PlayState.h"
#include "Game.h"
#include "GameObject.h"
#include "Texture.h"
#include "Map.h"
#include "LevelParser.h"
#include "ResourceManager.h"
#include "LevelManager.h"
#include <ctime>
#include <fstream>


Room::Room() {
	voidRoom = true;
	explored = false;
	for (int i = 0; i < 4; i++)
		doors.push_back(false);
}

Room::~Room()
{
}
void Room::load() {
//	//if (upDoor && downDoor && leftDoor && rightDoor)//UDLR
//	//{
//	//	filename = "..\\images\\roomUDLR.png";
//	//}
//	//else if (upDoor && downDoor && leftDoor)//UDL
//	//{
//	//	filename = "..\\images\\roomUDL.png";
//	//}
//	//else if (upDoor && downDoor && rightDoor)//UDR
//	//{
//	//	filename = "..\\images\\roomUDR.png";
//	//}
//	//else if (upDoor && leftDoor && rightDoor)//ULR
//	//{
//	//	filename = "..\\images\\roomULR.png";
//	//}
//	//else if (upDoor && downDoor)//UD
//	//{
//	//	filename = "..\\images\\roomUD.png";
//	//}
//	//else if (upDoor && leftDoor)//UL
//	//{
//	//	filename = "..\\images\\roomUL.png";
//
//	//}
//	//else if (upDoor && rightDoor)//UR
//	//{
//	//	filename = "..\\images\\roomUR.png";
//	//}
//
//	//else if (downDoor && leftDoor && rightDoor)//DLR
//	//{
//	//	filename = "..\\images\\roomDLR.png";
//	//}
//	//else if (downDoor && leftDoor)//DL
//	//{
//	//	filename = "..\\images\\roomDL.png";
//	//}
//	//else if (downDoor && rightDoor)//DR
//	//{
//	//	filename = "..\\images\\roomDR.png";
//	//}
//	//else if (leftDoor && rightDoor)//LR
//	//{
//	//	filename = "..\\images\\roomLR.png";
//	//}
//	//else if (upDoor)//U
//	//{
//	//	if (special == "Boss") {
//	//		filename = "..\\images\\roomBossU.png";
//	//	}
//	//	else if (special == "Chest") {
//	//		filename = "..\\images\\roomChestU.png";
//	//	}
//	//	else if (special == "Shop") {
//	//		filename = "..\\images\\roomShopU.png";
//	//	}
//	//	else {
//	//		filename = "..\\images\\roomU.png";
//	//	}
//	//}
//	//else if (downDoor)//D
//	//{
//	//	if (special == "Boss") {
//	//		filename = "..\\images\\roomBossD.png";
//	//	}
//	//	else if (special == "Chest") {
//	//		filename = "..\\images\\roomChestD.png";
//	//	}
//	//	else if (special == "Shop") {
//	//		filename = "..\\images\\roomShopD.png";
//	//	}
//	//	else if (special == "FirstRoom") {
//	//		filename = "..\\images\\firstRoom.png";
//	//	}
//	//	else {
//	//		filename = "..\\images\\roomD.png";
//	//	}
//	//}
//	//else if (leftDoor)//L
//	//{
//	//	if (special == "Boss") {
//	//		filename = "..\\images\\roomL.png";
//	//	}
//	//	else if (special == "Chest") {
//	//		filename = "..\\images\\roomChestL.png";
//	//	}
//	//	else if (special == "Shop") {
//	//		filename = "..\\images\\roomShopL.png";
//	//	}
//	//	else {
//	//		filename = "..\\images\\roomL.png";
//	//	}
//
//	//}
//	//else if (rightDoor)//R
//	//{
//	//	if (special == "Boss") {
//	//		filename = "..\\images\\roomBossR.png";
//	//	}
//	//	else if (special == "Chest") {
//	//		filename = "..\\images\\roomChestR.png";
//	//	}
//	//	else if (special == "Shop") {
//	//		filename = "..\\images\\roomShopR.png";
//	//	}
//	//	else {
//	//		filename = "..\\images\\roomR.png";
//	//	}
//
//	}
////	texture->loadFromImg(filename);*/

//Como esta puesto en el archivo sobre creacion de niveles, los niveles se guardaran del siguiente formato
//Si tiene puerta Izquierda, añadimos una L, luego lo mismo con R... del siguiente orden:
// U > R > D > L + _ + numero de sala
	string loadFile; 
	if (doors[Up])
		loadFile.push_back('U');
	if (doors[Right])
		loadFile.push_back('R');
	if (doors[Down])
		loadFile.push_back('D');
	if (doors[Left])
		loadFile.push_back('L');
	//Una vez hayamos puesto esto, guardamos el numero de puertas para mas tarde acceder a la carpeta
	int numDoors = loadFile.size();
	loadFile.push_back('_');

	//A partir de ahora seleccionaremos una sala aleatoria con las puertas dadas

	//Primero vamos a ver cuantos archivos con las puertas tenemos
	string levelPath = Game::getGame()->getResourceManager()->getLevelPath() + to_string(numDoors) + " Door\\";
	ifstream mapFile;
	int i = 0;
	bool found = true;
	while (found)
	{
		//Si existe el archivo lo abrirá y añadiremos uno mas. Si no nos salimos
		string aux = levelPath + loadFile + to_string(i) + ".tmx";
		mapFile.open(aux.c_str());
		found = mapFile.is_open();
		mapFile.close();
		if(found)
			i++;
	}
	//Al final queda refistrado en i el numero de niveles que existen (si existe alguno)
	string level;
	if (i > 0) {
		//Ahora seleccionamos una sala aleatoria entre las salas que haya
		int rnd = rand() % i;
		cout << rnd << endl;
		level = levelPath + loadFile + to_string(rnd) + ".tmx";
	}
	else
		level = Game::getGame()->getResourceManager()->getLevelPath() + "template.tmx"; //Si no encontramos cargaremos el de defecto
	voidRoom = false;
	map = LevelParser::parseLevel(level.c_str(),doors);
}
void Room::render() {

	/*
	for (Recorre los tiles de la sala) {//Pinta la sala
		if (...) {//Si está dentro de la sala
			tile->render();
		}
	}
	*/
	map->render();
}

void Room::setAllDoors(bool set)
{
	for (int i = 0; i < doors.size(); i++)
		doors[i] = set;
}

void Room::update()
{

}
//-----------------------------------------------------------------------------------------------
int Room::getX()
{
	return x;
}
int Room::getY()
{
	return y;
}
bool Room::getDoor(Direction door)
{
	return doors[door];
}
bool Room::getVisited()
{
	return visited;
}
string Room::getSpecial() {
	return special;
}
void Room::setX(int X) {
	x = X;
}
void Room::setY(int Y) {
	y = Y;
}
void Room::setDoor(Direction door, bool set)
{
	doors[door] = set;
}
void Room::setVisited(bool Visited) {
	visited = Visited;
}
void Room::setSpecial(string Special) {
	special = Special;
}

void Room::spawn()
{
	map->spawn();
}



//-------------------------------------------------------------------------------------