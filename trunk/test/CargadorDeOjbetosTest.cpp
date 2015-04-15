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

	Logger::getInstance()->info("Incia el test para el CargadorDeOjbetos");

	EscenarioGrafico* escenario;
	Personaje* jugador;
	PersonajeDibujable* personajeDibujable;


	////Inicialización desde Parser////
	Parser* parser = new Parser("src/recursos/escenario.json");
	parser->parsearDesdeJson();
	VentanaDef* ventanaDef = parser->getVentanaDef();
	EscenarioDef* escenarioDef = parser->getEscenarioDef();
	PersonajeDef* personajeDef = parser->getPersonajeDef();

	////Inicializacion de VentanaGrafica////
    Vector2f tamanioVentanaPx(ventanaDef->getAnchoPx(), ventanaDef->getAltoPx());
    Vector2f tamanioVentanaLogico(ventanaDef->getAncho(), escenarioDef->getAlto());

    bool exito = VentanaGrafica::Instance()->init(TITULO_VENTANA_INICIO, POS_VENTANA_INICIO, tamanioVentanaPx, tamanioVentanaLogico, INICIAR_FULLSCREEN);

    if (! exito){
    	Logger::getInstance()->error("Error al inicializar la VentanaGrafica");
    }else{
    	Logger::getInstance()->info("Inicialiazación de VentanaGrafica correcta.");
    }

	Vector2f relacionAspectos = VentanaGrafica::Instance()->obtener_relacion_aspectos();


	////Inicializacion de capas////
	list<Capa*> capas;
	list<Dibujable*> capasYPersonajes;
	for (list<CapaDef*>::iterator it_capas = parser->getCapasDef()->begin() ; it_capas != parser->getCapasDef()->end(); it_capas++)
	{
		cout<<**it_capas<<endl;

		Animacion fondoAnim((*it_capas)->getImagenFondo(), CANT_FOTOGRAMAS_FONDO, FPS_FONDO, (*it_capas)->getIdCapa(), Renderizador::Instance()->getRenderer());
		Vector2f tamIniCapa((*it_capas)->getAncho(), escenarioDef->getAlto());
		Vector2f posInCapa = POSICION_INICIAL_CAPA;

		Capa fondoCapa(&fondoAnim, tamIniCapa, posInCapa, relacionAspectos);
		capas.push_back(&fondoCapa);
		capasYPersonajes.push_back(&fondoCapa);

	}
	Logger::getInstance()->info("Inicialiazación de Capas correcta.");


	////Inicializacion de Personaje////
	Logger::getInstance()->info("Inicialiazación de Personaje.");

	Personaje jugador1(personajeDef->getAncho(), personajeDef->getAlto(), POSICION_INICIAL_PERSONAJE, VentanaGrafica::Instance());
	jugador = &jugador1;


	////Inicializacion de PersonajeDibujable////
	Vector2f tamanioPx(
    		jugador->getAncho()*VentanaGrafica::Instance()->relacion_de_aspectoX(),
			jugador->getAlto()*VentanaGrafica::Instance()->relacion_de_aspectoY());

	SpriteDef* primerSpriteSubQuieto = *(personajeDef->getSpritesDef()->begin());
	Animacion SubQuieto(primerSpriteSubQuieto->getImagen(), primerSpriteSubQuieto->getCantFotogramas(), primerSpriteSubQuieto->getFps(),  primerSpriteSubQuieto->getIdSprite(), Renderizador::Instance()->getRenderer());
	PersonajeDibujable personajeDibujable1(&SubQuieto, POSICION_INICIAL_PERSONAJE, tamanioPx, ORIENTACION_IZQUIERDA);

	for (list<SpriteDef*>::iterator it_sprites = personajeDef->getSpritesDef()->begin() ; it_sprites != personajeDef->getSpritesDef()->end(); it_sprites++)
	{
		Animacion sub_zero((*it_sprites)->getImagen(), (*it_sprites)->getCantFotogramas(), (*it_sprites)->getFps(), primerSpriteSubQuieto->getIdSprite(), Renderizador::Instance()->getRenderer());
		personajeDibujable1.agregarAnimacion(&sub_zero);
	}

	personajeDibujable = &personajeDibujable1;
	Logger::getInstance()->info("Inicialiazación de PersonajeDibujable correcta.");

	capasYPersonajes.push_back(&personajeDibujable1);

	////Inicializacion de EscenarioGrafico////
	EscenarioGrafico escenarioDibujable(escenarioDef->getAncho(), escenarioDef->getAlto(), escenarioDef->getYpiso(), &capasYPersonajes, &capas);
    escenario = &escenarioDibujable;
	Logger::getInstance()->info("Inicializacion de EscenarioGrafico correcta.");


	VentanaGrafica::Instance()->agregarEscenario(&escenarioDibujable);
    VentanaGrafica::Instance()->centrar_ventana();

    escenario->centrar_dibujables();

    Vector2f vector_centrado(escenarioDef->getAncho()/2.0, escenarioDef->getYpiso());
    jugador->centrar_en(vector_centrado);
    Logger::getInstance()->info("Carga correcta.");
    cout << "carga correcta" << endl;


}

CargadorDeOjbetosTest::~CargadorDeOjbetosTest() {
	// TODO Auto-generated destructor stub
}

