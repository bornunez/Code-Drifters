#pragma once
#include "checkML.h"
#include <string> 
#include "GameObject.h"
#include "Texture.h"
class ShopBox: public GameObject
{
private:
	bool active;
	Font* font;

	SDL_Rect boxRect;
	Texture* boxTex;

	SDL_Rect descriptionRect;
	std::string description;
	Texture* descriptionTex;
	

	SDL_Rect priceRect;
	std::string price;
	Texture* priceTex;

	void adjustRects();
	int fontSize = 25;
public:
	ShopBox();
	virtual ~ShopBox();
	virtual void render();

	void actualiza(std::string descripcion, int price);
	void setActive(bool active);
};

