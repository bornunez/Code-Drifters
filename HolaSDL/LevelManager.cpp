#include "LevelManager.h"
#include "DungeonGenerator.h"
#include "Room.h"
#include "Managers.h"
#include "Door.h"
#include "Map.h"
#include "PlayState.h"
#include "GameObject.h"
#include"MainCharacter.h"
#include "CoinManager.h"
#include "ItemManager.h"
#include "Message.h"
#include <iostream>
#include <fstream>

LevelManager* LevelManager::instance = nullptr;

LevelManager::LevelManager()
{
	//Ponemos el vector de direcciones
	directions = { {0,-1},{1,0},{0,1},{-1,0} };
}

void LevelManager::ResetInstance()
{
	delete instance;
	instance = nullptr;
}
LevelManager::~LevelManager()
{
	delete dungeon;
}

void LevelManager::onRoomChange(Room* room, Room* prevRoom, Direction dir)
{
	//COSAS QUE PASAN CUANDO CAMBIAS DE SALA AQUI
	//Antes de Spawnear, despawneamos los que hubiera
	Message auxMsg(ROOM_EXIT);
	if(prevRoom != nullptr)
		prevRoom->getMap()->sendMessage(&auxMsg);
	EnemyManager::getInstance()->killAll();
	ItemManager::getInstance()->reset();
	CoinManager::getInstance()->clean();

	//Y ponemos al jugador en la puerta contraria
	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
	if (dir != None) {
		Vector2D entry = room->getMap()->getDoor((Direction)((dir + 2) % 4))->getEntry();
		mc->getTransform()->position.set(entry);
	}

	//stops current music and plays shop one
	if (room->getType() == Shop) {
		switch (level){
		case 0:
		case 1:
			ResourceManager::getInstance()->getMusic(Level1)->stop();
			break;
		case 2:
			ResourceManager::getInstance()->getMusic(Level2)->stop();
		default:
			break;
		}
		ResourceManager::getInstance()->getMusic(Burdel)->play();
	}
	//stops shop music and restarts the current level one
	if (prevRoom != nullptr && prevRoom->getType() == Shop && room->getType() != Shop) {
		ResourceManager::getInstance()->getMusic(Burdel)->stop();
		switch (level) {
		case 0:
		case 1:
			ResourceManager::getInstance()->getMusic(Level1)->play();
			break;
		case 2:
			ResourceManager::getInstance()->getMusic(Level2)->play();
		default:
			break;
		};
	}
	
	//Si la sala es de tipo boss, lo spawneamos
	if (room->getType() == BossRoom)
	{
		GameObject * bossSpawn = room->getMap()->getBossSpawn();
		GameObject * ePoint = room->getMap()->getEntryPoint();
		if (bossSpawn != nullptr)
			EnemyManager::getInstance()->enterBossRoom(bossSpawn->getTransform()->position.getX(), bossSpawn->getTransform()->position.getY(),level);
		if (ePoint != nullptr)
			mc->getTransform()->position.set(ePoint->getTransform()->position);
	}

	mc->getTransform()->velocity.set(0, 0);
	mc->updatePreviousPosition();
	mc->updateBody();
	mc->getHook()->setHookStatus(HookStatus::STOP);
	mc->setMCState(MCState::Idle);

	room->spawn();
	room->setExplored(true);
	if (!getBossRoom()->isExplored()) {
		if (getRoom(Up) && getRoom(Up)->getType() == BossRoom) {
			getRoom(Up)->setExplored(true);
		}
		if (getRoom(Down) && getRoom(Down)->getType() == BossRoom) {
			getRoom(Down)->setExplored(true);
		}
		if (getRoom(Left) && getRoom(Left)->getType() == BossRoom) {
			getRoom(Left)->setExplored(true);
		}
		if (getRoom(Right) && getRoom(Right)->getType() == BossRoom) {
			getRoom(Right)->setExplored(true);
		}
	}
	Message msg(ROOM_ENTER);
	sendMessageCurrent(&msg);
}

LevelManager * LevelManager::getInstance()
{
	if (instance == nullptr)
		instance = new LevelManager();
	return instance;
}

void LevelManager::enterMap()
{
	onRoomChange(getFirstRoom(), nullptr, None);
	//getFirstRoom()->spawn();
	GameObject* ePoint = currentRoom->getMap()->getEntryPoint();
	if (ePoint != nullptr) {
		//Y ponemos al jugador en la puerta contraria
		MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
		mc->getTransform()->velocity.set(0, 0);
		mc->getTransform()->position.set(ePoint->getTransform()->position);
		mc->updatePreviousPosition();
		mc->updateBody();
	}
}

Room * LevelManager::getRoom(int x, int y)
{
	if(x >= 0 && x < dungeon->getLevelWidth() && y >= 0 && y < dungeon->getLevelHeight())
		return dungeon->getRoom(x, y);
	else 
		return nullptr;
}

