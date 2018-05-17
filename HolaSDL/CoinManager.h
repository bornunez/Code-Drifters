#pragma once
//#include "checkML.h"
#include"Coin.h"

class CoinManager
{
public:
	static CoinManager* getInstance();
	static void ResetInstance();
	virtual ~CoinManager();

	std::vector<Coin*> getCoins();
	Coin* getCoin(CoinType type);
	void clean();

	void Drop(int valueToDrop, int x, int y);
	void Pick(Coin* c);

	virtual void render();
	virtual void update();
	void setBonusMultiplier(float multiplicator);
protected:
	float bonusMultiplier = 1.0;

	CoinManager();
	std::vector<Coin*> coins;
	static CoinManager* instance;
	void spawnCoin(Coin* c, int x, int y);

};

