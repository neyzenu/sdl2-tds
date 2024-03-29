#include <iostream>
#include "GameWindow.hpp"

using std::cerr;
using std::cout;
using std::endl;

GameWindow::GameWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cerr << "error: SDL couldn't initialized" << endl;
		return;
	}
	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("Game",
							  SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED,
							  400, 400, 0);
	screenSurface = SDL_GetWindowSurface(window);
	renderer = SDL_GetRenderer(window);
	/* SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF)); */
}

void GameWindow::EventLoop()
{
	SDL_Event	e;
	bool		exit = false;
	
	while (!exit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
			else if (e.key.keysym.sym == SDLK_d)
			{
				if (gameObject)
					gameObject->SetPosition(gameObject->pos.x + 10, gameObject->pos.y);
			}
			else if (e.key.keysym.sym == SDLK_a)
			{
				if (gameObject)
					gameObject->SetPosition(gameObject->pos.x - 10, gameObject->pos.y);
			}
			else if (e.key.keysym.sym == SDLK_s)
			{
				if (gameObject)
					gameObject->SetPosition(gameObject->pos.x, gameObject->pos.y + 10);
			}
			
			else if (e.key.keysym.sym == SDLK_w)
			{
				if (gameObject)
					gameObject->SetPosition(gameObject->pos.x, gameObject->pos.y - 10);
			}
		}
		Render();
		// SDL_UpdateWindowSurface(window);
	}
	
}

void GameWindow::Render()
{
	SDL_RenderClear(renderer);
	if (gameObject)
		gameObject->Render();
	SDL_RenderPresent(renderer);
}

GameWindow::~GameWindow()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}