#include "Coin.h"



Coin::Coin(Texture* text, CoinType val) : GameObject(text,{0,0},10,10)
{
	//texture = text;
	//transform = pos;
	value = val;
}


Coin::~Coin()
{
}

void Coin::update(){}

void Coin::render() {}

void Coin::handleEvents(SDL_Event& e){}

CoinType Coin::getCoinType() { return value; }
