/*
 * Renderizador.cpp
 *
 *  Created on: 7/4/2015
 *      Author: val
 */

#include "Renderizador.h"
#include <iostream>

Renderizador* Renderizador::instancia_unica = NULL;

Renderizador* Renderizador::Instance()
{
	if (instancia_unica == NULL)
	{
		instancia_unica = new Renderizador();
	}
	return instancia_unica;
}

Renderizador::Renderizador():vWindow(NULL), vRenderer(NULL){

}

bool Renderizador::init(string titulo, Vector2f posicion, Vector2f tamanio, bool fullscreen){

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

		this->vWindow = SDL_CreateWindow(titulo.c_str(), posicion.X(), posicion.Y(), tamanio.X(), tamanio.Y(), flags);

		if (this->vWindow != NULL) // window init success
		{
			std::cout << "window creation success\n";
			this->vRenderer = SDL_CreateRenderer(vWindow, -1, SDL_RENDERER_SOFTWARE);

			if (this->vRenderer != NULL) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(this->vRenderer, 255, 0, 0, 255);
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

	std::cout << "init success\n" << endl;
	return true;
}

SDL_Renderer* Renderizador::getRenderer(){
	return this->vRenderer;
}

void Renderizador::dibujar(Dibujable* dibujable){
	SDL_RenderClear(this->vRenderer);
    dibujable->dibujar();
	SDL_RenderPresent(this->vRenderer);
}

Renderizador::~Renderizador(){
    instancia_unica = NULL;
	SDL_DestroyRenderer(this->vRenderer);
    SDL_DestroyWindow(this->vWindow);
	SDL_Quit();
}

