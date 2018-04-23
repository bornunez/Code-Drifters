#include "Minimap.h"
#include "Game.h"
#include "PlayState.h"
#include "Managers.h"
#include "DungeonGenerator.h"
#include "Room.h"

void Minimap::drawDoors(SDL_Rect rect, Room* room)
{
	SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0x0000ffff));//Dibujaremos en verde
	int cx = rect.x + rect.w / 2;
	int cy = rect.y + rect.h / 2; //El centro del objeto
	if (room->getDoor(Down))
		SDL_RenderDrawLine(Game::getGame()->getRenderer(), cx, cy, cx, cy + rect.h / 2);
	if (room->getDoor(Up))
		SDL_RenderDrawLine(Game::getGame()->getRenderer(), cx, cy, cx, cy - rect.h / 2);
	if (room->getDoor(Right))
		SDL_RenderDrawLine(Game::getGame()->getRenderer(), cx, cy, cx + rect.w /2, cy);
	if (room->getDoor(Left))
		SDL_RenderDrawLine(Game::getGame()->getRenderer(), cx, cy, cx - rect.w / 2, cy);
}

Minimap::Minimap(int w, int h, int rW, int rH) : width(w),height(h),rWidth(rW),rHeight(rH)
{
}

Minimap::~Minimap()
{
}

void Minimap::render()
{
	//A partir de donde podemos dibujar
	int winW = Game::getGame()->getWinW();
	int winH = Game::getGame()->getWinH();

	//Calculamos el medio de la "ventana"
	int centerX = winW - width / 2;
	int centerY = height / 2;

	//Vamos a centrar nuestra sala en el medio
	int currX = LevelManager::getInstance()->getCurrentRoom()->getX();
	int currY = LevelManager::getInstance()->getCurrentRoom()->getY();



	DungeonGenerator* level = LevelManager::getInstance()->getLevel();
	SDL_Rect destRect; // Cuadrado donde pintaremos la sala
	destRect.h = rHeight; destRect.w = rWidth;
	SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0xff00ffff));//Dibujaremos en verde

	//Pintamos la sala en el centor, a partir de ahi, las visitadas las pondremos en verde, las demas no se ven
	for (size_t i = 0; i < level->getLevelHeight(); i++)
	{
		for (size_t j = 0; j < level->getLevelWidth(); j++)
		{
			//Si la sala está explorada, la pintamos
			if (level->getRoom(i, j)->isExplored()) {
				//Pintamos distinta la sala actual
				if(level->getRoom(i,j)->getType() == Boss)
					SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0xff0000ff));//Dibujaremos en amarillo
				else {
					if (i == currX && j == currY)
						SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0xffff00ff));//Dibujaremos en amarillo
					else
						SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0xff00ffff));//Dibujaremos en morado
				}
				//Y colocamos las habitaciones en funcion a la actual
				destRect.x = (centerX + rWidth * (i - currX)) - rWidth/2;
				destRect.y = centerY + rHeight * (j - currY) - rHeight/2;

				//Finalmente, solo pintamos la sala si esta dentro de la "Ventana" del minimapa
				if (destRect.x > winW - width && destRect.y < winH + width) {
					SDL_RenderFillRect(Game::getGame()->getRenderer(), &destRect);
					drawDoors(destRect, level->getRoom(i, j));
				}
			}
		}
	}
	SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0x000000ff));//Dibujaremos en verde
}
