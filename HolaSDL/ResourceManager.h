#pragma once
#include "Texture.h"
#include <vector>
class Tileset;

// CONSTANTES
const int NUM_TEXTURES = 1;
const int NUM_TILESET = 1;
const int NUM_PROTATILESET = 1;
const int NUM_ENEMYTILESET = 2;
const string TEXT_PATH = "..\\images\\";
const string LEVEL_PATH = "..\\levels\\";
const string TILESET_PATH = "..\\levels\\tileset\\";
const string ENEMY_PATH = "..\\Animations\\Enemies\\";
const string PROTATILESET_PATH = "..\\Animations\\Protagonist\\tileset\\";
// Estructura para las texturas
typedef struct {
	string filename;
	int numRows;
	int numCols;
} TextureAtributes;

enum TextureName {BulletSprite,ProtaAnimation};

using namespace std;
class ResourceManager
{

private:
	const TextureAtributes TEXTURE_ATRIBUTES[NUM_TEXTURES]{ { "bullet.png", 1, 1 }};			//Esto ira a xml
	//Array que contiene punteros a todas las texturas del juego.
	Texture* textures[NUM_TEXTURES];
	//Vector de tilesets
	const string tilesetNames[NUM_TILESET]{ "tile.tsx" };	
	vector<Tileset*> tilesets;
	Tileset* currentTileset;
	const string protaTilesetName = "ProtaAnimation.tsx";
	Tileset* protaTileset;
	const string enemyTilesetNames[NUM_ENEMYTILESET]{ "Gunner.tsx", "Stalker.tsx" };
	vector<Tileset*> enemyTilesets;
	SDL_Renderer* renderer;
	static ResourceManager* instance;

	void loadTextures();
	void loadTilesets();
	void loadProtaTileset();
	void loadEnemyTilesets();
public:
	ResourceManager(SDL_Renderer* renderer);
	static ResourceManager* getInstance() { return instance; }
	static void createInstance(SDL_Renderer* renderer);

	~ResourceManager();
	Texture * getTexture(int numTexture) { return textures[numTexture]; };
	Tileset* getCurrTileset() { return currentTileset; };
	Tileset* getProtaTileset() { return protaTileset; };
	Tileset* getEnemyTileset(int numTileset) { return enemyTilesets[numTileset];
	}
};

