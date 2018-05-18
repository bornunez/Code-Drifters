#include "CoinManager.h"
#include"ResourceManager.h"
#include "Random.h"
#include "DecelerationComponent.h"
#include "MainCharacter.h"
#include "PlayState.h"

CoinManager* CoinManager::instance = nullptr;

CoinManager::CoinManager()
{
}

void CoinManager::ResetInstance()
{
	delete instance;
	instance = nullptr;
}

CoinManager::~CoinManager()
{
	//for (int i = 0; i < coins.size(); i++)
	//	delete coins[i];
	for (Coin* obj : coins)
		delete obj;

	coins.clear();
}

CoinManager * CoinManager::getInstance()
{
	if (instance == nullptr)
		instance = new CoinManager();
	return instance;
}

void CoinManager::Drop(int valueToDrop, int x, int y)
{
	//TCoins = ten coins, FCoins = five coins, OCoins = one coins
	int NumTCoins = 0,
		NumFCoins = 0,
		NumOCoins = 0,
		auxValue = valueToDrop * bonusMultiplier;
	//algorithm to randomize the quantity of coins dropped (up to the same value)
	int MaxOneCoins = auxValue / 10;
	if (MaxOneCoins > 0) {
		//number between 0 and MaxOneCoins, both inclusive
		NumTCoins = rand() % (MaxOneCoins + 1);
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
		Coin* c = getCoin(CoinType::TenCoin);
		spawnCoin(c, x, y);
	}
	for (int i = 0; i < NumFCoins; i++) {
		Coin* c = getCoin(CoinType::FiveCoin);
		spawnCoin(c, x, y);
	}
	for (int i = 0; i < NumOCoins; i++) {
		Coin* c = getCoin(CoinType::OneCoin);
		spawnCoin(c, x, y);
	}
}

void CoinManager::Pick(Coin * c)
{
	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
	c->setActive(false);
	switch (c->getCoinType())
	{
	case OneCoin:
		mc->changeMoney(1);
		break;
	case FiveCoin:
		mc->changeMoney(5);
		break;
	case TenCoin:
		mc->changeMoney(10);
		break;
	default:
		break;
	}
}

void CoinManager::spawnCoin(Coin * c, int x, int y)
{
	Transform* t = c->getTransform();
	t->position.set(x, y);
	c->updatePreviousPosition();
	c->updateBody();
	t->body.w = t->body.h = 50;
	int randX = rand() % 360;
	
	t->velocity.set(1,0);
	t->velocity.rotate(randX);
	t->speed = rand() % (500 - 250 + 1) + 250;

	c->addComponent(new DecelerationComponent(c, 1,0.5));

}

std::vector<Coin*> CoinManager::getCoins() { return coins; }

Coin * CoinManager::getCoin(CoinType type)
{
	int i = 0;
	while (i < coins.size() && (coins[i]->isActive() || coins[i]->getCoinType() != type))
		i++;
	if (i < coins.size()) {
		coins[i]->setActive(true);
		return coins[i];
	}
	else {
		Coin* newCoin = nullptr;
		switch (type)
		{
		case OneCoin:
			newCoin = new Coin(ResourceManager::getInstance()->getTexture(OneCoinSprite), type);
			break;
		case FiveCoin:
			newCoin = new Coin(ResourceManager::getInstance()->getTexture(FiveCoinSprite), type);
			break;
		case TenCoin:
			newCoin = new Coin(ResourceManager::getInstance()->getTexture(TenCoinSprite), type);
			break;
		default:
			break;
		}
		newCoin->setActive(true);
		coins.push_back(newCoin);
		return newCoin;
	}
}

void CoinManager::clean()
{
	for (Coin* c : coins)
		c->setActive(false);
}

void CoinManager::render() {
	for (int i = 0; i < coins.size(); i++) {
		if (coins[i]->isActive())
			coins[i]->render();
	}
}

void CoinManager::update() {
	for (int i = 0; i < coins.size(); i++) {
		if (coins[i]->isActive())
			coins[i]->update();
	}
}

void CoinManager::setBonusMultiplier(float multiplicator) {
	bonusMultiplier = multiplicator;
}

