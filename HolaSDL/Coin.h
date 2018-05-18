#pragma once
//#include "checkML.h"
#include"GameObject.h"
enum CoinType
{
	OneCoin,
	FiveCoin,
	TenCoin
};
class Coin : public GameObject
{
public:
	Coin(Texture* text, CoinType val);
	virtual ~Coin();
	virtual void handleEvents(SDL_Event& e);
	CoinType getCoinType();
private:
	CoinType value = CoinType::OneCoin;
};

