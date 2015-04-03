#include "GestorAnimaciones.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


using namespace std; // TODO : VER AMBITO

GestorAnimaciones* GestorAnimaciones::s_pInstance = NULL;

bool GestorAnimaciones::cargarAnimacion(std::string pathImagen, int cantidadFotogramas, int fps,  std::string id, SDL_Renderer* pRenderer)
{
//	SDL_Surface* pTempSurface = IMG_Load(pathImagen.c_str());
//    cout << pathImagen;
//	if (!pTempSurface)
//		return false;
//
//	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
//
//	SDL_FreeSurface(pTempSurface);
//
//	if (!pTexture)
//		return false;
//
//	Animacion* a = new Animacion(pTexture, cantidadFotogramas, fps);
//	mapaAnimaciones[id] = a;
//
//	return true;
}

Animacion* GestorAnimaciones::getAnimacion(std::string id) {
//	return mapaAnimaciones[id];
}

void GestorAnimaciones::clean() {
//	for (std::map<string, Animacion*>::iterator it=mapaAnimaciones.begin(); it!=mapaAnimaciones.end(); ++it)
//		SDL_DestroyTexture(it->second->getTextura());
}
