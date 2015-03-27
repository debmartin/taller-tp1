#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GestorTexturas.h"

using namespace std; // TODO : VER AMBITO

GestorTexturas* GestorTexturas::s_pInstance = NULL;

bool GestorTexturas::cargarImagen(std::string pathImagen, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(pathImagen.c_str());

	if (!pTempSurface)
		return false;

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	if (!pTexture)
		return false;

	m_textureMap[id] = pTexture;
	return true;
}

SDL_Texture* GestorTexturas::getTextura(std::string id) {
	return m_textureMap[id];
}

void GestorTexturas::clean() {
	for (std::map<string, SDL_Texture*>::iterator it=m_textureMap.begin(); it!=m_textureMap.end(); ++it)
		SDL_DestroyTexture(it->second);
}
