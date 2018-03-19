#include "MapManager.h"
#include "DungeonGenerator.h"
#include "Room.h"


MapManager::MapManager()
{
}

Room * MapManager::getLeftRoom()
{
	return dungeon->getRoom(roomX , roomY+1);
	
}

Room * MapManager::getRightRoom()
{
	return nullptr;
}

Room * MapManager::getTopRoom()
{
	return nullptr;
}

Room * MapManager::getBottomRoom()
{
	return nullptr;
}


void MapManager::changeRoom(Room * room)
{
	currentRoom = room;
	roomX = room->getX(); roomY = room->getY();
}


void MapManager::render()
{
	currentRoom->render();
}

void MapManager::init()
{
	newMap();
}

void MapManager::newMap()
{

	dungeon = new DungeonGenerator(20, 20, baseRooms + (level * roomsPerLevel));
	dungeon->CreateMap();
	firstRoom = dungeon->getFirstRoom();
	currentRoom = firstRoom;
	roomX = currentRoom->getX(); roomY = currentRoom->getY();
	//level->getFirstRoom()->addCharacter(mainCharacter);//Se añade el personaje a la primera sala
}

MapManager::~MapManager()
{
}
