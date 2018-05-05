#include "ParticleAnimation.h"
#include "Game.h"
#include "PlayState.h"
#include "Camera.h"



ParticleAnimation::ParticleAnimation(GameObject * o, Texture * texture, double angle, int fps, SDL_RendererFlip flip, bool loop, double time) : RenderComponent(o)
{
	this->texture = texture;
	this->angle = angle;
	this->fps = fps;
	this->flip = flip;
	this->finish = false;
	this->loop = loop;
	frameW = texture->getFrameWidth() * Game::getGame()->getScale();
	frameH = texture->getFrameHeight() * Game::getGame()->getScale();
	lastFrame = new Timer();
	activeTime = time;
	deactivate = new Timer();
}

ParticleAnimation::~ParticleAnimation()
{
}

void ParticleAnimation::render()
{
	if (loop) {
		deactivate->update();
		if (deactivate->TimeSinceTimerCreation > activeTime) {
			finish = true;
			currentFrame = 0;
			lastFrame->restart();
			gameObject->setActive(false);
			deactivate->restart();
		}
	}
	
	if (!finish) {
		lastFrame->update();

		float auxX = gameObject->getTransform()->position.getX() - PlayState::getInstance()->getCamera()->getTransform()->position.getX();
		float auxY = gameObject->getTransform()->position.getY() - PlayState::getInstance()->getCamera()->getTransform()->position.getY();

		SDL_Rect srcrect = { currentFrame* texture->getFrameWidth(), animationNumber * texture->getFrameHeight(), texture->getFrameWidth(), texture->getFrameHeight() };
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
			
			if (!loop) {
				finish = true;
				gameObject->setActive(false);
			}
			currentFrame = 0;
			lastFrame->restart();
		}
	}
	
}

void ParticleAnimation::setAnimationNumber(Uint32 animNumber)
{
	this->animationNumber = animNumber;
}

void ParticleAnimation::setAngle(float angle)
{
	this->angle = angle;
}

void ParticleAnimation::setFlip(SDL_RendererFlip flip)
{
	this->flip = flip;
}
