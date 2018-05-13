#pragma once
#include "DungeonGenerator.h"
#include "Room.h"
#include "LevelManager.h"
#include <ctime>
#include <iostream>
#include "ResourceManager.h"
#include "Game.h"
#include "Random.h"
#include "Texture.h"

/*Generador de mazmorras
Descripción del algoritmo:
Se usa una matriz para contener salas cuadradas con cuatro puertas posibles
en las direcciones cardinales, y dos vectores, uno de salas sin procesar y
otra con las salas ya procesadas.

Primero se crea la sala inicial que siempre tiene una puerta abajo, y se
añade al vector de salas sin visitar la sala que estaría debajo de esta.

El bucle principal de la generación de la mazmorra crea las salas pendientes
en el vector de salas sin procesar.
Para crear una sala, comprueba que no existan salas adyacentes a sus 4 direcciones.
Asigna aleatoriamente una de las direcciones posibles, crea su puerta, y mete en la
sala siguiente en el vector de salas sin procesar.
Cuando se crea una sala se decide aleatoriamente cuántas puertas de salida tendrá.

El bucle principal se ejecuta hasta que el vector de salas sin procesar se vacíe y
se hayan creado el número máximo de salas.

Una vez creada la estructura, se ejecuta un método que "cierra" las puertas que se
han quedado abiertas y no tienen una sala adyacente.
Después se buscan las salas que solo tienen una puerta (callejones sin salida), y
se asignan a estas siempre un boss, una tienda, y tesoros.

Si llega a haber un caso en el caso no hay suficientes callejones sin salida
porque se ha creado un mapa circular, entonces se vuelve a generar otra estructura distinta
para evitar errores.

La clase Room contiene su textura correspondiente, que carga dependiendo de las puertas
que estén abiertas.
*/

using namespace std;

DungeonGenerator::DungeonGenerator(int mapWidth, int mapHeight, int maxRooms) : 
	mapWidth_(mapWidth), mapHeight_(mapHeight),maxRooms_(maxRooms)
{
	loadTexts();
}

DungeonGenerator::~DungeonGenerator()
{
	//Revisar
	for (int i = 0; i < mapHeight_; i++) {
		Dungeon_[i].resize(mapWidth_);
		for (int j = 0; j < mapWidth_; j++) {
			delete Dungeon_[i][j];
		}
	}

	Dungeon_.clear();

	delete randText.texture;
	delete levelText.texture;
	delete loadText.texture;
	delete neonFont;
}

