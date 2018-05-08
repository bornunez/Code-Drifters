#include "GameOverState.h"
#include "Game.h"


GameOverState::GameOverState()
{

	font = new Font("..\\images\\Polentical Neon Regular.ttf", 100);
	font2 = new Font("..\\images\\Polentical Neon Bold.ttf", 100);
	op1Tex = new Texture(game->getRenderer());
	op2Tex = new Texture(game->getRenderer());
	op3Tex = new Texture(game->getRenderer());
	op1Tex->loadFromText("RESTART", *font2, white);
	op2Tex->loadFromText("TUTORIAL", *font2, white);
	op3Tex->loadFromText("EXIT", *font2, white);

	op1Rect = RECT(450, 550, 30 * 7, 70);
	op2Rect = RECT(125, 550, 30 * 8, 70);
	op3Rect = RECT(750, 550, 30 * 4, 70);


}


GameOverState::~GameOverState()
{
}

void GameOverState::handleEvent(SDL_Event & e)
{
	if(e.type == SDL_KEYDOWN) 
	{
		if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_UP) 
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
					selectedOp = 4;
				}
			}
			changeColors();

		}
		else if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN)
		{
			if (selectedOp == 0)
			{
				selectedOp = 1;
			}
			else
			{
				selectedOp++;
				if (selectedOp > 4)
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
	game->startGame();
}

void GameOverState::exitGame(Game* game)
{
	game->exit = true;
}

void GameOverState::changeColors()
{
	if (selectedOp == 1)
	{
		op1Tex->loadFromText("RESTART", *font2, blue);
		op2Tex->loadFromText("TUTORIAL", *font2, white);
		op3Tex->loadFromText("EXIT", *font2, white);
	}
	else if (selectedOp == 2)
	{
		op2Tex->loadFromText("TUTORIAL", *font2, blue);
		op1Tex->loadFromText("RESTART", *font2, white);
		op3Tex->loadFromText("EXIT", *font2, white);
	}
	else if (selectedOp == 3)
	{
		op3Tex->loadFromText("EXIT", *font2, blue);
		op2Tex->loadFromText("TUTORIAL", *font2, white);
		op1Tex->loadFromText("RESTART", *font2, white);
	}


}



