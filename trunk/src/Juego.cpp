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

Juego::Juego(VentanaGrafica* ventana, EscenarioGrafico* escenario, Personaje* personaje, PersonajeDibujable* personajeDib) :
    escenarioG(escenario), jugador1(personaje), jugadorDibujable1(personajeDib){

	juegoCorriendo = true;

	//Agrego observadores del Personaje.
	personaje->agregarObservador(personajeDib);
	personaje->agregarObservador(ventana);

	this->controladorJuego = new Controlador(this->jugador1);
}

void Juego::render()
{
	VentanaGrafica::Instance()->dibujarTodo();
}

void Juego::update()
{
	// INICIO CODIGO USUARIO
	this->jugador1->update();
	VentanaGrafica::Instance()->actualizar();
	// FIN CODIGO USUARIO
    cout << "=====================Juego::update===================" << endl;
    cout << "ESCENARIO->alto-logico:" << escenarioG->getAltoLogico() << endl;
    cout << "ESCENARIO->ancho-logico:" << escenarioG->getAnchoLogico() << endl;
    cout << "ESCENARIO->y-piso-logico:" << escenarioG->getYPisoLogico() << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "VENTANA-GRAFICA->limite logico Izquierdo:" << VentanaGrafica::Instance()->getLimiteLogicoIzquierdo() << endl;
    cout << "VENTANA-GRAFICA->limite logico Derecho:" << VentanaGrafica::Instance()->getLimiteLogicoDerecho() << endl;
    cout << "VENTANA-GRAFICA->relacion de aspecto X:" << VentanaGrafica::Instance()->relacion_de_aspectoX() << endl;
    cout << "VENTANA-GRAFICA->relacion de aspecto Y:" << VentanaGrafica::Instance()->relacion_de_aspectoY() << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "PERSONAJE-LOGICO->posicion-logica-X:" << jugador1->getPosicion().X() << endl;
    cout << "PERSONAJE-LOGICO->posicion-logica-Y:" << jugador1->getPosicion().Y() << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "PERSONAJE-DIBUJABLE->SPRITE->posicionPx-X:" << jugadorDibujable1->_getSprite()->getPosicion().X() << endl;
    cout << "PERSONAJE-DIBUJABLE->SPRITE->posicionPx-Y:" << jugadorDibujable1->_getSprite()->getPosicion().Y() << endl;
    cout << "PERSONAJE-DIBUJABLE->SPRITE->AnchoPx:" << jugadorDibujable1->_getSprite()->getAnchoPx() << endl;
    cout << "PERSONAJE-DIBUJABLE->SPRITE->AltoPx:" << jugadorDibujable1->_getSprite()->getAltoPx() << endl;
    cout << "=====================================================" << endl;
}

void Juego::handleEvents(bool& recargar)
{
	SDL_Event evento;

	// INICIO CODIGO USUARIO

	if (SDL_PollEvent(&evento))
	{
		if (evento.type == SDL_QUIT){
			juegoCorriendo = false;
		} else if (jugador1->estaSaltando()){
		    return;
		} else if (! controladorJuego->manejar_Evento(evento)){
            juegoCorriendo = false;
            recargar = true;
		}
	}
}

// a function to access the private running variable
bool Juego::running() { return juegoCorriendo; }

Juego::~Juego(){
    delete controladorJuego;
//    delete VentanaGrafica::Instance();
//    delete jugadorDibujable1;
//    delete jugador1;
//    delete escenarioG;
}


