#include "Game.h"



DungeonGenerator * Game::getLevel()
{
	return level;
}

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

	int roomNumber = 20;
	level = new DungeonGenerator(this, 20, 20, 20, 50, 50);

	//Esto debería ir en el playState, está puesto de prueba. Crea un personaje y una cámara, le asigna una sala al personaje
	camera = new Camera(this);	
	mainCharacter = new MainCharacter(this, 100,100,50,50);
	mainCharacter->setMaxVelocity(1);	
	mainCharacterMovement = new MCMovementComponent(mainCharacter, SDL_SCANCODE_W, SDL_SCANCODE_D, SDL_SCANCODE_S, SDL_SCANCODE_A);	
	mainCharacter->addComponent(mainCharacterMovement);
	level->CreateMap();
	level->getFirstRoom()->addCharacter(mainCharacter);//Se añade el personaje a la primera sala
	mainCharacter->changeCurrentRoom(level->getFirstRoom()->getX(), level->getFirstRoom()->getY());//Se le asigna la posición de la primera sala




	
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
		SDL_RenderClear(getRenderer());//Provisional en lugar del render
		camera->render();//" "
		SDL_RenderPresent(getRenderer());// " "
		handleEvents();
		mainCharacter->update();//Provisional en lugar del update
		
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
			mainCharacter->handleEvents(event);
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

