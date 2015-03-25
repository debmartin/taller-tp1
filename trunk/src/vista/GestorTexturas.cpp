#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GestorTexturas.h"

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
