#pragma once
#include "Texture.h"
#include <vector>
class Tileset;

// CONSTANTES
const int NUM_TEXTURES = 3;
const int NUM_TILESET = 1;
const string TEXT_PATH = "..\\images\\";
const string LEVEL_PATH = "..\\levels\\";
const string TILESET_PATH = "..\\levels\\tileset\\";
// Estructura para las texturas
typedef struct {
	string filename;
	int numRows;
	int numCols;
} TextureAtributes;

enum TextureName {BulletSprite,ProtaRun, ProtaIdle};

using namespace std;
class ResourceManager
{

private:
	const TextureAtributes TEXTURE_ATRIBUTES[NUM_TEXTURES]{ { "bullet.png", 1, 1 },{ "RunAnimation.png",12,4 } ,{ "ProtaIdle.png",4,1 } };			//Esto ira a xml
	//Array que contiene punteros a todas las texturas del juego.
	Texture* textures[NUM_TEXTURES];
	//Vector de tilesets
	const string tilesetNames[NUM_TILESET]{ "tile.tsx" };
	vector<Tileset*> tilesets;
	Tileset* currentTileset;

	SDL_Renderer* renderer;

	void loadTextures();
	void loadTilesets();

public:
	ResourceManager(SDL_Renderer* renderer);
	~ResourceManager();
	Texture * getTexture(int numTexture) { return textures[numTexture]; };
	Tileset* getCurrTileset() { return currentTileset; }
};