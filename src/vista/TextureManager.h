#pragma once
#ifndef __TextureManager__
#define __TextureManager__
#include <iostream>
#include <map>
#include <SDL2/SDL.h>

class TextureManager {
private:

	std::map<std::string, SDL_Texture*> m_textureMap;

	// SINGLETON
	TextureManager():cantidadFotogramas(1) {}
	static TextureManager* s_pInstance;
	int cantidadFotogramas;

public:
	static TextureManager* Instance()
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}
		return s_pInstance;
	}
	bool cargarImagen(std::string nombreArchivo, std::string id, SDL_Renderer* pRenderer);
	void dibujar(
			std::string id,
			SDL_Rect* rectTextura,
			SDL_Rect* rectVentana,
			SDL_Renderer* pRenderer,
			SDL_RendererFlip espejado = SDL_FLIP_NONE,
			SDL_Point* centroRotacion = NULL,
			const double anguloRotacion = 0);
};

typedef TextureManager TheTextureManager;

#endif /* defined (__TextureManager__) */
