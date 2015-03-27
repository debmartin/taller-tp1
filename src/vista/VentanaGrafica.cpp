/*
 * VentanaGrafica.cpp
 *
 *  Created on: 26/3/2015
 *      Author: val
 */

#include <iostream>
#include "VentanaGrafica.h"
#include <SDL2/SDL.h>

VentanaGrafica* VentanaGrafica::instancia_unica = NULL;

VentanaGrafica* VentanaGrafica::Instance()
{
	if (instancia_unica == NULL)
	{
		instancia_unica = new VentanaGrafica();
	}
	return instancia_unica;
}

VentanaGrafica::VentanaGrafica():vWindow(NULL), vRenderer(NULL) { }

bool VentanaGrafica::init(string titulo, int xpos, int ypos, int height, int width, bool fullscreen){

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

		vWindow = SDL_CreateWindow(titulo.c_str(), xpos, ypos, height, width, flags);

		if (vWindow != NULL) // window init success
		{
			std::cout << "window creation success\n";
			vRenderer = SDL_CreateRenderer(vWindow, -1, SDL_RENDERER_SOFTWARE);

			if (vRenderer != NULL) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(vRenderer, 255, 0, 0, 255);
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

SDL_Renderer* VentanaGrafica::getRenderer(){
	return this->vRenderer;
}

void VentanaGrafica::setSprite(Sprite* unSprite, string nombre){
	this->mapaSprites[nombre] = unSprite;
}

void VentanaGrafica::quitarSprite(string id){
	this->mapaSprites.erase(id);
}

void VentanaGrafica::cambiarSprite(string id, Sprite* nuevoSprite){
	this->mapaSprites[id] = nuevoSprite;
}

Sprite* VentanaGrafica::getSprite(string id){
	return this->mapaSprites[id];
}

void VentanaGrafica::dibujarTodo(){

	//SDL_SetRenderDrawColor(vRenderer, 255, 0, 0, 255);
	SDL_RenderClear(vRenderer);

	for (std::map<string,Sprite*>::iterator it=mapaSprites.begin(); it!=mapaSprites.end(); ++it)
		(it->second)->dibujar();

	SDL_RenderPresent(vRenderer);
}

void VentanaGrafica::cerrar() {
	SDL_DestroyWindow(vWindow);
	SDL_DestroyRenderer(vRenderer);
	SDL_Quit();
	cout << "Cerrando ventana" << endl;
}

void VentanaGrafica::update() {
	for (std::map<string,Sprite*>::iterator it=mapaSprites.begin(); it!=mapaSprites.end(); ++it)
		(it->second)->update();
}
VentanaGrafica::~VentanaGrafica(){}
