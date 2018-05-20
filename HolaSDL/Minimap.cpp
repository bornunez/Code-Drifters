#include "Minimap.h"
#include "Game.h"
#include "PlayState.h"
#include "Managers.h"
#include "DungeonGenerator.h"
#include "Room.h"

void Minimap::drawDoors(SDL_Rect destRect,SDL_Rect srcRect, Room* room)
{
	vector<bool> doors = room->getDoors();
	for (int i = 0; i < doors.size(); i++) {
		if (doors[i]) {
			openDoors[i]->render(destRect, &srcRect);
		}
		else {
			closedDoors[i]->render(destRect, &srcRect);
		}
	}
}

void Minimap::drawFill(SDL_Rect destRect, SDL_Rect srcRect, Room * room, bool on)
{
	if (on)
		onFills[room->getType()]->render(destRect, &srcRect);
	else
		offFills[room->getType()]->render(destRect, &srcRect);

	vector<bool> doors = room->getDoors();
	for (int i = 0; i < doors.size(); i++) {
		if (doors[i]) {
			if(on)
				openNormalOn[i]->render(destRect, &srcRect);
			else
				openNormalOff[i]->render(destRect, &srcRect);
		}
	}
}

Minimap::Minimap(float scale, float rScale, int mWidth, int mHeight) : scale(scale), rScale(rScale), marginHeight(mHeight), marginWidth(mWidth)
{
	ResourceManager* rm = ResourceManager::getInstance();
	int winW = Game::getGame()->getWinW();
	int winH = Game::getGame()->getWinH();
	float gameScale = Game::getGame()->getScale();

	//El borde y todos sus calculos
	border = rm->getTexture(MinimapBorder);
	borderBase = rm->getTexture(MinimapBase);
	width = border->getWidth() *  gameScale * scale;
	height = border->getHeight() * gameScale * scale;
	//Su rect
	borderRect.x = winW - width - mWidth;borderRect.y = mHeight;
	borderRect.w = width; borderRect.h = height;

	srcBorderRect.x = srcBorderRect.y = 0;
	srcBorderRect.w = border->getWidth(); srcBorderRect.h = border->getHeight();

	//Ahora las salas
	base = rm->getTexture(BaseRoom);
	openDoors = {
		rm->getTexture(OpenUp),
		rm->getTexture(OpenRight),
		rm->getTexture(OpenDown),
		rm->getTexture(OpenLeft),
	};
	closedDoors = {
		rm->getTexture(ClosedUp),
		rm->getTexture(ClosedRight),
		rm->getTexture(ClosedDown),
		rm->getTexture(ClosedLeft),
	};
	//Todas las salas comparten tamaño
	rWidth = base->getWidth() * gameScale * rScale;
	rHeight = base->getHeight() * gameScale * rScale;
	
	onFills = {
		rm->getTexture(First_On),
		rm->getTexture(Normal_On),
		rm->getTexture(Boss_On),
		rm->getTexture(Shop_On),
		rm->getTexture(Normal_On)
	};
	offFills = {
		rm->getTexture(First_Off),
		rm->getTexture(Normal_Off),
		rm->getTexture(Boss_Off),
		rm->getTexture(Shop_Off),
		rm->getTexture(Normal_Off)
	};
	openNormalOn = {
		rm->getTexture(OpenUpNormalOn),
		rm->getTexture(OpenRightNormalOn),
		rm->getTexture(OpenDownNormalOn),
		rm->getTexture(OpenLeftNormalOn)
	};
	openNormalOff = {
		rm->getTexture(OpenUpNormalOff),
		rm->getTexture(OpenRightNormalOff),
		rm->getTexture(OpenDownNormalOff),
		rm->getTexture(OpenLeftNormalOff)
	};
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
	int centerX = winW - width / 2 - marginWidth;
	int centerY = (height + marginHeight) / 2;


	//Vamos a centrar nuestra sala en el medio
	int currX = LevelManager::getInstance()->getCurrentRoom()->getX();
	int currY = LevelManager::getInstance()->getCurrentRoom()->getY();

	DungeonGenerator* level = LevelManager::getInstance()->getLevel();

	SDL_Rect roomRect, srcRoomRect;
	srcRoomRect.x = srcRoomRect.y = 0;
	srcRoomRect.w = base->getWidth(); srcRoomRect.h = base->getHeight();
	roomRect.w = rWidth; roomRect.h = rHeight;

	//Primero pintamos la base del fondo
	borderBase->render(borderRect, &srcBorderRect);

	//Pintamos la sala en el centor, a partir de ahi, las visitadas las pondremos en verde, las demas no se ven
	for (size_t i = 0; i < level->getLevelHeight(); i++)
	{
		for (size_t j = 0; j < level->getLevelWidth(); j++)
		{
			//Si la sala está explorada, la pintamos
			if (level->getRoom(i, j)->isExplored()) {
				//Y colocamos las habitaciones en funcion a la actual
				roomRect.x = (centerX + rWidth * (i - currX)) - rWidth/2;
				roomRect.y = centerY + rHeight * (j - currY) - rHeight/2;

				//Finalmente, solo pintamos la sala si esta dentro de la "Ventana" del minimapa
				if (roomRect.x > winW - (width + marginWidth) && roomRect.x < (winW - marginWidth - rWidth) && roomRect.y > marginHeight && roomRect.y < (marginHeight + height )) {
					base->render(roomRect,&srcRoomRect);
					drawFill(roomRect, srcRoomRect, level->getRoom(i, j), i == currX && j == currY);
					drawDoors(roomRect,srcRoomRect, level->getRoom(i, j));
				}
			}
		}
	}
	//Y para acabar pintamos el marco
	border->render(borderRect, &srcBorderRect);
	SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0x000000ff));//Dibujaremos en verde
}
