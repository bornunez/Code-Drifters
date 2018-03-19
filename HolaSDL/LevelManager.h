#pragma once
#include <vector>
using namespace std;

class Room;
class DungeonGenerator;

enum RoomDirection{Up,Right,Down,Left};
struct DirPair { int x; int y; };

class LevelManager
{
private:

	//Singleton
	static LevelManager * instance;
	LevelManager();

	//Cosas de puertas
	vector<DirPair> directions;

	//Progreso del jugador
	int level;
	int baseRooms;
	int roomsPerLevel;
	//Posicion del jugador
	int roomX, roomY;
	Room* currentRoom;
	Room* firstRoom;
	DungeonGenerator* dungeon;

public:
	static LevelManager * getInstance();

	Room* getCurrentRoom() { return currentRoom; }
	Room* getFirstRoom() { return firstRoom; }
 
	Room* getRoom(int x, int y);
	Room* getRoom(RoomDirection dir);

	void changeRoom(Room* room);
	void changeRoom(int x, int y);
	void changeRoom(RoomDirection dir);
	void render();

	//Metodos de control
	void init();
	void newMap();
	~LevelManager();
};