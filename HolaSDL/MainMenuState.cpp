#include "MainMenuState.h"
#include "Game.h"
#include "Time.h"


MainMenuState::MainMenuState()
{

	font = new Font("..\\images\\Polentical Neon Regular.ttf", 100);
	font2 = new Font("..\\images\\Polentical Neon Bold.ttf", 100);
	background = new Texture(game->getRenderer(), "..\\images\\Intro\\intro.png");
	openText = new Texture(game->getRenderer());
	op1Tex = new Texture(game->getRenderer());
	op2Tex = new Texture(game->getRenderer());
	op3Tex = new Texture(game->getRenderer());
	op4Tex = new Texture(game->getRenderer());
	op1Tex->loadFromText("NEW GAME", *font2, white);
	op2Tex->loadFromText("TUTORIAL", *font2, white);
	op3Tex->loadFromText("CREDITS", *font2, white);
	op4Tex->loadFromText("EXIT", *font2, white);
	c.a = 255;
	c.b = 200;
	c.g = 50;
	c.r = 200;
	bckgrndRect = RECT(0, 0, 1040, 720);
	textRect = RECT(320, 555, 450, 70);

	op1Rect = RECT(100, 350, 30 * 8, 70);
	op2Rect = RECT(100, 430, 30 * 8, 70);
	op3Rect = RECT(100, 500, 30 * 7, 70);
	op4Rect = RECT(100, 580, 30 * 4, 70);


}


MainMenuState::~MainMenuState()
{
	delete font;
	delete font2;
	delete background;
	delete openText;
	delete op1Tex;
	delete op2Tex;
	delete op3Tex;
	delete op4Tex;
}

void MainMenuState::handleEvent(SDL_Event & e)
{
	if (!flag && (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN))
	{
		flag = true;
	}
	else if(flag && e.type == SDL_KEYDOWN) 
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
				break;
			case 4:
				exitGame(game);
				break;
			}
		}
	}
	else if (flag && e.type == SDL_MOUSEBUTTONDOWN) 
	{
		SDL_GetMouseState(&mouse.x, &mouse.y);
		if (SDL_PointInRect(&mouse, &op1Rect) || SDL_PointInRect(&mouse, &op2Rect) || SDL_PointInRect(&mouse, &op3Rect) || SDL_PointInRect(&mouse, &op4Rect)) 
		{
			switch (selectedOp)
			{
			case 1:
				playState(game);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				exitGame(game);
				break;
			}
		}
	}
}

void MainMenuState::update()
{
	if (!flag) {
		openText->loadFromText("Press any Key to continue", *font, c);
		if (!alfaUp)
		{
			c.r -= 4 * Time::getInstance()->DeltaTime;
			c.b -= 4 * Time::getInstance()->DeltaTime;
			c.g-= 1 * Time::getInstance()->DeltaTime;
			if (c.r <= 0)
			{
				c.b = 0;
				c.g = 0;
				c.r = 0;
				alfaUp = true;
			}
		}
		else
		{
			c.r += 4 * Time::getInstance()->DeltaTime*40;
			c.b += 4 * Time::getInstance()->DeltaTime*40;
			c.g+= 1 * Time::getInstance()->DeltaTime*24;
			if (c.r >= 200)
			{
				c.b = 200;
				c.g = 50;
				c.r = 200;
				alfaUp = false;
			}
		}
	}
	else 
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
		else if (SDL_PointInRect(&mouse, &op4Rect) && selectedOp != 4)
		{
			selectedOp = 4;
			changeColors();
		}
		
	}
	for (GameObject* o: gameObjects) 
	{
		o->update();
	}
}

void MainMenuState::render()
{
	SDL_RenderClear(Game::getGame()->getRenderer());
	background->render(bckgrndRect);
	if (!flag) {
		openText->render(textRect);
	}
	else 
	{
		op1Tex->render(op1Rect);
		op2Tex->render(op2Rect);
		op3Tex->render(op3Rect);
		op4Tex->render(op4Rect);
	}
	for (GameObject* o : gameObjects) 
	{
		o->render();
	}
}

void MainMenuState::playState(Game* game)
{
	//game->startGame();
	game -> playIntro();
}

void MainMenuState::exitGame(Game* game)
{
	game->exit = true;
}

void MainMenuState::changeColors() 
{
	if (selectedOp == 1)
	{
		op1Tex->loadFromText("NEW GAME", *font2, blue);
		op2Tex->loadFromText("TUTORIAL", *font2, white);
		op3Tex->loadFromText("CREDITS", *font2, white);
		op4Tex->loadFromText("EXIT", *font2, white);
	}
	else if (selectedOp == 2)
	{
		op2Tex->loadFromText("TUTORIAL", *font2, blue);
		op1Tex->loadFromText("NEW GAME", *font2, white);
		op3Tex->loadFromText("CREDITS", *font2, white);
		op4Tex->loadFromText("EXIT", *font2, white);
	}
	else if (selectedOp == 3)
	{
		op3Tex->loadFromText("CREDITS", *font2, blue);
		op2Tex->loadFromText("TUTORIAL", *font2, white);
		op1Tex->loadFromText("NEW GAME", *font2, white);
		op4Tex->loadFromText("EXIT", *font2, white);
	}
	else if (selectedOp == 4)
	{
		op4Tex->loadFromText("EXIT", *font2, blue);
		op2Tex->loadFromText("TUTORIAL", *font2, white);
		op3Tex->loadFromText("CREDITS", *font2, white);
		op1Tex->loadFromText("NEW GAME", *font2, white);
	}


}



