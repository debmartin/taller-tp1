#ifndef __GestorTexturas__
#define __GestorTexturas__
#include <SDL2/SDL.h>
#include <iostream>
#include <map>

class GestorTexturas {
private:

	std::map<std::string, SDL_Texture*> m_textureMap;
	static GestorTexturas* s_pInstance;

public:
	static GestorTexturas* Instance()
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new GestorTexturas();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool cargarImagen(std::string nombreArchivo, std::string id, SDL_Renderer* pRenderer);

	SDL_Texture* getTextura(std::string id);

	void clean(); // TODO: limipar
};

#endif /* defined (__TextureManager__) */
