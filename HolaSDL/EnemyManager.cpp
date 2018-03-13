#include "EnemyManager.h"
#include "Enemy.h"


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
		//e = new Stalker(...));
		break;
	case Gunner:
		//e = new Gunner(...));
		break;
	case Ninja:
		//e = new Ninja(...));
		break;
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
		inactives.remove(e);
}

//Get Singleton instance
EnemyManager * EnemyManager::getInstance()
{
	if (instance = nullptr)
		instance = new EnemyManager();
	return instance;
}

void EnemyManager::update()
{
	for (Enemy* e : actives) {
		e->update();
	}
}

void EnemyManager::render()
{
	for (Enemy* e : actives) {
		e->render();
	}
}

void EnemyManager::spawn(int x, int y, EnemyType eType)
{
	//Primero miramos por si hay un enemigo
	Enemy* e = getInactiveEnemy(eType);
	//Si no lo hay creamos una instancia nueva
	if (e == nullptr)
		createEnemy(eType);
	//Lo spawneamos y lo añadimos a la lista de activos
	e->spawn(x, y);
	actives.push_back(e);
		
}

void EnemyManager::kill(Enemy * enemy)
{
	//Vamos a buscar el enemigo
	list<Enemy*>::iterator it = actives.begin();
	while (it != actives.end() && (*it!= enemy))
		it++;
	//Si lo encontramos, lo quitamos de la lista de activos
	if (it != inactives.end()) {
		actives.erase(it);
	}
	//Y lo movemos a la lista de inactivos
	inactives.push_back(enemy);
}

void EnemyManager::init()
{
	for (int i = 0; i < nEnemies; i++) {
		for (int j = 0; i < 5; i++) {
			//Creamos n enemigos de cada tipo
			inactives.push_back(createEnemy((EnemyType)i));
		}
	}
}
