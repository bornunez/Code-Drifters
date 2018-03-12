#pragma once

#include "ComponentContainer.h"
#include "Transform.h"
class Game;
class Texture;
class PlayState;

class GameObject : public ComponentContainer
{
protected:
	
	Game * game = nullptr;
	Texture * texture = nullptr; //Puntero a la textura
	Transform transform; //Informacion del objeto en el mundo
	bool active = true;
public:

	GameObject();
	GameObject(Texture* tex, Transform t, bool active = true);
	GameObject(Texture* tex, Vector2D position, float bodyHeight, float bodyWidth, bool active = true);
	GameObject(Texture* tex, int x, int y, int bodyWidth, int bodyHeight, bool active = true);
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

