#include "Animation.h"
#include "Game.h"
#include "TileLayer.h"
#include "Tileset.h"
Animation::Animation(Tileset* tileset,  GameObject* o, int tileSize, int offsetx, int offsety, bool loop, float time)
{
	offsetX = offsetx;
	offsetY = offsety;
	frameW = tileSize;
	frameH = tileSize;
	tileSet = tileset;
	gameObject = o;
	this->time = time;
	this->loop = loop;
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
	AnimationFrame* aux = new AnimationFrame(tileSet, gameObject,srcRect,destRect, xOffset, yOffset);
	animFrames.push_back(aux);
}

void Animation::setLayer(TileLayer * lay)//Recibe la layer y la divide para asignar los animationFrame
{
	layer = lay;
	std::vector<std::vector<int>> tileIDs = layer->getTileIDs();
	for (int i = 0; i < layer->getRows(); i++) {
		for (int j = 0; j < layer->getCols(); j++) {
			int tileID = tileIDs[i][j];
			if (tileID > 0) {
				SDL_Rect* srcRect = tileSet->getTileRect(tileID - 1);
				SDL_Rect destRec;
				destRec.x = gameObject->getTransform()->body.x;
				destRec.y = gameObject->getTransform()->body.y;
				destRec.w = frameW;
				destRec.h = frameH;
				addAnimationFrame(srcRect, destRec, offsetX,offsetY);				
			}
		}
	}
}
