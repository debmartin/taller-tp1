/*
 * CargadorDeObjetos.h
 *
 *  Created on: 14/4/2015
 *      Author: val
 */

#ifndef SRC_MODELO_CARGADORDEOBJETOS_H_
#define SRC_MODELO_CARGADORDEOBJETOS_H_

#include <list>
#include <string>

#include "../vista/PersonajeDibujable.h"
#include "Personaje.h"

class EscenarioGrafico;
class Parser;
class Personaje;
class PersonajeDibujable;

#define TITULO_VENTANA_INICIO "Taller de programacion TP: Mortal Kombat"
#define INICIAR_FULLSCREEN false
#define POS_VENTANA_INICIO Vector2f(100, 100)
#define POSICION_INICIAL_CAPA Vector2f(0, 0)
#define CANT_FOTOGRAMAS_FONDO 1
#define FPS_FONDO 1

using namespace std;

class CargadorDeOjbetos{
private:
	Parser* parser;
public:
	CargadorDeOjbetos(string escenario_path);
	virtual ~CargadorDeOjbetos();

	Personaje* cargarPersonaje();
	PersonajeDibujable* cargarPersonajeDibujable();
	// TODO ver como no pasarte este parametros (ariel)
	EscenarioGrafico* cargarEscenarioGrafico(PersonajeDibujable* personajeDibujable);

	list<Personaje*>* cargarPersonajes();
	list<PersonajeDibujable*>* cargarPersonajesDibujables();
	EscenarioGrafico* cargarEscenarioGrafico(list<PersonajeDibujable*>* personajesDibujables);

};

#endif /* SRC_MODELO_CARGADORDEOBJETOS_H_ */
