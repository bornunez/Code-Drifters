#pragma once
//#include "checkML.h"
#include <vector>
#include <list>
#include "Boss.h"
#include "Boss2.h"
#include "Boss3.h"

using namespace std;
class Enemy;
class MainCharacter;
class Spawner;

enum EnemyType{Stalker, Gunner, Ninja, Charger, Turret, Bomb, BossBomb, Bomber};
struct EnemyParams {
	int life;
	int speed;
	int meleDmg; int rangedDmg;
	int minDrop; int maxDrop; int healDrop;
	bool hookable;
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
	vector<EnemyParams> eParams = { 
		{100,350,10,0,5,7,33,true},
		{75,100,5,10,7,8,33,true},
		{75,200,15,0,7,8,33,true},
		{200,125,10,0,8,10,33,false},
		{10,100,0,10,8,10,33,false},
		{10,100,0,10,0,0,0,false},
		{10,100,0,10,0,0,0,false},
		{200,150,5,10,7,8,100,true} };
	//Donde van a estal almacenados todos los enemigos del juego
	list<Enemy*> inactives;
	list<Enemy*> actives;

	//Metodo aux para coger un enemigo del vector de inactivos, Coste O(n) con n = numero de enemigos inactivos
	Enemy* createEnemy(EnemyType eType);
	Enemy* getInactiveEnemy(EnemyType eType);
	Boss* actBoss1 = nullptr;
	Boss2* actBoss2 = nullptr;
	Boss3* actBoss3 = nullptr;
	MasterBoss* activeBoss = nullptr;

	MainCharacter* mc;

public:
	~EnemyManager();
	static EnemyManager* getInstance();
	static void ResetInstance();
	void update();
	void render();
	void lateRender();

	EnemyParams getParams(EnemyType type) { return eParams[type]; }

	//Spawnea un tipo de enemigo en unas X, Y dadas
	void spawn(int x, int y, EnemyType eType);
	void spawn(Spawner* spawner);

	void spawnBoss(int x, int y);
	void spawnBoss2(int x, int y);
	void spawnBoss3(int x, int y);
	void enterBossRoom(int x, int y, int level);
	MasterBoss* getActiveBoss() { return activeBoss; }

	//Desactiva un enemigo
	void kill(Enemy* enemy);
	void killAll();
	//Inicializar el Manager. Llamar al principio
	void init(MainCharacter* mainCharacter);
	list<Enemy*> getActiveEnemies() { return actives; };
};

