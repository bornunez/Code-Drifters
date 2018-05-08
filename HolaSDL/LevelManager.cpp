#include "LevelManager.h"
#include "DungeonGenerator.h"
#include "Room.h"
#include "Managers.h"
#include "Door.h"
#include "Map.h"
#include "PlayState.h"
#include "GameObject.h"
#include"MainCharacter.h"
#include "CoinManager.h"
#include "ItemManager.h"
#include <iostream>

LevelManager* LevelManager::instance = nullptr;

LevelManager::LevelManager()
{
	//Ponemos el vector de direcciones
	directions = { {0,-1},{1,0},{0,1},{-1,0} };
}

void LevelManager::onRoomChange(Room* room, Direction dir)
{
	//COSAS QUE PASAN CUANDO CAMBIAS DE SALA AQUI
	//Antes de Spawnear, despawneamos los que hubiera
	EnemyManager::getInstance()->killAll();
	ItemManager::getInstance()->reset();
	CoinManager::getInstance()->clean();

	//Y ponemos al jugador en la puerta contraria
	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
	if (dir != None) {
		Vector2D entry = room->getMap()->getDoor((Direction)((dir + 2) % 4))->getEntry();
		mc->getTransform()->position.set(entry);
	}
	
	//Si la sala es de tipo boss, lo spawneamos
	if (room->getType() == BossRoom)
	{
		GameObject * bossSpawn = room->getMap()->getBossSpawn();
		GameObject * ePoint = room->getMap()->getEntryPoint();
		if (bossSpawn != nullptr)
			EnemyManager::getInstance()->spawnBoss(bossSpawn->getTransform()->position.getX(), bossSpawn->getTransform()->position.getY());
		if (ePoint != nullptr)
			mc->getTransform()->position.set(ePoint->getTransform()->position);
	}

	mc->getTransform()->velocity.set(0, 0);
	mc->updatePreviousPosition();
	mc->updateBody();

	room->spawn();
	room->setExplored(true);
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
	int auxX = roomX + directions[dir].x;
	int auxY = roomY + directions[dir].y;
	return auxX >= 0 && auxX < dungeon->getLevelWidth() && auxY >= 0 && auxY < dungeon->getLevelHeight() ? getRoom(auxX,auxY ) : nullptr;
	//return getRoom(auxX, auxY);
}

void LevelManager::changeRoom(Room * room)
{
	if (!room->isVoid()) {
		currentRoom = room;
		roomX = room->getX(); roomY = room->getY();
		onRoomChange(room, None);
	}
}

void LevelManager::changeRoom(int x, int y)
{
	Room* room = getRoom(x, y);
	if (room != nullptr && !room->isVoid()) {
		currentRoom = room;
		roomX = x; roomY = y;
		onRoomChange(room, None);
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
			if (room->getType() == Shop)
				cout << "Tienda!";
			currentRoom = room;
			roomX += directions[dir].x;
			roomY += directions[dir].y;
			onRoomChange(room, dir);
		}
	}
}

Room * LevelManager::getBossRoom()
{
	Room* r = nullptr;
	bool found = false;
	for (int i = 0;!found && i < dungeon->getLevelHeight(); i++) {
		for (int j = 0; !found && j < dungeon->getLevelWidth(); j++) {
			 r = dungeon->getRoom(j, i);
			 found = r->getType() == BossRoom;	
		}
	}
	return found ? r : nullptr;

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
	
	//level->getFirstRoom()->addCharacter(mainCharacter);//Se a�ade el personaje a la primera sala
}

LevelManager::~LevelManager()
{
}