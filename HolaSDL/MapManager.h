#pragma once
class Room;
class DungeonGenerator;
class MapManager
{
private:
	//Progreso del jugador
	int level = 0;
	const int baseRooms = 20;
	const int roomsPerLevel = 5;
	//Posicion del jugador
	int roomX, roomY;
	Room* currentRoom;
	Room* firstRoom;
	DungeonGenerator* dungeon;
public:
	MapManager();
	Room* getCurrentRoom() { return currentRoom; }
	Room* getFirstRoom() { return firstRoom; }

	Room* getLeftRoom();
	Room* getRightRoom();
	Room* getTopRoom();
	Room* getBottomRoom();

	void changeRoom(Room* room);
	void render();

	//Metodos de control
	void init();
	void newMap();
	~MapManager();
};

