#include "SimpleAnimationComponent.h"
#include "GameObject.h"
#include "Transform.h"

SimpleAnimationComponent::SimpleAnimationComponent(GameObject* o, Texture* texture, double angle, int fps, SDL_RendererFlip flip) : RenderComponent(o)
{
	this->texture = texture;
	this->angle = angle;
	this->fps = fps;
	this->flip = flip;
}

void SimpleAnimationComponent::setAnimationNumber(AnimationNumber animNumber)
{
	this->animationNumber = animNumber;
}

void SimpleAnimationComponent::setAngle(float angle)
{
	this->angle = angle;
}

void SimpleAnimationComponent::setFlip(SDL_RendererFlip flip)
{
	this->flip = flip;
}

SimpleAnimationComponent::~SimpleAnimationComponent()
{
}

void SimpleAnimationComponent::render()
{
	Uint32 ticks = SDL_GetTicks();
	
	Uint32 sprite = (ticks / fps) % texture->getNumCols();
	SDL_Rect srcrect = { sprite * texture->getFrameWidth(), animationNumber * texture->getFrameHeight(), texture->getFrameWidth(), texture->getFrameHeight()};
	SDL_Rect dstrect = { gameObject->getTransform()->position.getX(), gameObject->getTransform()->position.getY() , texture->getFrameWidth(), texture->getFrameHeight() };

	texture->render(dstrect, angle, &srcrect);
}
