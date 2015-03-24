#include "TextureManager.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

TextureManager* TextureManager::s_pInstance = NULL;

bool TextureManager::cargarImagen(std::string pathImagen, std::string id, SDL_Renderer* pRenderer)
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

void TextureManager::dibujar(
		std::string id,
		SDL_Rect* rectTextura,
		SDL_Rect* rectVentana,
		SDL_Renderer* pRenderer,
		SDL_RendererFlip espejado,
		SDL_Point* centroRotacion,
		const double anguloRotacion)
{
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], rectTextura, rectVentana, anguloRotacion, centroRotacion, espejado);
}
