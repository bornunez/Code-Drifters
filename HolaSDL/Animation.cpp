#include "Animation.h"
#include "Game.h"
#include "TileLayer.h"
#include "Tileset.h"
Animation::Animation(string animationName, Tileset* tileset,  GameObject* o, int tileSize, int offsetx, int offsety, bool loop, float time)
{
	offsetX = offsetx;
	offsetY = offsety;
	frameW = tileSize;
	frameH = tileSize;
	tileSet = tileset;
	gameObject = o;
	this->time = time;
	this->loop = loop;
	name = animationName;
	currentFrame = 0;
	lastFrame = new Timer();
}


Animation::~Animation()
{
	delete lastFrame;
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
	animFrames[currentFrame]->render(flip);
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

	
	animFrames[currentFrame]->render(flip);
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

void Animation::addAnimationFrame(SDL_Rect* srcRect, SDL_Rect destRect, int xOffset, int yOffset, int frameWidth, int frameHeight)//Añade un frame a la animación
{	
	AnimationFrame* aux = new AnimationFrame(tileSet, gameObject,srcRect,destRect, xOffset, yOffset, frameWidth, frameHeight);
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
				destRec.w = frameW * Game::getGame()->getScale();
				destRec.h = frameH * Game::getGame()->getScale();
				addAnimationFrame(srcRect, destRec, offsetX,offsetY,frameW,frameH);				
			}
		}
	}
}

void Animation::setFlip(SDL_RendererFlip flip)//Rota el sprite y con él todas las boxes y puntos
{
	this->flip = flip;	
	for (uint i = 0; i < animFrames.size(); i++) {
		vector<std::pair<int,int>> hitboxOffset = animFrames[i]->getHitboxOffset();
		vector<SDL_Rect> hitboxes = animFrames[i]->getHitboxes();
		for (uint j = 0; j < hitboxOffset.size(); j++) {
			std::pair<int, int> aux;
			hitboxOffset[j].first = gameObject->getTransform()->body.w*Game::getGame()->getScale() - (hitboxOffset[j].first + hitboxes[j].w);//Desplaza de forma simétrica en x el punto
			aux = { hitboxOffset[j].first , hitboxOffset[j].second };
			animFrames[i]->setHitboxOffset(j, aux);
		}
		vector<std::pair<int, int>> hurtboxOffset = animFrames[i]->getHurtboxOffset();
		vector<SDL_Rect> hurtboxes = animFrames[i]->getHurtboxes();
		for (uint j = 0; j < hurtboxOffset.size(); j++) {
			std::pair<int, int> aux;
			hurtboxOffset[j].first = gameObject->getTransform()->body.w*Game::getGame()->getScale() - (hurtboxOffset[j].first + hurtboxes[j].w);//Desplaza de forma simétrica en x el punto
			aux = { hurtboxOffset[j].first , hurtboxOffset[j].second };
			animFrames[i]->setHurtboxOffset(j, aux);
		}
		std::pair<int, int> gunPosOffset = animFrames[i]->getGunPosOffset();
		Vector2D gunPos = animFrames[i]->getGunPosition();
		gunPosOffset.first = gameObject->getTransform()->body.w*Game::getGame()->getScale() - (gunPosOffset.first);
		animFrames[i]->setGunPosOffset({ gunPosOffset.first, gunPosOffset.second });
	}
}
