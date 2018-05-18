#include "SimpleAnimationComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"
#include "Timer.h"

SimpleAnimationComponent::SimpleAnimationComponent(GameObject* o, Texture* texture, double angle, int fps, SDL_RendererFlip flip, bool loop) : RenderComponent(o)
{
	this->texture = texture;
	this->angle = angle;
	this->fps = fps;
	this->flip = flip;
	this->loop = loop;
	this->finish = false;
	frameW = texture->getFrameWidth() * Game::getGame()->getScale();
	frameH = texture->getFrameHeight() * Game::getGame()->getScale();
	lastFrame = new Timer();
}

SimpleAnimationComponent::~SimpleAnimationComponent()
{
	delete lastFrame;
}

void SimpleAnimationComponent::setAnimationNumber(Uint32 animNumber)
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


void SimpleAnimationComponent::render()
{
	if (loop) {
		Uint32 ticks = SDL_GetTicks();

		float auxX = gameObject->getTransform()->position.getX() - PlayState::getInstance()->getCamera()->getTransform()->position.getX();
		float auxY = gameObject->getTransform()->position.getY() - PlayState::getInstance()->getCamera()->getTransform()->position.getY();

		Uint32 sprite = (ticks / fps) % texture->getNumCols();
		SDL_Rect srcrect = { sprite * texture->getFrameWidth(), animationNumber * texture->getFrameHeight(), texture->getFrameWidth(), texture->getFrameHeight() };
		SDL_Rect dstrect = { auxX, auxY , frameW, frameH };

		SDL_Point center;
		center.x = 0;
		center.y = dstrect.h / 2;

		texture->render(dstrect, angle, &center, &srcrect, flip);
	}
	else {
		if(!finish) {
			lastFrame->update();

			float auxX = gameObject->getTransform()->position.getX() - PlayState::getInstance()->getCamera()->getTransform()->position.getX();
			float auxY = gameObject->getTransform()->position.getY() - PlayState::getInstance()->getCamera()->getTransform()->position.getY();

			SDL_Rect srcrect = { currentFrame* texture->getFrameWidth(), animationNumber * texture->getFrameHeight(), texture->getFrameWidth(), texture->getFrameHeight()};
			SDL_Rect dstrect = { auxX, auxY , frameW, frameH };

			SDL_Point center;
			center.x = dstrect.w / 2;
			center.y = dstrect.h / 2;

			texture->render(dstrect, angle, &center, &srcrect, flip);

			if (lastFrame->TimeSinceTimerCreation > 0.05)
			{
				currentFrame++;
				lastFrame->restart();
			}

			if (currentFrame >= texture->getNumCols())
			{
				finish = true;
				currentFrame = 0;
				lastFrame->restart();
			}
		}
	}
}
