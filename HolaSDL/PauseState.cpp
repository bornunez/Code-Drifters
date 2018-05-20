#include "PauseState.h"
#include "Game.h"



PauseState::PauseState(GameState* upper): UpperGameState(upper)
{
	white = { COLOR(0x30CCF8ff) };
	blue = { COLOR(0x46FFECff) };
	font = new Font("..\\images\\Polentical Neon Regular.ttf", 100);
	font2 = new Font("..\\images\\Polentical Neon Bold.ttf", 100);
	op1Tex = new Texture(game->getRenderer());
	op2Tex = new Texture(game->getRenderer());
	op3Tex = new Texture(game->getRenderer());
	title1 = new Texture(game->getRenderer());
//	title2 = new Texture(game->getRenderer());
	if (game->getLanguage() == Language::English)
	{
		op1 = "RESUME";
		op2 = "MAIN MENU";
		op3 = "EXIT";
		pause = "PAUSE";
	}
	else
	{
		op1 = "CONTINUAR";
		op2 = "IR AL MENÚ";
		op3 = "SALIR";
		pause = "PAUSA";
	}
	background = new Texture(game->getRenderer(), "..\\Arbol\\Central.png");
	op1Tex->loadFromText(op1, *font2, white);
	op2Tex->loadFromText(op2, *font2, white);
	op3Tex->loadFromText(op3, *font2, white);
	title1->loadFromText(pause, *font2, white);
//	title2->loadFromText("PAUSE", *font2, blue);

	bckgrndRect = RECT(345, 85, 350, 550);

	op1Rect = RECT(525-(30 * op1.length())/2, 280, 30 * op1.length(), 50);
	op2Rect = RECT(525 - (27 * op2.length()) / 2, 390, 27 * op2.length(), 50);
	op3Rect = RECT(525 - (30 * op3.length()) / 2, 500, 30 * op3.length(), 50);

	title1Rect = RECT(415, 130, 45* pause.length(), 70);
//	title2Rect = RECT(393, 128, 45*5, 70);
}


PauseState::~PauseState()
{
	delete font;
	delete font2;
	delete op1Tex;
	delete op2Tex;
	delete op3Tex;
	delete title1;
	delete background;
}

void PauseState::handleEvent(SDL_Event & e)
{
	if (e.type == SDL_KEYDOWN)
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
					selectedOp = 3;
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
				game->endDialogue();
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
				game->endDialogue();
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

void PauseState::update()
{
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (SDL_PointInRect(&mouse, &op1Rect) && selectedOp != 1)
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


	for (GameObject* o : gameObjects)
	{
		o->update();
	}
}

void PauseState::render()
{
	SDL_RenderClear(Game::getGame()->getRenderer());
	UpperGameState::render();
	background->render(bckgrndRect);
//	title2->render(title2Rect);
	title1->render(title1Rect);
	op1Tex->render(op1Rect);
	op2Tex->render(op2Rect);
	op3Tex->render(op3Rect);
	for (GameObject* o : gameObjects)
	{
		o->render();
	}
}

void PauseState::exitGame(Game* game)
{
	game->exit = true;
}

void PauseState::changeColors()
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
