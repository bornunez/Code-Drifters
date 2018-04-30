#include "EnemyManager.h"
#include "Enemy.h"
#include "ExampleEnemy.h"
#include "EnemyStalker.h"
#include "EnemyGunner.h"
#include "EnemyCharger.h"
#include "MainCharacter.h"
#include "EnemyTurret.h"
#include "EnemyBomb.h"
#include "EnemyBomber.h"
#include "Map.h"
#include "PlayState.h"

EnemyManager* EnemyManager::instance = nullptr;

EnemyManager::EnemyManager()
{
}


Enemy * EnemyManager::createEnemy(EnemyType eType)
{
	Enemy* e = nullptr;
	switch (eType)
	{
	case Stalker:
		e = new EnemyStalker(mc);
		break;
	case Gunner:
		e = new EnemyGunner(mc);
		break;
	case Ninja:
		//e = new Ninja(...));
		break;
	case Charger:
		e = new EnemyCharger(mc);
		break;
	case Turret:
		e = new EnemyTurret(mc);
		break;
	case Bomb:
		e = new EnemyBomb(mc);
		break;
	case Bomber: 
		e = new EnemyBomber(mc);
	default:
		break;
	}
	return e;
}

Enemy * EnemyManager::getInactiveEnemy(EnemyType eType)
{
	//Vamos a buscar a ver si hay algun enemigo de el tipo
	list<Enemy*>::iterator it = inactives.begin();
	while (it != inactives.end() && (*it)->getType() != eType)
		it++;
	//Si lo encontramos, lo quitamos de la lista de inactivos
	if (it != inactives.end()) {
		Enemy* e = *it;
		inactives.erase(it);
		return e;
	}
	//Si no devolvemos null
	return nullptr;
}

EnemyManager::~EnemyManager()
{
	for (Enemy* e : actives)
		kill(e);
	for (Enemy* e : inactives)
		PlayState::getInstance()->removeGameObject(e);
}

//Get Singleton instance
EnemyManager * EnemyManager::getInstance()
{
	if (instance == nullptr)
		instance = new EnemyManager();
	return instance;
}

void EnemyManager::update()
{
	for (Enemy* e : actives) {
		e->update();
	}
	if (actBoss1 != nullptr)
	{
		actBoss1->update();
	}
	if (actBoss2 != nullptr)
	{
		actBoss2->update();
	}
}

void EnemyManager::render()
{
	for (Enemy* e : actives) {
		e->render();
	}
	if (actBoss1 != nullptr)
	{
		actBoss1->render();
	}
	if (actBoss2 != nullptr)
	{
		actBoss2->render();
	}
}

void EnemyManager::spawn(int x, int y, EnemyType eType)
{
	//Primero miramos por si hay un enemigo
	Enemy* e = getInactiveEnemy(eType);
	//Si no lo hay creamos una instancia nueva
	if (e == nullptr)
		e = createEnemy(eType);
	//Lo spawneamos y lo añadimos a la lista de activos
	e->spawn(x, y);
	actives.push_back(e);
		
}

void EnemyManager::spawn(Spawner * spawner)
{
	//Primero miramos por si hay un enemigo
	Enemy* e = getInactiveEnemy(spawner->getEnemy());
	//Si no lo hay creamos una instancia nueva
	if (e == nullptr)
		e = createEnemy(spawner->getEnemy());
	//Lo spawneamos y lo añadimos a la lista de activos
	e->spawn(spawner->getX(),spawner->getY(),spawner);
	actives.push_back(e);
}
void EnemyManager::spawnBoss(int x, int y)
{
	actBoss2 = new Boss2(mc, x, y, 128, 128);
	activeBoss = actBoss2;
}
void EnemyManager::spawnBoss2(int x, int y)
{
	actBoss2 = new Boss2(mc, x, y, 128, 128);
	activeBoss = actBoss2;
}
void EnemyManager::ResetInstance()
{
	instance->killAll();
	delete instance; // REM : it works even if the pointer is NULL (does nothing then)
	instance = NULL; // so GetInstance will still work.
}

void EnemyManager::kill(Enemy * enemy)
{
	//Vamos a buscar el enemigo
	list<Enemy*>::iterator it = actives.begin();
	while (it != actives.end() && (*it!= enemy))
		it++;
	//Si lo encontramos, lo quitamos de la lista de activos
	if (it != actives.end()) {
		actives.erase(it);
	}
	//Y lo movemos a la lista de inactivos
	inactives.push_back(enemy);
}

void EnemyManager::killAll()
{
	list<Enemy*>::iterator it;
	while (!actives.empty())
	{
		it = actives.begin();
		if ((*it)->isDead())
			(*it)->onDestroy();
		kill(*it);
	}
	if (activeBoss != nullptr)
		activeBoss->setActive(false);
}

void EnemyManager::init(MainCharacter* mainCharacter)
{
	mc = mainCharacter;
	for (int i = 0; i < nEnemies; i++) {
		for (int j = 0; j < 5; j++) {
			//Creamos n enemigos de cada tipo
			Enemy* e = createEnemy((EnemyType)i);
			if(e!=nullptr)
				inactives.push_back(e);
		}
	}
}