void DungeonGenerator::CreateMap()//Genera una estructura, "cierra" las puertas abiertas, si la mazmorra es válida entonces asigna las salas especiales
{
	vector<Room*> deadEnds_;
	do {
		ClearMap();
		GenerateDungeon();
		FixDoors();//Cierra las puertas que se han quedado abiertas sin salas contiguas
		deadEnds_ = FindDeadEnds();
	} while (deadEnds_.size() < 3);//Si se crea un mapa circular no valido, entonces se genera otro mapa
	CreateSpecialRooms();
	load();
}
Room * DungeonGenerator::getRoom(int x, int y)
{
	return Dungeon_[y][x];
}
Room * DungeonGenerator::getFirstRoom()
{
	return visitedRooms_[0];
}
//----------------------------------------------------------------------------------------------------------------
void DungeonGenerator::ClearMap()//Reinicia los valores de los vectores y de la mazmorra
{
	visitedRooms_.clear();
	unvisitedRooms_.clear();
	Dungeon_.clear();
	roomsLeft_ = maxRooms_;
	Dungeon_.resize(mapHeight_);
	for (int i = 0; i < mapHeight_; i++) {
		Dungeon_[i].resize(mapWidth_);
		for (int j = 0; j < mapWidth_; j++) {
			Dungeon_[i][j] = new Room();
			Dungeon_[i][j]->setX(j);
			Dungeon_[i][j]->setY(i);
			Dungeon_[i][j]->setAllDoors(false);
			Dungeon_[i][j]->setType(Normal);
		}
	}
}
void DungeonGenerator::GenerateDungeon()//Crea la estructura de la mazmorra
{

	AddFirstRoom();//Crea la sala principal
	int i = 0;
	while (unvisitedRooms_.size()>0 && roomsLeft_ > 0)//Va creando salas hasta que no quedan más por procesar
	{
		int maxExitRooms = 0;//Define el número máximo de puertas de salida que podrá tener una sala

		if (roomsLeft_>2) {
			maxExitRooms = 3;
		}
		else if (roomsLeft_>1) {
			maxExitRooms = 2;
		}
		else if (roomsLeft_>0) {
			maxExitRooms = 1;
		}
		int rnd = rand() % (maxExitRooms);//Define si se va a crear una sala de 1,2 o 3 salidas
		if (maxExitRooms>0) {
			if (rnd == 0) {//Crea 1 salida
				CreateRoom(unvisitedRooms_[0]->getX(), unvisitedRooms_[0]->getY());//Crea la primera sala del vector de salas sin procesar
				roomsLeft_--;
			}
			else if (rnd == 1) {//Crea 2 salidas
				CreateRoom(unvisitedRooms_[0]->getX(), unvisitedRooms_[0]->getY());//Crea la primera sala del vector de salas sin procesar
				CreateRoom(unvisitedRooms_[0]->getX(), unvisitedRooms_[0]->getY());//Crea la primera sala del vector de salas sin procesar
				roomsLeft_--;
			}
			else if (rnd == 2) {//Crea 3 salidas
				CreateRoom(unvisitedRooms_[0]->getX(), unvisitedRooms_[0]->getY());//Crea la primera sala del vector de salas sin procesar
				CreateRoom(unvisitedRooms_[0]->getX(), unvisitedRooms_[0]->getY());//Crea la primera sala del vector de salas sin procesar
				CreateRoom(unvisitedRooms_[0]->getX(), unvisitedRooms_[0]->getY());//Crea la primera sala del vector de salas sin procesar
				roomsLeft_--;
			}
		}

		Dungeon_[unvisitedRooms_[0]->getY()][unvisitedRooms_[0]->getX()]->setVisited(true);
		visitedRooms_.push_back(Dungeon_[unvisitedRooms_[0]->getY()][unvisitedRooms_[0]->getX()]);
		unvisitedRooms_.erase(unvisitedRooms_.begin());//Borra la sala actual de las salas sin visitar
		i++;
		system("cls");
		std::cout << "Creating rooms: [ " << i << " / " << maxRooms_ << " ]" << endl;
		RenderProgresBar(i, maxRooms_, "Creating Rooms...");
	}
	
}
void DungeonGenerator::AddFirstRoom()//Crea la sala inicial de la mazmora
{
	int midWidth = round(mapWidth_ / 2);
	int midHeight = round(mapHeight_ / 2);
	Dungeon_[midHeight][midWidth]->setVisited(true);//Crea la primera sala en la mitad de la matriz
	visitedRooms_.push_back(Dungeon_[midHeight][midWidth]);
	visitedRooms_[0]->setType(First);
	unvisitedRooms_.push_back(Dungeon_[midHeight + 1][midWidth]);//Añade la sala de abajo al vector de salas sin visitar
	Dungeon_[midHeight][midWidth]->setDoor(Down,true);
	SetEntryDoor(midWidth, midHeight + 1, "Up");
}
void DungeonGenerator::FixDoors()//"Cierra" las puertas que se han quedado abiertas y no tienen salas contiguas
{
	for (int i = 0; i<visitedRooms_.size(); i++) {
		int x = visitedRooms_[i]->getX();
		int y = visitedRooms_[i]->getY();
		if (CellInsideBounds(x + 1, y) && AvailableCell(x + 1, y)) {//Si no hay celda a la derecha dentro de los límites del mapa
			Dungeon_[y][x]->setDoor(Right, false);
			Dungeon_[y][x + 1]->setDoor(Left,false);
		}
		if (CellInsideBounds(x - 1, y) && AvailableCell(x - 1, y)) {//Si no hay celda a la izquierda dentro de los límites del mapa
			Dungeon_[y][x]->setDoor(Left,false);
			Dungeon_[y][x - 1]->setDoor(Right,false);
		}
		if (CellInsideBounds(x, y + 1) && AvailableCell(x, y + 1)) {//Si no hay celda abajo dentro de los límites del mapa
			Dungeon_[y][x]->setDoor(Down,false);
			Dungeon_[y + 1][x]->setDoor(Up,false);
		}
		if (CellInsideBounds(x, y - 1) && AvailableCell(x, y - 1)) {//Si no hay celda arriba dentro de los límites del mapa
			Dungeon_[y][x]->setDoor(Up,false);
			Dungeon_[y - 1][x]->setDoor(Down,false);
		}
	}
}
void DungeonGenerator::CreateSpecialRooms()//Asigna las salas especiales a las salas con una sola puerta
{
	vector<Room*> deadEnds_ = FindDeadEnds();
	int deadEndsnum = deadEnds_.size();
	int bossRooms = 1;
	int shopRooms = 1;
	int chestRooms = round(deadEndsnum / 2);//La mitad de las salas restntes tienen tesoro
	int rnd = rand() % deadEnds_.size();
	deadEnds_[rnd]->setType(BossRoom);
	deadEnds_.erase(deadEnds_.begin() + rnd);
	rnd = rand() % deadEnds_.size();
	deadEnds_[rnd]->setType(Shop);
	deadEnds_.erase(deadEnds_.begin() + rnd);
	for (int i = 0; i < chestRooms; i++) {
		rnd = rand() % deadEnds_.size();
		deadEnds_[rnd]->setType(Chest);
		deadEnds_.erase(deadEnds_.begin() + rnd);
	}
}
void DungeonGenerator::CreateRoom(int x, int y)//Crea una sala dada su posición
{
	vector<string> posibleDirections_ = CheckDirections(x, y);//Crea una lista de direcciones posibles
	string direction = "";
	if (posibleDirections_.size() > 0) {
		int rnd = rand() % posibleDirections_.size();//Selecciona una dirección aleatoriamente
		direction = posibleDirections_[rnd];
	}
	SetRoomDirections(posibleDirections_, direction, x, y);//Añade la sala contigua a las salas sin visitar
}
//-----------------------------------------------------------------------------------------------------------------
void DungeonGenerator::UnvisitedRoomToQueue(vector<string> posibleDirections_, string direction, int x, int y) {//Añade la sala al vector de salas sin visitar
	vector<string>::iterator it = find(posibleDirections_.begin(), posibleDirections_.end(), direction);//Quita la propia dirección del vector de direcciones disponibles
	posibleDirections_.erase(it);
	vector<Room*>::iterator itU = find(unvisitedRooms_.begin(), unvisitedRooms_.end(), Dungeon_[y][x]);
	vector<Room*>::iterator itV = find(visitedRooms_.begin(), visitedRooms_.end(), Dungeon_[y][x]);
	if (itU == unvisitedRooms_.end() && itV == visitedRooms_.end()) {//Solo la añade si no está ya en algún vector
		unvisitedRooms_.push_back(Dungeon_[y][x]); // Añade la sala de arriba a las salas sin visitar
	}
}
void DungeonGenerator::SetEntryDoor(int x, int y, string direction)//Se usa para asignar la puerta de entrada
{
	if (direction == "Up") {
		Dungeon_[y][x]->setDoor(Up, true);
	}
	else if (direction == "Down") {
		Dungeon_[y][x]->setDoor(Down, true);
	}
	else if (direction == "Right") {
		Dungeon_[y][x]->setDoor(Right, true);
	}
	else if (direction == "Left") {
		Dungeon_[y][x]->setDoor(Left, true);
	}
}
vector<Room*> DungeonGenerator::FindDeadEnds()//Busca las salas que solo tienen una puerta, "salas sin salida"
{
	vector<Room*> deadEnds_;
	//Empieza en el 1 para saltarse la sala inicial
	for (int i = 1; i< visitedRooms_.size(); i++) {
		int doorCount = 0;
		if (visitedRooms_[i]->getDoor(Up)) {
			doorCount++;
		}
		if (visitedRooms_[i]->getDoor(Down)) {
			doorCount++;
		}
		if (visitedRooms_[i]->getDoor(Right)) {
			doorCount++;
		}
		if (visitedRooms_[i]->getDoor(Left)) {
			doorCount++;
		}
		if (doorCount == 1) {
			deadEnds_.push_back(visitedRooms_[i]);
		}
	}
	return deadEnds_;
}
void DungeonGenerator::SetRoomDirections(vector<string> posibleDirections_, string direction, int x, int y)//"Abre" las puertas la sala según las direcciones
{
	if (direction == "Up")
	{
		Dungeon_[y][x]->setDoor(Up, true);
		SetEntryDoor(x, y - 1, "Down");//Asigna la puerta de entrada de la sala de arriba	
		UnvisitedRoomToQueue(posibleDirections_, direction, x, y - 1);
	}
	else if (direction == "Down")
	{
		Dungeon_[y][x]->setDoor(Down, true);
		SetEntryDoor(x, y + 1, "Up");
		UnvisitedRoomToQueue(posibleDirections_, direction, x, y + 1);
	}
	else if (direction == "Right")
	{
		Dungeon_[y][x]->setDoor(Right, true);
		SetEntryDoor(x + 1, y, "Left");
		UnvisitedRoomToQueue(posibleDirections_, direction, x + 1, y);
	}
	else if (direction == "Left")
	{
		Dungeon_[y][x]->setDoor(Left, true);
		SetEntryDoor(x - 1, y, "Right");
		UnvisitedRoomToQueue(posibleDirections_, direction, x - 1, y);
	}
}
vector<string> DungeonGenerator::CheckDirections(int x, int y)//Comprueba las direcciones en las que es posible crear otra sala
{
	vector<string> posibleDirections_;
	posibleDirections_.clear();
	if (AvailableCell(x, y - 1))//Mira si hay sala arriba
	{
		posibleDirections_.push_back("Up");
	}
	if (AvailableCell(x, y + 1))//Mira si hay sala abajo
	{
		posibleDirections_.push_back("Down");
	}
	if (AvailableCell(x + 1, y))//Mira si hay sala a la derecha
	{
		posibleDirections_.push_back("Right");
	}
	if (AvailableCell(x - 1, y))//Mira si hay sala a la izquierda
	{
		posibleDirections_.push_back("Left");
	}
	return posibleDirections_;
}

