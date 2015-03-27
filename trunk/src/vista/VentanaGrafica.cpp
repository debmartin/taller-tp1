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
	vRenderer = NULL;
}

void VentanaGrafica::init(string titulo, SDL_Rect disposicion, bool fullscreen){

	//vWindow = SDL_CreateWindow(titulo, xpos, ypos, height, width, flags);
}

SDL_Renderer* VentanaGrafica::getRenderer(){
	return this->vRenderer;
}

void VentanaGrafica::agregarSprite(Sprite* unSprite, string nombre){
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

}

VentanaGrafica::~VentanaGrafica(){}
