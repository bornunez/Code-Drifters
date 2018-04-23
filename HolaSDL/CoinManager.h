#pragma once
#include"Coin.h"

class CoinManager
{
public:
	static CoinManager* getInstance();
	virtual ~CoinManager();
	std::vector<Coin*> getCoins();
	Coin* getCoin(CoinType type);

	void Drop(int valueToDrop, int x, int y);
	void Pick(Coin* c);

	virtual void render();
	virtual void update();
protected:
	CoinManager();
	std::vector<Coin*> coins;
	static CoinManager* instance;
	void spawnCoin(Coin* c, int x, int y);
};

