#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "sdl_includes.h"
#include "Font.h"

using namespace std;
typedef unsigned int uint;

class Texture {
public:
	Texture(SDL_Renderer* renderer);
	Texture(SDL_Renderer* renderer, string fileName, uint numRows, uint numCols);				//Carga una textura 
	Texture(SDL_Renderer* renderer, string text, const Font& font, const SDL_Color color);		//Carga una textura de texto
	virtual ~Texture();

	int getWidth();
	int getHeight();
	bool loadFromImg(string filename, uint numRows = 1, uint numCols = 1);
	bool loadFromText(string texto, Font const& font, SDL_Color color = { 0, 0, 0, 255 });
	void render(int x, int y) const;
	void render(SDL_Rect const& dest, SDL_Rect* clip = nullptr) const;
	void render(SDL_Rect const& dest, double angle, SDL_Rect* clip = nullptr) const;
	void close();

private:

	SDL_Texture *texture = nullptr;
	SDL_Renderer* renderer = nullptr;
	uint width;		//	Texture	width (pixels)
	uint height;	//	Texture	height (pixels)
	uint frameWidth = 0; //	Frame width	(pixels)	
	uint frameHeight = 0; //	Frame height (pixels)
	string path;	//Directorio desde el que se lee la textura
};

#endif /* TEXTURE_H_ */
