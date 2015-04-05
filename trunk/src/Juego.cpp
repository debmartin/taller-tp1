/*
 * Juego.cpp
 *
 *  Created on: 27/3/2015
 *      Author: val
 */

#include "Juego.h"
#include <cstddef>
#include <SDL2/SDL.h> //TODO: Solo para tests

#include "vista/GestorAnimaciones.h"
#include "vista/VentanaGrafica.h"
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

	// Cargar Animaciones al GestorAnimaciones
	exito = GestorAnimaciones::Instance()->cargarAnimacion("screen-pit.png", 1, 1,  "screen-pit", VentanaGrafica::Instance()->getRenderer());
	if (!exito) {
		cout << "ERRROR AL CREAR TEXTURA" << endl;
		exit(1);
	}

	exito = GestorAnimaciones::Instance()->cargarAnimacion("zubzero-quieto.png", 12, 10,  "zubzero-quieto", VentanaGrafica::Instance()->getRenderer());
	if (!exito) {
		cout << "ERRROR AL CREAR TEXTURA" << endl;
		exit(1);
	}

	exito = GestorAnimaciones::Instance()->cargarAnimacion("zubzero-caminando.png", 9, 10, "zubzero-caminando", VentanaGrafica::Instance()->getRenderer());
	if (!exito) {
		cout << "ERRROR AL CREAR TEXTURA" << endl;
		exit(1);
	}

	// Cargar Sprite SPRPIT en VentanaGrafica
	Sprite* sprPit;
	sprPit = new Sprite("screen-pit", Vector2(0, 0), 1.0f);
	sprPit->escalarConTamanio(640,480);
	VentanaGrafica::Instance()->setSprite(sprPit, "sprPit");

	// Cargar Sprite SUBZERO en VentanaGrafica
	subzero = new Sprite("zubzero-quieto", Vector2(100, 195), 2.0f);
	subzero->escalarConFactor(2.0f,2.0f);
	VentanaGrafica::Instance()->setSprite(subzero, "subzero");

	// Configuracion del controlador
	this->jugadorDibujable1.setSprite(subzero);
	this->controladorJuego.setPersonaje(jugador1);
	this->controladorJuego.setPersonajeDibujable(jugadorDibujable1);
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
	GestorAnimaciones::Instance()->clean();
}

// a function to access the private running variable
bool Juego::running() { return juegoCorriendo; }