void DungeonGenerator::load() {//Cada sala carga su textura correspondiente
	//for (int i = 0; i < visitedRooms_.size(); i++)
	int i = 0;
	for(auto & vr : visitedRooms_)
	{
		vr->load();
		system("cls");
		cout << "Loading rooms: [ " << i << " / " << maxRooms_ << " ]" << endl;
		RenderProgresBar(i, maxRooms_, "Loading Rooms...");
		i++;
	}
}
bool DungeonGenerator::AvailableCell(int x, int y)//Determina si la celda está disponible
{
	if (CellInsideBounds(x, y) && !Dungeon_[y][x]->getVisited())
	{
		return true;
	}
	else return false;
}


void DungeonGenerator::loadTexts()
{
	int scale = 1;
	Game* g = Game::getGame();
	ResourceManager* re = ResourceManager::getInstance();
	randText.texture = new Texture(g->getRenderer());
	levelText.texture = new Texture(g->getRenderer());
	loadText.texture = new Texture(g->getRenderer());

	neonFont = new Font("..\\images\\Polentical Neon Bold.ttf", 50);
	//Cargamos las texturas
	loadbar.borderTex = re->getTexture(LoadbarBarra);
	loadbar.barTex = re->getTexture(LoadbarBarra);
	loadbar.BottomTex = re->getTexture(LoadBarFondo);
	loadbar.backGroundTex = re->getTexture(LoadingScreenBG);
	randText.texture->loadFromText(Random::fraseAleatoria(), *neonFont, { COLOR(0xff00ffff) });
	levelText.texture->loadFromText("Level " + to_string(LevelManager::getInstance()->getLevelNumber()), *neonFont, { COLOR(0xff00ffff) });
	//"Level " + to_string(LevelManager::getInstance()->getLevelNumber())

	//Ajustamos las posiciones
	loadbar.currentSrc.x = loadbar.currentSrc.y = 0;
	loadbar.currentSrc.w = loadbar.borderTex->getWidth();
	loadbar.currentSrc.h = loadbar.borderTex->getHeight();

	//Todas las texturas comparten el mismo dst rect
	loadbar.backGroundDst.w = loadbar.backGroundTex->getWidth() * g->getScale() * scale;
	loadbar.backGroundDst.h = loadbar.backGroundTex->getHeight() * g->getScale() * scale;

	loadbar.dst.w = loadbar.currDst.w = loadbar.currentSrc.w * g->getScale() * scale;
	loadbar.dst.h = loadbar.currDst.h = loadbar.currentSrc.h * g->getScale() * scale;

	//Situaremos la barra en mitad de la pantalla, y el texto en el cuarto superior
	randText.dest.w = randText.texture->getWidth() * 0.6; randText.dest.h = randText.texture->getHeight() * 0.6;
	randText.dest.x = (g->getWinW() - randText.dest.w) / 2;
	randText.dest.y = g->getWinH() - (g->getWinH() - randText.dest.h) / 8;

	levelText.dest.w = levelText.texture->getWidth();  levelText.dest.h = levelText.texture->getHeight();
	levelText.dest.x = (g->getWinW() - levelText.dest.w) / 2; levelText.dest.y = (g->getWinH() - levelText.dest.h) / 4;


	loadbar.backGroundDst.x = (g->getWinW() - loadbar.backGroundDst.w) / 2;
	loadbar.backGroundDst.y = (g->getWinH() - loadbar.backGroundDst.h) / 2;

	loadbar.dst.x = loadbar.currDst.x = (g->getWinW() - loadbar.dst.w) / 2;
	loadbar.dst.y = loadbar.currDst.y = (g->getWinH() - loadbar.dst.h) / 2;
}

