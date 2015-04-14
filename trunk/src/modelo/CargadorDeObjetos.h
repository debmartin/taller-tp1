/*
 * CargadorDeObjetos.h
 *
 *  Created on: 14/4/2015
 *      Author: val
 */

#ifndef SRC_MODELO_CARGADORDEOBJETOS_H_
#define SRC_MODELO_CARGADORDEOBJETOS_H_

#include "../json/Parser.h"
#include "../utils/Logger.h"
#include "../json/EscenarioDef.h"
#include "../json/VentanaDef.h"
#include "../json/PersonajeDef.h"
#include "../vista/VentanaGrafica.h"
#include "../vista/EscenarioGrafico.h"
#include "../vista/Capa.h"
#include "../modelo/Personaje.h"
#include "../vista/PersonajeDibujable.h"
#include "../vista/Sprite.h"

#include <jsoncpp/json/json.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string.h>

#define TITULO_VENTANA_INICIO "Taller de programacion TP: Mortal Kombat"
#define INICIAR_FULLSCREEN false
#define POSICION_INICIAL_PERSONAJE Vector2f(750, 100)
#define POS_VENTANA_INICIO Vector2f(100, 100)
#define POSICION_INICIAL_CAPA Vector2f(0, 0)
#define CANT_FOTOGRAMAS_FONDO 1
#define FPS_FONDO 1

using namespace std;

class CargadorDeOjbetos{
private:
	EscenarioGrafico* escenario;
	Personaje* jugador;
	PersonajeDibujable* personajeDibujable;

public:
	CargadorDeOjbetos();
	virtual ~CargadorDeOjbetos();
	void cargarObjetos();
	EscenarioGrafico* getEscenarioGrafico();
	Personaje* getPersonaje();
	PersonajeDibujable* getPersonajeDibujable();
};

#endif /* SRC_MODELO_CARGADORDEOBJETOS_H_ */
