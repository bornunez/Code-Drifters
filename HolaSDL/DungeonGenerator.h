#pragma once
#include <vector>
#include "sdl_includes.h"
class Room;
class Game;

using namespace std;
class DungeonGenerator
{
public:
	DungeonGenerator(Game* game,int mapWidth, int mapHeight, int maxRooms, int sizeX, int sizeY);
	~DungeonGenerator();
	void CreateMap();
	void Run();

	Room* getRoom(int x, int y);
	Room* getFirstRoom();

private:
	void ClearMap();
	vector<Room*> FindDeadEnds();
	void CreateSpecialRooms();
	void AddFirstRoom();
	vector<string> CheckDirections(int x, int y);
	void GenerateDungeon();
	void CreateRoom(int x, int y);
	void FixDoors();
	void UnvisitedRoomToQueue(vector<string> posibleDirections_, string direction, int x, int y);
	void SetRoomDirections(vector<string> posibleDirections_, string direction, int x, int y);
	void SetEntryDoor(int x, int y, string direction);
	bool CellInsideBounds(int x, int y);
	bool AvailableCell(int x, int y);
	void render();

	void LoadTextures();
	int winY = 50;
	int winX = 50;
	int winWidth = 800;
	int winHeight = 600;

	
	SDL_Rect size_;

	int mapWidth_;
	int mapHeight_;
	int maxRooms_;
	int roomsLeft_;
	Game* game_;
	vector<Room*> visitedRooms_;
	vector<Room*> unvisitedRooms_;
	vector<vector<Room*>> Dungeon_;

};

