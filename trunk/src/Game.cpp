#include "Game.h"
#include <cstddef>
#include <Box2D/Box2D.h>

Game::Game() : m_bRunning(false), m_pWindow(NULL), m_pRenderer(NULL) {}

Game::~Game() {}

// simply set the running variable to true
bool Game::init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen)
{

	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";

		// init the window
		int flags;
		if (fullscreen)
			flags = SDL_WINDOW_FULLSCREEN;
		else
			flags = 0;

		m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

		if (m_pWindow != NULL) // window init success
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != NULL) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}

	std::cout << "init success\n";
	m_bRunning = true; // everything inited successfully, start the main loop

	// INICIO CODIGO USUARIO

	// FIN CODIGO USUARIO


	return true;
}

void Game::render()
{
	// clear the window to black
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color

	// INICIO CODIGO USUARIO

	// FIN CODIGO USUARIO

	// show the window
	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update()
{
	// INICIO CODIGO USUARIO

	// FIN CODIGO USUARIO
}

void Game::handleEvents()
{
	SDL_Event event;

	// INICIO CODIGO USUARIO

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}

	// FIN CODIGO USUARIO
}

void Game::clean() {
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

// a function to access the private running variable
bool Game::running() { return m_bRunning; }
