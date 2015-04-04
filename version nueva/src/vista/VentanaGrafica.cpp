/*
 * VentanaGrafica.cpp
 *
 *  Created on: 26/3/2015
 *      Author: val
 */

#include <iostream>
#include "VentanaGrafica.h"
#include <SDL2/SDL.h>
#include <vector>

VentanaGrafica* VentanaGrafica::instancia_unica = NULL;

VentanaGrafica* VentanaGrafica::Instance()
{
	if (instancia_unica == NULL)
	{
		instancia_unica = new VentanaGrafica();
	}
	return instancia_unica;
}

VentanaGrafica::VentanaGrafica():vWindow(NULL), vRenderer(NULL), escenario(NULL){ }

bool VentanaGrafica::init(string titulo, int xpos, int ypos, int height, int width, bool fullscreen, EscenarioGrafico* unEscenario){

	this->escenario = unEscenario;

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

		vWindow = SDL_CreateWindow(titulo.c_str(), xpos, ypos, width, height, flags);

		if (vWindow != NULL)
		{
			std::cout << "window creation success\n";
			vRenderer = SDL_CreateRenderer(vWindow, -1, SDL_RENDERER_SOFTWARE);

			if (vRenderer != NULL)
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(vRenderer, 255, 0, 0, 255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false;
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false;
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false;
	}

	std::cout << "init success\n" << endl;
	return true;

}

SDL_Renderer* VentanaGrafica::getRenderer(){
	return this->vRenderer;
}

void VentanaGrafica::dibujarTodo(){
	SDL_RenderClear(vRenderer);
    this->escenario->dibujar();
	SDL_RenderPresent(vRenderer);
	cout << "VentanaGrafica::dibujarTodo()" << endl;
}

void VentanaGrafica::cerrar() {
	SDL_DestroyWindow(vWindow);
	SDL_DestroyRenderer(vRenderer);
	SDL_Quit();
	cout << "Cerrando ventana" << endl;
}

void VentanaGrafica::actualizar() {
    escenario->actualizar();
}

//Devuelve limites logicos del escenario
LimitesLogicos VentanaGrafica::getLimitesLogicos(){

	LimitesLogicos limitesLogicos(this->escenario->getAnchoLogico(), this->escenario->getAltoLogico(), this->escenario->getYPisoLogico());
	return limitesLogicos;
}

VentanaGrafica::~VentanaGrafica(){}
