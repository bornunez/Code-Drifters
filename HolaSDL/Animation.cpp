#include "Animation.h"



Animation::Animation(GameObject* o, int totalFrames, bool loop, float time, int frameWidth, int framwHeight)
{
	gameObject = o;
	this->time = time;
	this->loop = loop;
	this->totalFrames = totalFrames;
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
	if (lastFrame->TimeSinceTimerCreation > time) {
		lastFrame->restart();
		currentFrame++;
		if (currentFrame >= animFrames.size()) {
			currentFrame = animFrames.size()-1;
		}
	}
	animFrames[currentFrame]->render();
}


void Animation::loadAnimation(int firstRow, int lastRow, int col)//Carga animaciones que no varían en tamaño
{
	for (int i = firstRow; i < lastRow; i++) {
		SDL_Rect* aux = new SDL_Rect();
		aux->h = frameH;
		aux->w = frameW;
		aux->x = frameW * firstRow;
		aux->y = frameH * col;
		aux->x = frameW * i;
		addAnimationFrame(aux, gameObject->getTransform()->body);		
	}
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

void Animation::setTime(int tim)//Cambia el tiempo entre frames
{
	time = tim;
}

void Animation::addAnimationFrame(SDL_Rect* srcRect, SDL_Rect destRect)//Añade un frame a la animación
{
	AnimationFrame* aux = new AnimationFrame(gameObject,srcRect,destRect);
	animFrames.push_back(aux);
}
