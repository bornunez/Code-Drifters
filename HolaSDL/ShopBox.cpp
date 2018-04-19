#include "ShopBox.h"
#include "Game.h"



void ShopBox::adjustRects()
{
	descriptionRect.w = description.size() * 25;
	priceRect.w = price.size() * 25;
}

ShopBox::ShopBox()
{
	boxTex = new Texture(game->getRenderer(), "..\\images\\DialogoSinAnim.png");
	descriptionTex = new Texture(game->getRenderer());
	costTex = new Texture(game->getRenderer());
	priceTex = new Texture(game->getRenderer());

	font = new Font("..\\images\\Polentical Neon Bold.ttf", 50);
	boxRect= RECT(70, 470, 900, 250);
	descriptionRect= RECT(150, 510, 150, 50);
	costRect= RECT(150, 570, 150, 50);
	priceRect = RECT(350, 570, 150, 50);

	active = false;
	
}


ShopBox::~ShopBox()
{
	delete boxTex;
	delete costTex;
	delete descriptionTex;
	delete priceTex;
}

void ShopBox::render()
{
	if (active) 
	{
		boxTex->render(boxRect);
		descriptionTex->render(descriptionRect);
		costTex->render(costRect);
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
	else if (prc = -1) 
	{
		price = "YA OBTENIDO";
	}
	else 
	{
		price= std::to_string(prc);
	}
	priceTex->loadFromText(price, *font);
	adjustRects();
}

void ShopBox::setActive(bool activ)
{
	active = activ;
}
