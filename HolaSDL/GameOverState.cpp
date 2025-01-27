#include "GameOverState.h"
#include "Game.h"
#include "Time.h"
#include "ResourceManager.h"

GameOverState::GameOverState()
{
	ResourceManager::getInstance()->getMusic(SadEnd)->play();
	blue = { COLOR(0xFE1B0AFF) };
	white = { COLOR(0x990606FF) };
	font = new Font("..\\images\\Polentical Neon Regular.ttf", 100);
	font2 = new Font("..\\images\\Polentical Neon Bold.ttf", 100);
	op1Tex = new Texture(game->getRenderer());
	op2Tex = new Texture(game->getRenderer());
	op3Tex = new Texture(game->getRenderer());
	title1 = new Texture(game->getRenderer());
	title2 = new Texture(game->getRenderer());
	deathChar = new Texture(game->getRenderer(), "..\\images\\Death.png");
	if (game->getLanguage() == Language::English)
	{
		op1 = "RESTART";
		op2 = "MAIN MENU";
		op3 = "EXIT";
	}
	else
	{
		op1 = "REINTENTAR";
		op2 = "IR AL MEN�";
		op3 = "SALIR";
	}
	op1Tex->loadFromText(op1, *font2, white);
	op2Tex->loadFromText(op2, *font2, white);
	op3Tex->loadFromText(op3, *font2, white);

	title1->loadFromText("GAME OVER", *font2, blue);
	title2->loadFromText("GAME OVER", *font2, white);

	op1Rect = RECT(450, 550, 25 * op2.length(), 70);
	op2Rect = RECT(125, 550, 25 * op2.length(), 70);
	op3Rect = RECT(750, 550, 25 * op3.length(), 70);

	title1Rect = RECT(180, 80, 680, 170);
	title2Rect = RECT(175, 75, 680, 170);

	deathRect = RECT(0, -220, 64*15, 64*15);


}


GameOverState::~GameOverState()
{
	delete font;
	delete font2;
	delete op1Tex;
	delete op2Tex;
	delete op3Tex;
	delete title2;
	delete title1;
	delete deathChar;
}

void GameOverState::handleEvent(SDL_Event & e)
{
	if(e.type == SDL_KEYDOWN) 
	{
		if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT) 
		{
			if (selectedOp == 0) 
			{
				selectedOp = 1;
			}
			else 
			{
				selectedOp--;
				if (selectedOp < 1) 
				{
					selectedOp = 3;
				}
			}
			changeColors();

		}
		else if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_LEFT)
		{
			if (selectedOp == 0)
			{
				selectedOp = 1;
			}
			else
			{
				selectedOp++;
				if (selectedOp > 3)
				{
					selectedOp = 1;
				}
			}
			changeColors();

		}
		else if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_RETURN)
		{
			switch (selectedOp)
			{
			case 1:
				playState(game);
				break;
			case 2:
				game->quitToMenu();
				break;
			case 3:
				exitGame(game);
				break;
			}
		}
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN) 
	{
		SDL_GetMouseState(&mouse.x, &mouse.y);
		if (SDL_PointInRect(&mouse, &op1Rect) || SDL_PointInRect(&mouse, &op2Rect) || SDL_PointInRect(&mouse, &op3Rect)) 
		{
			switch (selectedOp)
			{
			case 1:
				playState(game);
				break;
			case 2:
				game->quitToMenu();
				break;
			case 3:
				exitGame(game);
				break;
			}
		}
	}
}

void GameOverState::update()
{
		SDL_GetMouseState(&mouse.x, &mouse.y);
		if (SDL_PointInRect(&mouse, &op1Rect)&& selectedOp!=1)
		{			
			selectedOp = 1;
			changeColors();
		}
		else if (SDL_PointInRect(&mouse, &op2Rect) && selectedOp != 2)
		{
			selectedOp = 2;
			changeColors();
		}
		else if (SDL_PointInRect(&mouse, &op3Rect) && selectedOp != 3)
		{
			selectedOp = 3;
			changeColors();
		}
		

	for (GameObject* o: gameObjects) 
	{
		o->update();
	}
}

void GameOverState::render()
{
	SDL_RenderClear(Game::getGame()->getRenderer());
		deathChar->render(deathRect);
		title2->render(title2Rect);
		title1->render(title1Rect);
		op1Tex->render(op1Rect);
		op2Tex->render(op2Rect);
		op3Tex->render(op3Rect);
	for (GameObject* o : gameObjects) 
	{
		o->render();
	}
}

void GameOverState::playState(Game* game)
{
	game->restart();
}

void GameOverState::exitGame(Game* game)
{
	game->exit = true;
}

void GameOverState::changeColors()
{
	if (selectedOp == 1)
	{
		op1Tex->loadFromText(op1, *font2, blue);
		op2Tex->loadFromText(op2, *font2, white);
		op3Tex->loadFromText(op3, *font2, white);
	}
	else if (selectedOp == 2)
	{
		op2Tex->loadFromText(op2, *font2, blue);
		op1Tex->loadFromText(op1, *font2, white);
		op3Tex->loadFromText(op3, *font2, white);
	}
	else if (selectedOp == 3)
	{
		op3Tex->loadFromText(op3, *font2, blue);
		op2Tex->loadFromText(op2, *font2, white);
		op1Tex->loadFromText(op1, *font2, white);
	}


}



