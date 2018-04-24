#include "Coin.h"
#include "SimpleAnimationComponent.h"
#include "BasicMovement.h"


Coin::Coin(Texture* text, CoinType val) : GameObject(text,0,0,50,50)
{
	//texture = text;
	//transform = pos;
	value = val;
	setCollisionsLayers({ "Aire","Paredes" });
	addComponent(new SimpleAnimationComponent(this, text,0.0,200));
	addComponent(new BasicMovement(this));
}


Coin::~Coin()
{
}

void Coin::handleEvents(SDL_Event& e){}

CoinType Coin::getCoinType() { return value; }