Room * LevelManager::getRoom(Direction dir)
{
	int auxX = roomX + directions[dir].x;
	int auxY = roomY + directions[dir].y;
	return auxX >= 0 && auxX < dungeon->getLevelWidth() && auxY >= 0 && auxY < dungeon->getLevelHeight() ? getRoom(auxX,auxY ) : nullptr;
	//return getRoom(auxX, auxY);
}

void LevelManager::changeRoom(Room * room)
{
	if (!room->isVoid()) {
		Room* prevRoom = currentRoom;
		currentRoom = room;
		roomX = room->getX(); roomY = room->getY();
		onRoomChange(room,prevRoom, None);
	}
}

void LevelManager::changeRoom(int x, int y)
{
	Room* room = getRoom(x, y);
	if (room != nullptr && !room->isVoid()) {
		Room* prevRoom = currentRoom;
		currentRoom = room;
		roomX = x; roomY = y;
		onRoomChange(room,prevRoom, None);
	}
}

void LevelManager::changeRoom(Direction dir)
{
	bool canMove = getDoor(dir);
	if (canMove) {
		//Pedimos la sala de la direccion
		Room* room = getRoom(dir);
		if (room != nullptr && !room->isVoid()) {
			//Si hay sala, la cambiamos
			Room* prevRoom = currentRoom;
			currentRoom = room;
			roomX += directions[dir].x;
			roomY += directions[dir].y;
			onRoomChange(room,prevRoom, dir);
		}
	}
}

Room * LevelManager::getBossRoom()
{
	Room* r = nullptr;
	bool found = false;
	for (int i = 0;!found && i < dungeon->getLevelHeight(); i++) {
		for (int j = 0; !found && j < dungeon->getLevelWidth(); j++) {
			 r = dungeon->getRoom(j, i);
			 found = r->getType() == BossRoom;	
		}
	}
	return found ? r : nullptr;

}

Room * LevelManager::getShopRoom()
{
	Room* r = nullptr;
	bool found = false;
	for (int i = 0; !found && i < dungeon->getLevelHeight(); i++) {
		for (int j = 0; !found && j < dungeon->getLevelWidth(); j++) {
			r = dungeon->getRoom(j, i);
			found = r->getType() == Shop;
		}
	}
	return found ? r : nullptr;

}


void LevelManager::update()
{
	currentRoom->getMap()->update();
}

void LevelManager::handleEvents(SDL_Event & e)
{
	currentRoom->getMap()->handleEvents(e);
}

void LevelManager::render()
{
	currentRoom->render();
}

void LevelManager::lateRender()
{
	currentRoom->lateRender();
}

bool LevelManager::getDoor(Direction dir)
{
	return currentRoom->getDoor(dir);
}

void LevelManager::init(bool tutorial)
{
	level = 0;
	baseRooms = 6;
	roomsPerLevel = 4;
	newMap();
}

void LevelManager::newMap()
{
	if (level <= 0) {
		dungeon = new DungeonGenerator(4, 4, 7);
		dungeon->CreateMapFromFile();
	}
	else {
		dungeon = new DungeonGenerator(20, 20, baseRooms + (level * roomsPerLevel));
		dungeon->CreateMap();
	}
	firstRoom = dungeon->getFirstRoom();
	currentRoom = firstRoom;
	roomX = currentRoom->getX(); roomY = currentRoom->getY();
	currentRoom->setExplored(true);
	
	//level->getFirstRoom()->addCharacter(mainCharacter);//Se a�ade el personaje a la primera sala
}

void LevelManager::nextLevel()
{
	//Desactiva el Boss del nivel tras matarlo
	if (EnemyManager::getInstance()->getActiveBoss() != nullptr) {
		EnemyManager::getInstance()->getActiveBoss()->setInvincibility(true);
		EnemyManager::getInstance()->getActiveBoss()->getTransform()->overlapCollision.active = false;
	}
	if (level == 0) {
		ofstream ofile;
		ofile.open("..\\levels&tiles\\Tutorial\\tutorial_done");
		if (ofile.is_open()) {
			ofile.close();
		}
	}
	PlayState::getInstance()->getMainCharacter()->addHP(100);
	delete dungeon;
	level++;
	if (level <= maxLevel) {
		if (level == 2) {
			currentLevelType = Lab;
		}
		else if (level == 1) {
			currentLevelType = City;
		}
		newMap();
	}
	else {
		//Ir a los creditos
	}
}

void LevelManager::sendMessageCurrent(Message * msg)
{
	currentRoom->getMap()->sendMessage(msg);
}

void LevelManager::sendMessageAll(Message * msg)
{
	Room* r = nullptr;
	for (int i = 0;i < dungeon->getLevelHeight(); i++) {
		for (int j = 0;j < dungeon->getLevelWidth(); j++) {
			r = dungeon->getRoom(j, i);
			if (r != nullptr && !r->isVoid())
				r->getMap()->sendMessage(msg);
		}
	}
}

