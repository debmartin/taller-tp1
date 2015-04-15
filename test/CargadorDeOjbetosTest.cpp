/*
 * CargadorDeOjbetosTest.cpp
 *
 *  Created on: 14/4/2015
 *      Author: ariel
 */

#include "CargadorDeOjbetosTest.h"

#include <iostream>
#include <list>

#include "../src/json/CapaDef.h"
#include "../src/json/EscenarioDef.h"
#include "../src/json/Parser.h"
#include "../src/json/PersonajeDef.h"
#include "../src/json/SpriteDef.h"
#include "../src/json/VentanaDef.h"
#include "../src/modelo/Personaje.h"
#include "../src/modelo/Vector2f.h"
#include "../src/utils/Logger.h"
#include "../src/vista/Animacion.h"
#include "../src/vista/Capa.h"
#include "../src/vista/EscenarioGrafico.h"
#include "../src/vista/PersonajeDibujable.h"
#include "../src/vista/Renderizador.h"
#include "../src/vista/Sprite.h"
#include "../src/vista/VentanaGrafica.h"

#define TITULO_VENTANA_INICIO "Taller de programacion TP: Mortal Kombat"
#define INICIAR_FULLSCREEN false
#define POSICION_INICIAL_PERSONAJE Vector2f(750, 100)
#define POS_VENTANA_INICIO Vector2f(100, 100)
#define POSICION_INICIAL_CAPA Vector2f(0, 0)
#define CANT_FOTOGRAMAS_FONDO 1
#define FPS_FONDO 1

CargadorDeOjbetosTest::CargadorDeOjbetosTest() {
	// TODO Auto-generated constructor stub

}

void CargadorDeOjbetosTest::ejecutar() {



}

CargadorDeOjbetosTest::~CargadorDeOjbetosTest() {
	// TODO Auto-generated destructor stub
}

