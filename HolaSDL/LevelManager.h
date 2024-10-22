#pragma once
//#include "checkML.h"
#include <vector>
#include "sdl_includes.h"
class Message;
using namespace std;

class Room;
class DungeonGenerator;

enum Direction{Up,Right,Down,Left, None};
struct DirPair { int x; int y; };
enum LevelType{ City, Lab};
const int maxLevel = 2;

class LevelManager
{
private:
	//Singleton
	static LevelManager * instance;
	LevelManager();

	void onRoomChange(Room * room,Room* prevRoom, Direction dir);

	//Cosas de puertas
	vector<DirPair> directions;

	//Progreso del jugador
	int level;
	int baseRooms;
	int roomsPerLevel;
	vector<string> levelTypePath { "City_Levels\\" , "Lab_Levels\\" };
	LevelType currentLevelType;
	//Posicion del jugador
	int roomX, roomY;
	Room* currentRoom;
	Room* firstRoom;
	DungeonGenerator* dungeon;

public:
	static LevelManager * getInstance();
	static void ResetInstance();

	DungeonGenerator* getLevel() { return dungeon; }
	int getLevelNumber() { return level; }
	Room* getCurrentRoom() { return currentRoom; }
	Room* getFirstRoom() { return firstRoom; }
	void enterMap();
 
	Room* getRoom(int x, int y);
	Room* getRoom(Direction dir);

	void changeRoom(Room* room);
	void changeRoom(int x, int y);
	void changeRoom(Direction dir);
	Room* getBossRoom();
	Room* getShopRoom();

	void update();
	void handleEvents(SDL_Event & e);
	void render();
	void lateRender();

	bool getDoor(Direction dir);

	string getActiveLevelPath() { return levelTypePath[currentLevelType]; }

	//Metodos de control
	void init(bool tutorial);
	void newMap();
	void nextLevel();

	void sendMessageCurrent(Message* msg);
	void sendMessageAll(Message* msg);
	~LevelManager();
};