#pragma once
#include"Coin.h"

class CoinManager
{
public:
	void Drop(int valueToDrop);
	CoinManager();
	virtual ~CoinManager();
	std::vector<Coin*> getCoins();
	Coin* getCoin(CoinType type);

	virtual void render();
	virtual void update();
protected:
	std::vector<Coin*> coins;
};

