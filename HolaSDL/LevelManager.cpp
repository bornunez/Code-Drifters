#include "LevelManager.h"
#include "DungeonGenerator.h"
#include "Room.h"
#include "Managers.h"
#include "Door.h"
#include "Map.h"
#include "PlayState.h"
#include "GameObject.h"
#include"MainCharacter.h"
#include "ItemManager.h"
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

void LevelManager::enterMap()
{
	getFirstRoom()->spawn();
	GameObject* ePoint = currentRoom->getMap()->getEntryPoint();
	if (ePoint != nullptr) {
		//Y ponemos al jugador en la puerta contraria
		MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
		mc->getTransform()->velocity.set(0, 0);
		mc->getTransform()->position.set(ePoint->getTransform()->position);
		mc->updatePreviousPosition();
		mc->updateBody();
	}
}

Room * LevelManager::getRoom(int x, int y)
{
	if(x >= 0 && x < dungeon->getLevelWidth() && y >= 0 && y < dungeon->getLevelHeight())
		return dungeon->getRoom(x, y);
	else 
		return nullptr;
}

Room * LevelManager::getRoom(Direction dir)
{
	return getRoom(roomX + directions[dir].x, roomY + directions[dir].y);
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
	Room* room = getRoom(x, y);
	if (room != nullptr && !room->isVoid()) {
		currentRoom = room;
		roomX = x; roomY = y;
	}
}

void LevelManager::changeRoom(Direction dir)
{
	bool canMove = getDoor(dir);
	if (canMove) {
		//Pedimos la sala de la direccion
		Room* room = getRoom(dir);
		if (room != nullptr && !room->isVoid()) {
			//Si hay sala, la cambiamos
			currentRoom = room;
			roomX += directions[dir].x;
			roomY += directions[dir].y;
			//COSAS QUE PASAN CUANDO CAMBIAS DE SALA AQUI
			//Antes de Spawnear, despawneamos los que hubiera
			EnemyManager::getInstance()->killAll();
			ItemManager::getInstance()->reset();

			//Y ponemos al jugador en la puerta contraria
			MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
			Vector2D entry = room->getMap()->getDoor((Direction)((dir + 2) % 4))->getEntry();
			mc->getTransform()->velocity.set(0, 0);
			mc->getTransform()->position.set(entry);
			mc->updatePreviousPosition();
			mc->updateBody();
			room->spawn();
			room->setExplored(true);
		}
	}
}


void LevelManager::render()
{
	currentRoom->render();
}

bool LevelManager::getDoor(Direction dir)
{
	return currentRoom->getDoor(dir);
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
	currentRoom->setExplored(true);
	
	//level->getFirstRoom()->addCharacter(mainCharacter);//Se añade el personaje a la primera sala
}

LevelManager::~LevelManager()
{
}