#include "SkeletonRenderer.h"
#include <algorithm>
#include "Transform.h"
#include "GameObject.h"
#include "Game.h"
#include "Camera.h"
SkeletonRendered::SkeletonRendered(GameObject* o ,SDL_Color color) : RenderComponent(o)
{
}


SkeletonRendered::~SkeletonRendered() {
}

void SkeletonRendered::render() {

	Camera* camera = GameManager::getInstance()->getCamera();
	SDL_Renderer* renderer = Game::getGame()->getRenderer();
	Transform* t = gameObject->getTransform();
	// the rotation angle of the object wrt to
	double angle = Vector2D(0, -1).angle(t->direction);

	// assuming the (0,0) point is the middle of the object, the following are
	// vectors to the corners of its bounding rectangle
	Vector2D lu(-t->body.w / 2, -t->body.h / 2);
	Vector2D ru(t->body.w / 2, -t->body.h / 2);
	Vector2D rb(t->body.w / 2, t->body.h / 2);
	Vector2D lb(-t->body.w / 2, t->body.h / 2);

	//// rotate the corners
	//lu.rotate(angle);
	//ru.rotate(angle);
	//rb.rotate(angle);
	//lb.rotate(angle);

	// the center of the object
	double x = t->body.x + t->body.w / 2 - camera->getTransform()->position.getX();
	double y = t->body.y + t->body.h / 2 - camera->getTransform()->position.getY();

	// draw lines between the corners, after shifting them by (x,y)
	SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
	SDL_RenderDrawLine(renderer, lu.getX() + x, lu.getY() + y, ru.getX() + x,
			ru.getY() + y);
	SDL_RenderDrawLine(renderer, ru.getX() + x, ru.getY() + y, rb.getX() + x,
			rb.getY() + y);
	SDL_RenderDrawLine(renderer, rb.getX() + x, rb.getY() + y, lb.getX() + x,
			lb.getY() + y);
	SDL_RenderDrawLine(renderer, lb.getX() + x, lb.getY() + y, lu.getX() + x,
			lu.getY() + y);

	// draw direction vector
	SDL_SetRenderDrawColor(renderer, 255, 200, 200, 200);
	Vector2D dir = (t->direction) * (t->body.h / 2);
	SDL_RenderDrawLine(renderer, x, y, dir.getX() + x, dir.getY() + y);

	// draw velocity vector
	SDL_SetRenderDrawColor(renderer, 100, 255, 100, 100);

	Vector2D vel = t->velocity;
	double wh = std::min(t->body.h, t->body.h) / 2; // minimum of width an height
	vel = vel * wh / 5; // why 5? i
	SDL_RenderDrawLine(renderer, x, y, vel.getX() + x, vel.getY() + y);

}
