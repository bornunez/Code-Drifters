#include "CollisionsManager.h"
#include "Managers.h"
#include "Room.h"
#include "Map.h"
#include "TileLayer.h"
#include "CollisionHandler.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "Enemy.h"
#include "PlayState.h"

CollisionsManager* CollisionsManager::instance = nullptr;

CollisionsManager::CollisionsManager()
{


}

CollisionsManager::~CollisionsManager()
{
}

CollisionsManager * CollisionsManager::getInstance()
{
	if (instance == nullptr)
		instance = new CollisionsManager();
	return instance;
}

void CollisionsManager::handleInput(const SDL_Event & event)
{
}

void CollisionsManager::update()
{
	//COLISIONES DEL PLAYER



	//COLISIONES DE LAS BALAS
	bulletCollisions();


	//COLISIONES DE LOS ENEMIGOS


}

void CollisionsManager::render()
{
}

void CollisionsManager::bulletCollisions()
{
	//Colisionamos
	Room* currRoom = LevelManager::getInstance()->getCurrentRoom();
	vector<string>::iterator it;
	vector<string> collisionsLayer = { "Paredes" };
	vector<Bullet*> bullets = BulletManager::getInstance()->getBullets();

	//Colisionamos todas las balas que esten activas
	for (Bullet* b : bullets) {
		if (b->isActive()) {
			Transform* t = b->getTransform();

			//COLISION CON ENEMIGOS
			bool hit = false;
			switch (b->getType())
			{
			case (BulletType::MCBullet):
			{
				list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();
				for (GameObject* e : enemies) {//Itera la lista de enemigos activos
					if (!e->getInvincibility()) {//Solo puede atacar si son vulnerables
						vector<SDL_Rect> enemyHurtboxes = e->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
						SDL_Rect hitbox = t->body;
						uint i = 0;
						while (!hit && i < enemyHurtboxes.size()) {//Itera sobre las hurtboxes del enemigo
							if (CollisionHandler::RectCollide(enemyHurtboxes[i], hitbox)) {//Comprueba la colisión de las hitboxes de las espada con las hurtboxes del enemigo
								hit = true;
								//Mandar mensaje de collision bala / enemigo
							}
							i++;
						}
					}
				}
				break;
			}
			case BulletType::GunnerBullet:
			{
				//Colisionamos la bala con las hurtboxes del player
				MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
				vector<SDL_Rect> hurtBoxes = mc->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
				SDL_Rect hitbox = t->body;
				int i = 0;
				while (!hit && i< hurtBoxes.size())
				{
					if (!mc->getInvincibility()) {
						if (CollisionHandler::RectCollide(hurtBoxes[i], hitbox)) {//Comprueba la colisión de las hitboxes de las espada con las hurtboxes del enemigo
							hit = true;
							//Mandar mensaje de collision bala / player
						}
						i++;
					}
				}
			}
			default:
				break;
			}
			bool collision = false;
			//COLISION CON PAREDES
			for (it = collisionsLayer.begin(); it != collisionsLayer.end() && !collision; it++) {
				TileLayer* tl = static_cast<TileLayer*>(currRoom->getMap()->GetLayer(*it));
				if (tl != nullptr) {
					if (CollisionHandler::Collide(t, tl)) {
						collision = true;
					}
				}
			}
			if (collision || hit)
				b->setActive(false);
		}
	}
}

void CollisionsManager::playerCollisions()
{
}

void CollisionsManager::enemyCollisions()
{
}

