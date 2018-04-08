#pragma once
#include <vector>
#include <list>

using namespace std;
class Enemy;
class MainCharacter;
class Spawner;

enum EnemyType{Stalker, Gunner, Ninja, Charger, Turret};
struct EnemyParams {
	int life;
	int speed;
	int meleDmg; int rangedDmg;
	int minDrop; int maxDrop;
};

class EnemyManager
{
private:
	//const int nEnemies = Ninja - Stalker;
	const int nEnemies = 1;
	//Singleton things
	EnemyManager();
	static EnemyManager* instance;
	//Donde van a estar los datos por defecto de los enemigos (Lo suyo seria leerlo de un XML )
	vector<EnemyParams> eParams = { {100,350,10,0,5,7},{75,10,5,10,7,8},{75,200,15,0,7,8},{10,100,10,0,8,10},{ 10,100,0,10,8,10 } };
	//Donde van a estal almacenados todos los enemigos del juego
	list<Enemy*> inactives;
	list<Enemy*> actives;

	//Metodo aux para coger un enemigo del vector de inactivos, Coste O(n) con n = numero de enemigos inactivos
	Enemy* createEnemy(EnemyType eType);
	Enemy* getInactiveEnemy(EnemyType eType);

	MainCharacter* mc;

public:
	~EnemyManager();
	static EnemyManager* getInstance();
	void update();
	void render();

	EnemyParams getParams(EnemyType type) { return eParams[type]; }

	//Spawnea un tipo de enemigo en unas X, Y dadas
	void spawn(int x, int y, EnemyType eType);
	void spawn(Spawner* spawner);
	//Desactiva un enemigo
	void kill(Enemy* enemy);
	void killAll();
	//Inicializar el Manager. Llamar al principio
	void init(MainCharacter* mainCharacter);
	list<Enemy*> getActiveEnemies() { return actives; };
};

