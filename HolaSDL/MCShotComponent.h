#pragma once
//#include "checkML.h"
#include "InputComponent.h"
#include "Vector2D.h"
#include "Timer.h"

class BulletManager;
class MainCharacter;

class MCShotComponent : public InputComponent
{
private:
	Vector2D aux;
	MainCharacter * mc;
	BulletManager* bulletManager;			//Puntero a BulletManager necesario para enviar mensaje
public:
	MCShotComponent(MainCharacter * o);
	void handleEvents(SDL_Event & e);
	void receiveMessage(std::string msg) {};
	virtual ~MCShotComponent();

};