#pragma once
#include "Texture.h"

// CONSTANTES
const int NUM_TEXTURES = 1;
const string TEXT_PATH = "..\\images\\";
const string LEVEL_PATH = "..\\levels\\";

// Estructura para las texturas
typedef struct {
	string filename;
	int numRows;
	int numCols;
} TextureAtributes;

enum TextureName {BulletSprite};

using namespace std;
class ResourceManager
{

private:
	const TextureAtributes TEXTURE_ATRIBUTES[NUM_TEXTURES] { { "bullet.png", 1, 1 } };			//Esto ira a xml
	//Array que contiene punteros a todas las texturas del juego.
	Texture* textures[NUM_TEXTURES];

	SDL_Renderer* renderer;

	void loadTextures();

public:
	ResourceManager(SDL_Renderer* renderer);
	~ResourceManager();
	Texture * getTexture(int numTexture) { return textures[numTexture]; };
};