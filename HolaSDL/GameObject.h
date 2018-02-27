#pragma once
#include "sdl_includes.h"
#include "ComponentContainer.h"
#include "Texture.h"
#include "Transform.h"

class Game;

class GameObject : public ComponentContainer
{
protected:
	
	Game * game = NULL;
	Texture * texture = NULL; //Puntero a la textura
	Transform transform; //Informacion del objeto en el mundo
	bool active = true;

public:

	GameObject();
	GameObject(Game* game, Texture* tex, Transform t, bool active = true);
	GameObject(Game* game, Texture* tex, Vector2D position, bool active = true);
	~GameObject();

	//Ciclo del Objeto
	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event& e);

	//Gets y sets
	bool isActive() { return active; }
	bool setActive(bool active) { this->active = active; }
	Transform* getTransform() { return &transform; }
	Texture* getTexture() { return texture; }
};

