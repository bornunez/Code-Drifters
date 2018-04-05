#pragma once
#include "Texture.h"
#include <vector>
class Tileset;

// CONSTANTES
const int NUM_TEXTURES = 23;
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

//Aqui se pone el nombre que se le va a dar  a la textura como argumento en el getTexture
enum TextureName { BulletSprite, SwordButton, GunButton, MemexButton, MaxAttackButton, SwordChargeButton};

//IMPORTANTE//
//El orden en el que se ponen las cosas en la enum debe ser el mismo que en el que se añaden las cosas abajo en TextureAtributes ya que si no no van a coincidir

using namespace std;
class ResourceManager
{
private:
	//Aqui se añaden las texturas con estoso args {path, numRows, numCols}
	const TextureAtributes TEXTURE_ATRIBUTES[NUM_TEXTURES]{ 
		{ "bullet.png", 1, 1 },
		{ "Tree\\1.png", 1, 1 },
		{ "Tree\\243534.png", 1, 1 },
		{ "Tree\\3.png", 1, 1 },
		{ "Tree\\11.png", 1, 1 },
		{ "Tree\\12.png", 1, 1 },
		{ "Tree\\21.png", 1, 1 },
		{ "Tree\\22.png", 1, 1 },
		{ "Tree\\31.png", 1, 1 },
		{ "Tree\\32.png", 1, 1 },
		{ "Tree\\111.png", 1, 1 },
		{ "Tree\\121.png", 1, 1 },
		{ "Tree\\122.png", 1, 1 },
		{ "Tree\\211.png", 1, 1 },
		{ "Tree\\221.png", 1, 1 },
		{ "Tree\\311.png", 1, 1 },
		{ "Tree\\312.png", 1, 1 },
		{ "Tree\\321.png", 1, 1 },
		{ "Tree\\2211.png", 1, 1 },
		{ "Tree\\BlueLine.png", 1, 1 },
		{ "Tree\\GreenLine.png", 1, 1 },
		{ "Tree\\RedLine.png", 1, 1 },
		{ "Tree\\Line.png", 1, 1 },
	};			



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

	//Devuelve la textura dado su numero en la enum
	Texture * getTexture(int numTexture) { return textures[numTexture]; };
	Tileset* getCurrTileset() { return currentTileset; };
	Tileset* getProtaTileset() { return protaTileset; };
	Tileset* getEnemyTileset(int numTileset) { return enemyTilesets[numTileset];
	}
};

