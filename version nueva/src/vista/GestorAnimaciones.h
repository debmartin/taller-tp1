#ifndef __GestorAnimaciones__
#define __GestorAnimaciones__
#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include "Animacion.h"

class GestorAnimaciones {
private:

	std::map<std::string, Animacion*> mapaAnimaciones;
	static GestorAnimaciones* s_pInstance;

public:
	static GestorAnimaciones* Instance()
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new GestorAnimaciones();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool cargarAnimacion(std::string nombreArchivo, int cantidadFotogramas, int fps, std::string id, SDL_Renderer* pRenderer);

	Animacion* getAnimacion(std::string id);

	void clean();
};

#endif /* defined (__TextureManager__) */
