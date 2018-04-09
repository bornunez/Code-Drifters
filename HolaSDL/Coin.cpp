#include "Coin.h"



Coin::Coin(Texture* text, Transform pos, CoinType val) : GameObject()
{
	texture = text;
	transform = pos;
	value = val;
}


Coin::~Coin()
{
}

void Coin::update(){}

void Coin::render() {}

void Coin::handleEvents(SDL_Event& e){}

CoinType Coin::getCoinType() { return value; }
