/*
 * CargadorDeObjetos.h
 *
 *  Created on: 14/4/2015
 *      Author: val
 */

#ifndef SRC_MODELO_CARGADORDEOBJETOS_H_
#define SRC_MODELO_CARGADORDEOBJETOS_H_

#include <map>
#include <string>

#include "../vista/PersonajeDibujable.h"
#include "../controlador/ControladorJoystickMenu.h"
#include "Combo.h"
#include "MapaDeCombos.h"
#include "estado/Estado.h"
#include "fisica/BVH.h"
#include "Personaje.h"
#include "PersonajeInteligente.h"

class JugadorDef;

class Jugador;

class EscenarioGrafico;
class Parser;
class Personaje;
class PersonajeDibujable;

#define TITULO_VENTANA_INICIO "Mortal Kombat"
#define INICIAR_FULLSCREEN false
#define POS_VENTANA_INICIO Vector2f(100, 100)
#define POSICION_INICIAL_CAPA Vector2f(0, 0)
#define CANT_FOTOGRAMAS_FONDO 1
#define FPS_FONDO 1

using namespace std;

class CargadorDeOjbetos{
private:
	Parser* parser;
	string idPersonaje1Elegido;
	string idPersonaje2Elegido;
	string modo_juego;
	string nombrePersonajeElegido1;
	string nombrePersonajeElegido2;
public:
	CargadorDeOjbetos(string escenario_path);
	virtual ~CargadorDeOjbetos();

	map<string, Personaje*>* cargarPersonajes();
	map<string, PersonajeDibujable*>* cargarPersonajesDibujables();
	void cargarEscenarioGrafico(PersonajeDibujable* personajeDibujable1, PersonajeDibujable* personajeDibujable2);
	Jugador* cargarJugador1();
	Jugador* cargarJugador2();
	map<estado_personaje, BVH*>* cargarCajasColisionPersonaje(float ancho_logico_personaje, float alto_logico_personaje);
	BVH* cargarCajasColisionArmaPersonaje(float ancho_logico_arma, float alto_logico_arma);
	void cargarInfo_desdeMenus();
	string getIdPersonaje1Elegido() const;
	string getIdPersonaje2Elegido() const;
	vector<Combo*>* cargarCombos(string nombrePersonaje);
	string verModoDeJuego();
private:
	Jugador* cargarJugador(JugadorDef* jugadorDef);

};

#endif /* SRC_MODELO_CARGADORDEOBJETOS_H_ */
