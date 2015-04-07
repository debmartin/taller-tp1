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
#include "vista/Sprite.h"

#define TEXTO_ERROR_TEXTURA "ERROR AL CREAR TEXTURA"

// simply set the running variable to true
Juego::Juego(VentanaGrafica* ventana, EscenarioGrafico* escenario, Personaje* pers, PersonajeDibujable* persDib) :
    ventanaG(ventana), escenarioG(escenario), jugador1(pers), jugadorDibujable1(persDib){

	juegoCorriendo = true; // everything inited successfully, start the main loop

	// INICIO CODIGO USUARIO

	// Cargar Animaciones al GestorAnimaciones
//	bool exito = GestorAnimaciones::Instance()->cargarAnimacion(IMAGEN_FONDO, 1, 1,  ID_FONDO, ventanaG->getRenderer());
//	if (!exito) {
//		cout << TEXTO_ERROR_TEXTURA << endl;
//		exit(1);
//	}
//
//	exito = GestorAnimaciones::Instance()->cargarAnimacion(IMAGEN_ZUBZERO_QUIETO, 12, 10,  ID_ZUBZERO_QUIETO, ventanaG->getRenderer());
//	if (!exito) {
//		cout << TEXTO_ERROR_TEXTURA << endl;
//		exit(1);
//	}
//
//	exito = GestorAnimaciones::Instance()->cargarAnimacion(IMAGEN_ZUBZERO_CAMINANDO, 9, 10, ID_ZUBZERO_CAMINANDO, ventanaG->getRenderer());
//	if (!exito) {
//		cout << TEXTO_ERROR_TEXTURA << endl;
//		exit(1);
//	}

//	// Cargar Sprite SPRPIT en VentanaGrafica
//	Sprite* sprPit;
//	sprPit = new Sprite("screen-pit", Vector2(0, 0), 1.0f);
//	sprPit->escalarConTamanio(640,480);
//	VentanaGrafica::Instance()->setSprite(sprPit, "sprPit");
//
//	// Cargar Sprite SUBZERO en VentanaGrafica
//	subzero = new Sprite("zubzero-quieto", Vector2(100, 195), 2.0f);
//	subzero->escalarConFactor(2.0f,2.0f);
//	VentanaGrafica::Instance()->setSprite(subzero, "subzero");
//
//	// Configuracion del controlador
//	this->jugadorDibujable1.setSprite(subzero);
	this->controladorJuego = new Controlador(jugador1);
//	this->controladorJuego.setPersonajeDibujable(jugadorDibujable1);
	// FIN CODIGO USUARIO

}

void Juego::render()
{
	VentanaGrafica::Instance()->dibujarTodo();
}

void Juego::update()
{
	// INICIO CODIGO USUARIO
	VentanaGrafica::Instance()->actualizar();
	// FIN CODIGO USUARIO
}

void Juego::handleEvents()
{
	SDL_Event evento;

	// INICIO CODIGO USUARIO

	if (SDL_PollEvent(&evento))
	{
		if (evento.type == SDL_QUIT){
			juegoCorriendo = false;
		}
		else{
			this->controladorJuego->manejar_Evento(evento);
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
}

// a function to access the private running variable
bool Juego::running() { return juegoCorriendo; }

Juego::~Juego(){
    ventanaG->~VentanaGrafica();
}


