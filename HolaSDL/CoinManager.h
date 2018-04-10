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
protected:
	std::vector<Coin*> coins;
};

