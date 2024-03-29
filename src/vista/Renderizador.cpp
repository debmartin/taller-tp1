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

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{

		Logger::getInstance()->debug("Renderizador: SDL init.");

		// Inicializacion de ventana
		int flags;
		if (fullscreen)
			flags = SDL_WINDOW_FULLSCREEN;
		else
			flags = 0;

		this->vWindow = SDL_CreateWindow(titulo.c_str(), posicion.X(), posicion.Y(), tamanio.X(), tamanio.Y(), flags);

		if (this->vWindow != NULL)
		{
			Logger::getInstance()->debug("Renderizador: ventana creada.");
			this->vRenderer = SDL_CreateRenderer(vWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

			if (this->vRenderer != NULL)
			{
				Logger::getInstance()->debug("Renderizador: creacion correcta..");
				SDL_SetRenderDrawColor(this->vRenderer, 255, 0, 0, 255);
			}
			else
			{
				Logger::getInstance()->error("Renderizador: falla al crear el renderizador.");
				return false;
			}
		}
		else
		{
			Logger::getInstance()->error("Renderizador: falla al crear la ventana");
			return false;
		}
	}
	else
	{
		Logger::getInstance()->debug("Renderizador: falla en SDL init.");
		return false;
	}
	if (TTF_Init() != 0){
			std::cout << "ERROR: TTF_Init" << endl;
	}

	Logger::getInstance()->debug("Renderizador: inicializacion finalizada.");
	return true;
}

SDL_Renderer* Renderizador::getRenderer(){
	return this->vRenderer;
}

SDL_Window* Renderizador::getWindow() {
	return this->vWindow;
}

void Renderizador::dibujar(Dibujable* dibujable){
	SDL_RenderClear(this->vRenderer);
    dibujable->dibujar();

}

void Renderizador::destruir() {
    instancia_unica = NULL;
	SDL_DestroyRenderer(this->vRenderer);
    SDL_DestroyWindow(this->vWindow);
	SDL_Quit();
}

Renderizador::~Renderizador(){
    instancia_unica = NULL;
	SDL_DestroyRenderer(this->vRenderer);
    SDL_DestroyWindow(this->vWindow);
	SDL_Quit();
}

