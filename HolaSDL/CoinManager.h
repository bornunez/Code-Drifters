#pragma once
#include"Coin.h"

class CoinManager
{
public:
	void Drop(int valueToDrop);
	CoinManager();
	~CoinManager();
	std::vector<Coin*> getCoins();
	Coin* getCoin();
protected:
	std::vector<Coin*> coins;
};

