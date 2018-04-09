#include "CoinManager.h"



void CoinManager::Drop(int valueToDrop)
{
}

CoinManager::CoinManager()
{
}

CoinManager::~CoinManager()
{
}

std::vector<Coin*> CoinManager::getCoins() { return coins; }

Coin * CoinManager::getCoin()
{
	int i = 0;
	while (i < coins.size() && coins[i]->isActive)
		i++;
	if (i < coins.size())
		return coins[i];
	else {

	}
	return nullptr;
}


