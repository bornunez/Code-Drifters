#pragma once

#include "ComponentContainer.h"
#include "Transform.h"
#include <map>
class Animation;
class Game;
class Texture;
class PlayState;

class GameObject : public ComponentContainer
{
protected:
	
	Game * game = nullptr;
	PlayState* playState = nullptr;
	Texture * texture = nullptr; //Puntero a la textura
	Transform transform; //Informacion del objeto en el mundo
	Vector2D centerPosition;//Centro del objeto
	Vector2D displayPosition;//Posición respecto a la cámara
	Vector2D displayCenterPosition;//Centro del objeto respecto a la cámara
	

	std::map<const char*, Animation*> animations;//Animaciones que contiene
	Animation* currentAnimation;
	bool active = true;
	bool invincible = false;
public:

	GameObject();
	GameObject(Texture* tex, bool active = true);			//Para las balas
	GameObject(Texture* tex, Transform t, bool active = true);
	GameObject(Texture* tex, Vector2D position, float bodyHeight, float bodyWidth, bool active = true);
	GameObject(Texture* tex, int x, int y, int bodyWidth, int bodyHeight, bool active = true);
	~GameObject();

	//Ciclo del Objeto
	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event& e);

	void updateCenterPosition();
	void updateDisplayPosition();
	void updateDisplayCenterPosition();

	//Gets y sets
	bool isActive() { return active; }
	void setActive(bool active) { this->active = active; }
	Transform* getTransform() { return &transform; }
	Texture* getTexture() { return texture; }
	Vector2D getCenterPos() { return centerPosition; }
	Vector2D getDisplayPos() { return displayPosition; }
	Vector2D getDisplayCenterPos() { return displayCenterPosition; }
	Animation* getCurrentAnimation();
	void changeCurrentAnimation(const char * animName);
	bool getInvincibility() { return invincible; }
	void setInvincibility(bool state) { invincible = state; }
	void setTransform(Transform t) { this->transform = t; }
};

