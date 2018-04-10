#include "CoinManager.h"
#include"ResourceManager.h"


void CoinManager::Drop(int valueToDrop)
{
	//TCoins = ten coins, FCoins = five coins, OCoins = one coins
	int NumTCoins = 0,
		NumFCoins = 0,
		NumOCoins = 0,
		auxValue = valueToDrop;
	//algorithm to randomize the quantity of coins dropped (up to the same value)
	int MaxTenCoins = auxValue / 10;
	if (MaxTenCoins > 0) {
		//number between 0 and MaxTenCoins, both inclusive
		NumTCoins = rand() % (MaxTenCoins + 1);
		auxValue -= (NumTCoins * 10);
	}
	//analogue for five coins 
	int MaxFiveCoins = auxValue / 5;
	if (MaxFiveCoins > 0) {
		NumFCoins = rand() % (MaxFiveCoins + 1);
		auxValue -= (NumFCoins * 5);
	}
	//we can't randomize the last coin due to value loss
	NumOCoins = auxValue;

	/*cout << NumTCoins << " Numero de monedas de 10" << endl;
	cout << NumFCoins << " Numero de monedas de 5" << endl;
	cout << NumOCoins << " Numero de monedas de 1" << endl;*/

	//now we use getCoin to create the active coins
	for (int i = 0; i < NumTCoins; i++) {
		Coin* c = getCoin(CoinType::HundredCoin);
	}
	for (int i = 0; i < NumFCoins; i++) {
		Coin* c = getCoin(CoinType::FiftyCoin);
	}
	for (int i = 0; i < NumOCoins; i++) {
		Coin* c = getCoin(CoinType::TenCoin);
	}
}

CoinManager::CoinManager()
{
}

CoinManager::~CoinManager()
{
	for (int i = 0; i < coins.size(); i++)
		delete coins[i];
}

std::vector<Coin*> CoinManager::getCoins() { return coins; }

Coin * CoinManager::getCoin(CoinType type)
{
	int i = 0;
	while (i < coins.size() && coins[i]->isActive() && coins[i]->getCoinType() != type)
		i++;
	if (i < coins.size()) {
		coins[i]->setActive(true);
		return coins[i];
	}
	else {
		Coin* newCoin = new Coin(ResourceManager::getInstance()->getTexture(CoinSprite), type);
		coins.push_back(newCoin);
		return newCoin;
	}
}


