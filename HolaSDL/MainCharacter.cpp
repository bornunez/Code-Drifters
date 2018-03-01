#include "MainCharacter.h"
#include "Game.h"



//Personaje principal

MainCharacter::MainCharacter(Game* game, Transform t) : GameObject(game)
{
	transform.position.setX(t.position.getX());
	transform.position.setY(t.position.getY());
	transform.body.w = t.body.w;
	transform.body.h = t.body.h;
	
}
MainCharacter::MainCharacter(Game* game, int x, int y, int w, int h) : GameObject(game)
{
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;
}

MainCharacter::~MainCharacter()
{
}
void MainCharacter::render(){
	SDL_Rect rect RECT(transform.position.getX(),transform.position.getY(),transform.body.w,transform.body.h);
	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0xff00ffff));
	SDL_RenderFillRect(game->getRenderer(), &rect);
	SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0x000000ff));	
}

//Getters & Setters

void MainCharacter::addCurrentBullets(int num)
{
	currentBullets += num;
	if (currentBullets > maxBullets) {
		currentBullets = maxBullets;
	}
}
int MainCharacter::getCurrentBullets()
{
	return currentBullets;
}
void MainCharacter::setMaxBullets(int bullets)
{
	maxBullets=bullets;
}
float MainCharacter::getMeleeDamage()
{
	return meleeDamage;
}
void MainCharacter::setMeleeDamage(float dmg)
{
	meleeDamage = dmg;
}
void MainCharacter::setMaxVelocity(float vel)
{
	maxVelocity = vel;
}
float MainCharacter::getVelocity()
{
	return velocity;
}
float MainCharacter::getMaxVelocity()
{
	return maxVelocity;
}
float MainCharacter::getHP()
{
	return HP;
}
void MainCharacter::substractHP(int damage)
{
	HP-=damage;
}
int MainCharacter::getCurrentRoomX()
{
	return currentRoomX;
}

int MainCharacter::getCurrentRoomY()
{
	return currentRoomY;
}

void MainCharacter::changeCurrentRoom(int x, int y)
{
	currentRoomX = x;
	currentRoomY = y;
}
