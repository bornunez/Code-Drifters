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
#include "ItemManager.h"
#include "ItemObject.h"
#include "Transform.h"

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
	playerCollisions();


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

			bool hit = false;
			switch (b->getType())
			{
			case (BulletType::MCBullet):
			{
				//COLISION CON ENEMIGOS
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
								//Habria que cambiar el 1000 por el tiempo del arma
								MCBulletStun msg(2.5);
								e->sendMessage(&msg);
							}
							i++;
						}
					}
				}
				break;
			}
			//COLISION CON JUGADOR
			case BulletType::GunnerBullet:
			{
				//Colisionamos la bala con las hurtboxes del player
				MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
				vector<SDL_Rect> hurtBoxes = mc->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
				SDL_Rect hitbox = t->body;
				int i = 0;
				while (!hit && i < hurtBoxes.size())
				{
					if (!mc->getInvincibility()) {
						if (CollisionHandler::RectCollide(hurtBoxes[i], hitbox)) {//Comprueba la colisión de las hitboxes de las espada con las hurtboxes del enemigo
							hit = true;
							//Mandar mensaje de collision bala / player
							Message msg(ENEMY_BULLET_COLLISION);
							mc->sendMessage(&msg);
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
	vector<ItemObject*> items = ItemManager::getInstance()->getItems();
	//Colisionamos la bala con las hurtboxes del player
	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
	for (ItemObject* item : items) {
		if (item->isActive() && CollisionHandler::RectCollide(mc->getTransform()->body, item->getTransform()->body)) {
			//Mandar mensaje a mc
			ItemManager::getInstance()->PickItem(item);
		}
	}

	////Colision jugador con enemigos activos, sin hurt

	//list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();
	//MainCharacter* mc = PlayState::getInstance()->getMainCharacter();

	//for (Enemy* enemy : enemies)
	//{
	//	if (CollisionHandler::RectCollide(mc->getTransform()->body, enemy->getTransform()->body))
	//		//Si colisiona con un enemigo no se mueve
	//}

}

void CollisionsManager::enemyCollisions()
{

}

void layerCollisions(GameObject* o) {

	Transform* t = o->getTransform();
	vector<string> collisionsLayer = o->getCollisionsLayers();

	//Movemos al personaje y a su body
	t->body.x = t->position.getX(); t->body.y = t->position.getY();

	vector<SDL_Rect> rects = { t->body, t->body };
	vector<bool> collisions = { false,false };
	//Colisionamos
	Room* currRoom = LevelManager::getInstance()->getCurrentRoom();
	bool collisionX = false;
	bool collisionY = false;
	vector<string>::iterator it;
	for (it = collisionsLayer.begin(); it != collisionsLayer.end() && (!collisionX || !collisionY); it++) {
		TileLayer* tl = static_cast<TileLayer*>(currRoom->getMap()->GetLayer(*it));
		if (tl != nullptr) {
			collisions = CollisionHandler::Collide(rects, tl);
			collisionX = collisions[0] || collisionX;
			collisionY = collisions[1] || collisionY;
		}
	}
	if (collisionX || collisionY) {
		//Si hay colision, cogemos la antigua posicion
		Vector2D prevPosition = o->getPreviousPosition();
		if (collisionX) {
			t->position.setX(prevPosition.getX());
		}
		else{
			t->position.setY(prevPosition.getY());
		}
		//Finalmente lo notificamos
		Message msg(HIT_WALL);
		o->sendMessage(&msg);
	}
}
