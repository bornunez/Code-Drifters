#include "ShopBox.h"
#include "Game.h"



void ShopBox::adjustRects()
{
	descriptionRect.w = description.size() * fontSize;
	descriptionRect.x = (boxRect.x+boxRect.w/2) - (description.size() * fontSize)/2;
	priceRect.w = price.size() * fontSize;
	priceRect.x = (boxRect.x + boxRect.w / 2) - (price.size() * fontSize)/2;
}

ShopBox::ShopBox()
{
	boxTex = new Texture(game->getRenderer(), "..\\images\\DialogoSinAnim.png");
	descriptionTex = new Texture(game->getRenderer());
	priceTex = new Texture(game->getRenderer());

	font = new Font("..\\images\\Polentical Neon Bold.ttf", 50);
	boxRect= RECT(70, 520, 900, 200);
	descriptionRect= RECT(170, 560, 150, 50);
	priceRect = RECT(350, 620, 150, 50);

	active = false;
	
}


ShopBox::~ShopBox()
{
	delete boxTex;
	delete descriptionTex;
	delete priceTex;
}

void ShopBox::render()
{
	if (active) 
	{
		boxTex->render(boxRect);
		descriptionTex->render(descriptionRect);
		priceTex->render(priceRect);
	}
}

void ShopBox::actualiza(std::string descrip, int prc)
{
	description = descrip;
	descriptionTex->loadFromText(description, *font);
	if (prc == 0) 
	{
		price = "NO DISPONIBLE";
	}
	else if (prc == -1) 
	{
		price = "YA OBTENIDO";
	}
	else 
	{
		price= std::to_string(prc)+" CREDITS";
	}
	priceTex->loadFromText(price, *font);
	adjustRects();
}

void ShopBox::setActive(bool activ)
{
	active = activ;
}
