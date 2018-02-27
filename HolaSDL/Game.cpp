#include "Game.h"



MainCharacter * Game::getCharacter()
{
	return mainCharacter;
}

Game::Game()
{
	winX = winY = 50;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	window = SDL_CreateWindow("Haro I de Saboya", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	camera = new Camera(this);
	mainCharacter = new MainCharacter(this);
	
	if (renderer == nullptr)//Si hay errores activa el flag
	{
		error = true;
	}
	else
	{
		stateMachine = new GameStateMachine();
		//MainMenuState* mm = new MainMenuState(this);
		//stateMachine->pushState(mm);

	}
}
Game::~Game()
{
	delete stateMachine;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

SDL_Renderer * Game::getRenderer()
{
	return renderer;
}

Camera * Game::getCamera()
{
	return camera;
}

void Game::run()
{
	while (!exit) 
	{
		SDL_RenderClear(getRenderer());
		mainCharacter->render();
		handleEvents();
		SDL_RenderPresent(getRenderer());
	}
}

void Game::handleEvents()
{
	while (SDL_PollEvent(&event) && !exit) {

		if (event.type == SDL_QUIT)
		{
			exit = true;
		}

		else
		{
			//stateMachine->currentState()->handleEvent(event);
		}
	}
}

int Game::getWinW() {//Pide el ancho de la ventana
	return winWidth;
}
int Game::getWinH() {//Pide la altura de la altura
	return winHeight;
}

