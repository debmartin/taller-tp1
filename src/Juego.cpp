/*
 * Juego.cpp
 *
 *  Created on: 27/3/2015
 *      Author: val
 */

#include "Juego.h"
#include <cstddef>
#include <SDL2/SDL.h> //TODO: Solo para tests
#include "vista/VentanaGrafica.h"
#include "vista/GestorTexturas.h"
#include "vista/Sprite.h"
Juego::~Juego() { }

// simply set the running variable to true
Juego::Juego(const char* titulo, int xpos, int ypos, int altura, int ancho, bool fullscreen)
{

	bool exito = VentanaGrafica::Instance()->init(titulo, xpos, ypos, altura, ancho, fullscreen);

	if (!exito)
		cout << "Error al inicializar juego" << endl;

	juegoCorriendo = true; // everything inited successfully, start the main loop

	// INICIO CODIGO USUARIO

	// 1) Cargar Texturas
	exito = GestorTexturas::Instance()->cargarImagen("screen-pit.png", "screen-pit", VentanaGrafica::Instance()->getRenderer());
	if (!exito) {
		cout << "ERRROR AL CREAR TEXTURA" << endl;
		exit(1);
	}

	exito = GestorTexturas::Instance()->cargarImagen("zubzero-quieto.png", "zubzero-quieto", VentanaGrafica::Instance()->getRenderer());
	if (!exito) {
		cout << "ERRROR AL CREAR TEXTURA" << endl;
		exit(1);
	}

	exito = GestorTexturas::Instance()->cargarImagen("zubzero-caminando.png", "zubzero-caminando", VentanaGrafica::Instance()->getRenderer());
	if (!exito) {
		cout << "ERRROR AL CREAR TEXTURA" << endl;
		exit(1);
	}

	// 2) Cargar Sprites
	Sprite* sprPit;
	sprPit = new Sprite("screen-pit", Vector2(0, 0), 1, 1, 1);
	sprPit->escalarConTamanio(640,480);
	VentanaGrafica::Instance()->setSprite(sprPit, "sprPit");

	sprSubZeroQuieto = new Sprite("zubzero-quieto", Vector2(0, 0), 12, 1, 10);
	sprSubZeroQuieto->setPosicion(Vector2(80,195));
	sprSubZeroQuieto->escalarConFactor(2,2);

	sprSubZeroCaminando = new Sprite("zubzero-caminando", Vector2(0, 0), 9, 1, 10);
	sprSubZeroCaminando->setPosicion(Vector2(80,195));
	sprSubZeroCaminando->escalarConFactor(2,2);

	jugadorDibujable1.setSprite(sprSubZeroQuieto);
	jugadorDibujable1.setSprite(sprSubZeroCaminando);
	jugadorDibujable1.setSprite(sprSubZeroCaminando);

	controladorJuego.setPersonaje(jugador1);
	controladorJuego.setPersonajeDibujable(jugadorDibujable1);
	// FIN CODIGO USUARIO
}

void Juego::render()
{
	VentanaGrafica::Instance()->dibujarTodo();
}

void Juego::update()
{
	// INICIO CODIGO USUARIO
	VentanaGrafica::Instance()->update();
	// FIN CODIGO USUARIO
}

void Juego::handleEvents()
{
	SDL_Event evento;

	// INICIO CODIGO USUARIO

	if (SDL_PollEvent(&evento))
	{
		if (evento.type == SDL_QUIT)
			juegoCorriendo = false;
		else{
			this->controladorJuego.manejar_Evento(evento);
		}
	}
}
/*
		else if( evento.type == SDL_KEYDOWN )
		{

			switch( evento.key.keysym.sym )
			{
				case SDLK_RIGHT:
					VentanaGrafica::Instance()->setSprite(sprSubZeroCaminando, "sprSubZero");
					sprSubZeroCaminando->setSentidoReproduccion(HACIA_ADELANTE);
					sprSubZeroCaminando->desplazar(Vector2(5,0));
					sprSubZeroQuieto->desplazar(Vector2(5,0));
				break;

				case SDLK_LEFT:
					VentanaGrafica::Instance()->setSprite(sprSubZeroCaminando, "sprSubZero");
					sprSubZeroCaminando->setSentidoReproduccion(HACIA_ATRAS);
					sprSubZeroCaminando->desplazar(Vector2(-5,0));
					sprSubZeroQuieto->desplazar(Vector2(-5,0));

				break;

			}
		}
		else
			VentanaGrafica::Instance()->setSprite(sprSubZeroQuieto, "sprSubZero");

	}
*/
	// FIN CODIGO USUARIO

void Juego::clean() {
	VentanaGrafica::Instance()->cerrar();
	GestorTexturas::Instance()->clean();
}

// a function to access the private running variable
bool Juego::running() { return juegoCorriendo; }



