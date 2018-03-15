#include "Animation.h"
#include "Game.h"


Animation::Animation(GameObject* o, bool loop, float time, int frameWidth, int framwHeight)
{
	gameObject = o;
	this->time = time;
	this->loop = loop;
	frameW = frameWidth;
	frameH = framwHeight;
	currentFrame = 0;
	lastFrame = new Timer();
}


Animation::~Animation()
{
}

void Animation::loopedAnimation()//Al final de la ejecución de un ciclo se vuelve al primer frame
{
	
	if (lastFrame->TimeSinceTimerCreation > time) {
		lastFrame->restart();
		currentFrame++;
		if (currentFrame >= animFrames.size()) {
			currentFrame = 0;
		}
	}
	animFrames[currentFrame]->render();
}

void Animation::normalAnimation()//El último frame se mantiene
{
	if (!finish) {

		if (lastFrame->TimeSinceTimerCreation > time) {
			lastFrame->restart();
			currentFrame++;
			if (currentFrame >= animFrames.size()) {
				finish = true;
				currentFrame = 0;
			}
		}
	}

	
	animFrames[currentFrame]->render();
}


void Animation::loadAnimation(int firstCol, int lastCol, int row, int xOffset, int yOffset)//Carga animaciones que no varían en tamaño
{
	for (int i = firstCol; i < lastCol; i++) {
		SDL_Rect* aux = new SDL_Rect();
		aux->h = frameH;
		aux->w = frameW;
		aux->x = frameW * firstCol;
		aux->y = frameH * row;
		aux->x = frameW * i;
		SDL_Rect destRec;
		destRec.x = gameObject->getTransform()->body.x + xOffset;
		destRec.y = gameObject->getTransform()->body.y + yOffset;
		destRec.w = frameW * Game::getGame()->getScale();
		destRec.h = frameH * Game::getGame()->getScale();
		addAnimationFrame(aux, destRec, xOffset, yOffset);

	}
}
//Carga frames individuales, se usa cuando tienen tamaños distintos
void Animation::loadAnimationFrame(int frameIndex, int srcRow, int srcCol, int frameWidth, int frameHeight, SDL_Rect destRect) {
	SDL_Rect* aux = new SDL_Rect();
	aux->h = frameHeight;
	aux->w = frameWidth;
	aux->x = frameWidth * srcRow;
	aux->y = frameHeight * srcCol;
	addAnimationFrame(aux, destRect);
}

void Animation::runAnimation()//Ejecuta las animaciones dependiendo de si es loop o no
{
	lastFrame->update();
	if (loop) {
		loopedAnimation();
	}
	else {
		normalAnimation();
	}
}

void Animation::startAnimation()
{
	finish = false;
	currentFrame = 0;
}

bool Animation::isFinished()//Determina si la animación ha terminado
{
	return finish;
}

void Animation::setTime(int tim)//Cambia el tiempo entre frames
{
	time = tim;
}

void Animation::addAnimationFrame(SDL_Rect* srcRect, SDL_Rect destRect, int xOffset, int yOffset)//Añade un frame a la animación
{	
	AnimationFrame* aux = new AnimationFrame(gameObject,srcRect,destRect, xOffset, yOffset);
	animFrames.push_back(aux);
}
