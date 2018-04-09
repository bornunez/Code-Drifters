#pragma once
#include"GameObject.h"
enum class CoinType
{
	TenCoin,
	FiftyCoin,
	HundredCoin
};
class Coin : public GameObject
{
public:
	Coin(Texture* text, Transform pos, CoinType val);
	~Coin();
	virtual void render();
	virtual void update();
	virtual void handleEvents(SDL_Event& e);
	CoinType getCoinType();
private:
	CoinType value = CoinType::TenCoin
};

