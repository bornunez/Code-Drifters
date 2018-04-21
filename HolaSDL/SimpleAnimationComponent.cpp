#include "SimpleAnimationComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"

SimpleAnimationComponent::SimpleAnimationComponent(GameObject* o, Texture* texture, double angle, int fps, SDL_RendererFlip flip, bool loop) : RenderComponent(o)
{
	this->texture = texture;
	this->angle = angle;
	this->fps = fps;
	this->flip = flip;
	this->loop = loop;
	this->finish = false;	
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
	if(!finish) {
		Uint32 ticks = SDL_GetTicks();

		float auxX = gameObject->getTransform()->position.getX() - PlayState::getInstance()->getCamera()->getTransform()->position.getX();
		float auxY = gameObject->getTransform()->position.getY() - PlayState::getInstance()->getCamera()->getTransform()->position.getY();

		Uint32 sprite = (ticks / fps) % texture->getNumCols();
		SDL_Rect srcrect = { sprite * texture->getFrameWidth(), animationNumber * texture->getFrameHeight(), texture->getFrameWidth(), texture->getFrameHeight()};
		SDL_Rect dstrect = { auxX, auxY , texture->getFrameWidth() * Game::getGame()->getScale(), texture->getFrameHeight() * Game::getGame()->getScale() };

		texture->render(dstrect, angle, &srcrect);
		if (!loop)
			currentFrame++;

		if (currentFrame >= texture->getNumCols())
			finish = true;
	}
}