void DungeonGenerator::RenderProgresBar(int current, int max, string text)
{
	Game* g = Game::getGame();
	SDL_Renderer* r = g->getRenderer();
	SDL_RenderClear(r);
	loadbar.currentSrc.w = loadbar.barTex->getWidth() * ((float)current / (float)max);
	loadbar.currDst.w = loadbar.dst.w * ((float)current / (float)max);

	loadbar.BottomTex->render(loadbar.dst);
	loadbar.barTex->render(loadbar.currDst, &loadbar.currentSrc);
	loadbar.backGroundTex->render(loadbar.backGroundDst);

	//TEXTS
	loadText.texture->loadFromText(text, *neonFont, { COLOR(0x7e7effff) });
	loadText.dest.w = loadText.texture->getWidth(); loadText.dest.h = loadText.texture->getHeight();
	loadText.dest.x = (g->getWinW() - loadText.dest.w) / 2;
	loadText.dest.y = ((g->getWinW() - loadText.dest.h) / 2);
	
	loadText.texture->render(loadText.dest);
	randText.texture->render(randText.dest);
	levelText.texture->render(levelText.dest);


	SDL_RenderPresent(r);
}


bool DungeonGenerator::CellInsideBounds(int x, int y)//Determina si la posición dada se encuentra dentro de la matriz del mapa
{
	if (x < 0 || x >= mapWidth_ || y<0 || y >= mapHeight_)
	{
		return false;
	}
	else
	{
		return true;
	}
}
