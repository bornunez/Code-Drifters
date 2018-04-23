#pragma once
#include"GameObject.h"
enum class CoinType
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

