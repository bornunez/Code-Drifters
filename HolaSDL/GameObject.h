#pragma once
//#include "checkML.h"
#include "ComponentContainer.h"
#include "Transform.h"
#include <vector>
#include <map>
class Animation;
class Game;
class Texture;
class PlayState;

using namespace std;

class GameObject : public ComponentContainer
{
protected:
	
	Game * game = nullptr;
	PlayState* playState = nullptr;
	Texture * texture = nullptr; //Puntero a la textura
	Transform transform; //Informacion del objeto en el mundo
	Vector2D prevPosition; //Posicion antigua
	Vector2D overlapPrevPos;
	Vector2D centerPosition;//Centro del objeto
	Vector2D displayPosition;//Posición respecto a la cámara
	Vector2D displayCenterPosition;//Centro del objeto respecto a la cámara
	int spriteOffsetX=0;
	int spriteOffsetY=0;
	

	std::map<const char*, Animation*> animations;//Animaciones que contiene
	Animation* currentAnimation;

	vector<string> collisionsLayer;

	bool active = true;
	bool invincible = false;
	bool movable = true;
	bool dead = false;
public:

	GameObject();
	GameObject(Texture* tex, bool active = true);			//Para las balas
	GameObject(Texture* tex, Transform t, bool active = true);
	GameObject(Texture* tex, Vector2D position, float bodyHeight, float bodyWidth, bool active = true);
	GameObject(Texture* tex, int x, int y, int bodyWidth, int bodyHeight, bool active = true);
	virtual ~GameObject();

	//Ciclo del Objeto
	virtual void update();
	virtual void render();
	virtual void lateRender();
	virtual void handleEvents(SDL_Event& e);

	void updateCenterPosition();
	void updateDisplayPosition();
	void updateDisplayCenterPosition();
	void updateBody();
	void updateOverlapBody();
	void allUpdates();
	//Gets y sets
	bool isActive() { return active; }
	void setActive(bool active) { this->active = active; }
	Transform* getTransform() { return &transform; }
	Vector2D getPreviousPosition() { return prevPosition; }
	Vector2D getOverlapPrevPos() { return overlapPrevPos; }
	void updatePreviousPosition() {
		prevPosition = transform.position;
		overlapPrevPos.set(transform.overlapCollision.overlapBody.x, transform.overlapCollision.overlapBody.y);
	}

	Texture* getTexture() { return texture; }
	Vector2D getCenterPos() { return centerPosition; }
	Vector2D getDisplayPos() { return displayPosition; }
	Vector2D getDisplayCenterPos() { return displayCenterPosition; }

	Animation* getCurrentAnimation();
	void flipAllAnimations(SDL_RendererFlip flip);
	void changeCurrentAnimation(const char * animName);
	bool getInvincibility() { return invincible; }
	void setInvincibility(bool state) { invincible = state; }
	void setTransform(Transform t) { this->transform = t; }
	bool canMove() { return movable; }
	void setMovable(bool mov) { movable = mov; }
	bool isDead() { return dead; }
	void setDeath(bool b) { dead = b; }

	void setCollisionsLayers(vector<string> colLayer) { collisionsLayer = colLayer; }
	void addCollisionLayer(string colLayer);
	void removeCollisionLayer(string colLayer);
	vector<string> getCollisionsLayers() { return collisionsLayer; }

	void setSpriteOffset(int x, int y) { spriteOffsetX = x; spriteOffsetY = y; }
};

