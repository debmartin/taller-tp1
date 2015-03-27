/*
 * VentanaGrafica.cpp
 *
 *  Created on: 26/3/2015
 *      Author: val
 */

#include "VentanaGrafica.h"

VentanaGrafica* VentanaGrafica::instancia_unica = NULL;

VentanaGrafica* VentanaGrafica::Instance()
{
	if (instancia_unica == NULL)
	{
		instancia_unica = new VentanaGrafica();
	}
	return instancia_unica;
}

VentanaGrafica::VentanaGrafica(){
	vWindow = NULL;
}

void VentanaGrafica::init(string titulo, SDL_Rect disposicion, bool fullscreen){

	//vWindow = SDL_CreateWindow(titulo, xpos, ypos, height, width, flags);
}

SDL_Renderer* VentanaGrafica::getRenderer(){

}

void VentanaGrafica::agregarSprite(Sprite* unSprite, string s){

}

void VentanaGrafica::quitarSprite(string id){

}

void VentanaGrafica::cambiarSprite(string id, Sprite* nuevoSprite){

}

void VentanaGrafica::getSprite(string id){

}

void VentanaGrafica::dibujarTodo(){

}

VentanaGrafica::~VentanaGrafica(){}
