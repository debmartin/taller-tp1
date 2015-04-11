/*
 * Renderizador.h
 *
 *  Created on: 7/4/2015
 *      Author: val
 */

#ifndef SRC_VISTA_RENDERIZADOR_H_
#define SRC_VISTA_RENDERIZADOR_H_

#include <SDL2/SDL.h>
#include <string>
#include "Dibujable.h"
#include "../modelo/Vector2f.h"

using namespace std;

class Renderizador{
	private:
		SDL_Window* vWindow;
		SDL_Renderer* vRenderer;

		// SINGLETON
		Renderizador();
		static Renderizador* instancia_unica;

	public:
		virtual ~Renderizador();
		bool init(string titulo, Vector2f posicion, Vector2f tamanio, bool fullscreen);
		SDL_Renderer* getRenderer();
		void dibujar(Dibujable* dibujable);
		static Renderizador* Instance();
};

#endif /* SRC_VISTA_RENDERIZADOR_H_ */
