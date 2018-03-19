#include "LevelManager.h"
#include "DungeonGenerator.h"
#include "Room.h"
#include "Managers.h"
#include <iostream>

LevelManager* LevelManager::instance = nullptr;

LevelManager::LevelManager()
{
	//Ponemos el vector de direcciones
	directions = { {0,-1},{1,0},{0,1},{-1,0} };
}

LevelManager * LevelManager::getInstance()
{
	if (instance == nullptr)
		instance = new LevelManager();
	return instance;
}

Room * LevelManager::getRoom(int x, int y)
{
	return dungeon->getRoom(x, y);
}

Room * LevelManager::getRoom(RoomDirection dir)
{
	return dungeon->getRoom(roomX + directions[dir].x, roomY + directions[dir].y);
}

void LevelManager::changeRoom(Room * room)
{
	if (!room->isVoid()) {
		currentRoom = room;
		roomX = room->getX(); roomY = room->getY();
	}
}

void LevelManager::changeRoom(int x, int y)
{
	Room* room = dungeon->getRoom(x, y);
	if (!room->isVoid()) {
	currentRoom = room;
	roomX = x; roomY = y;
}
}

void LevelManager::changeRoom(RoomDirection dir)
{
	Room* room = getRoom(dir);
	if (!room->isVoid()) {
		currentRoom = room;
		roomX += directions[dir].x;
		roomY += directions[dir].y;
		std::cout << "Cambio de direccion" << std::endl;
		room->spawn();
	}
	else 
		std::cout << "Abajo no hay sala!" << std::endl;
}


void LevelManager::render()
{
	currentRoom->render();
}

void LevelManager::init()
{
	level = 0;
	baseRooms = 20;
	roomsPerLevel = 5;
	newMap();
}

void LevelManager::newMap()
{

	dungeon = new DungeonGenerator(20, 20, baseRooms + (level * roomsPerLevel));
	dungeon->CreateMap();
	firstRoom = dungeon->getFirstRoom();
	currentRoom = firstRoom;
	roomX = currentRoom->getX(); roomY = currentRoom->getY();
	//level->getFirstRoom()->addCharacter(mainCharacter);//Se añade el personaje a la primera sala
}

LevelManager::~LevelManager()
{
}