#pragma once
//#include "checkML.h"
#include <vector>
#include <string>
#include "sdl_includes.h"
class Room;
class Game;
class PlayState;
class Texture;
class Font;

using namespace std;

struct LoadBar {
	SDL_Rect dst;
	SDL_Rect currDst;

	SDL_Rect currentSrc;

	SDL_Rect backGroundDst;
	Texture* backGroundTex;

	Texture* borderTex;
	Texture* barTex;
	Texture* BottomTex;
};
struct TextRect
{
	SDL_Rect dest;
	Texture* texture;
};

using namespace std;
class DungeonGenerator
{
public:
	DungeonGenerator(int mapWidth, int mapHeight, int maxRooms);
	~DungeonGenerator();
	void CreateMap();
	void CreateMapFromFile();

	int getLevelWidth() { return mapWidth_; }
	int getLevelHeight() { return mapHeight_; }

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
	void load();
	bool AvailableCell(int x, int y);

	int mapWidth_;
	int mapHeight_;
	int maxRooms_;
	int roomsLeft_;
	vector<Room*> visitedRooms_;
	vector<Room*> unvisitedRooms_;
	vector<vector<Room*>> Dungeon_;

	//Carga del tutorial
	void GenerateFromFile(string file);
	void SetMapDoors();
	void SetDoors(int i, int j);
	void LoadRoomsFromFile();

	void loadTexts();
	LoadBar loadbar;
	void RenderProgresBar(int current, int max, string text);
	Font* neonFont;
	TextRect randText, loadText,levelText;
};

