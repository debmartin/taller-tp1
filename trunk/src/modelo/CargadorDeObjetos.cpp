/*
 * CargadorDeObjetos.cpp
 *
 *  Created on: 14/4/2015
 *      Author: val
 */

#include "CargadorDeObjetos.h"

#include <list>
#include <utility>

#include "../json/CapaDef.h"
#include "../json/EscenarioDef.h"
#include "../json/JugadorDef.h"
#include "../json/Parser.h"
#include "../json/PersonajeDef.h"
#include "../json/SpriteDef.h"
#include "../json/VentanaDef.h"
#include "../utils/Logger.h"
#include "../vista/Animacion.h"
#include "../vista/ArmaDibujable.h"
#include "../vista/Capa.h"
#include "../vista/EscenarioGrafico.h"
#include "../vista/Renderizador.h"
#include "../vista/Sprite.h"
#include "../vista/VentanaGrafica.h"
#include "Arma.h"
#include "Jugador.h"
#include "Vector2f.h"

CargadorDeOjbetos::CargadorDeOjbetos(string escenario_path) {

	////Inicialización desde Parser////
	this->parser = new Parser(escenario_path);
	if (!parser->parsearDesdeJson()) {
		parser->cargarJsonPorDefecto();
		parser->parsearDesdeJson();
	}

	////Inicializacion de VentanaGrafica////

	Vector2f tamanioVentanaPx(parser->getVentanaDef()->getAnchoPx(),
							  parser->getVentanaDef()->getAltoPx());

	Vector2f tamanioVentanaLogico(parser->getVentanaDef()->getAncho(),
								  parser->getEscenarioDef()->getAlto());

	bool exito = VentanaGrafica::Instance()->init(TITULO_VENTANA_INICIO,
												POS_VENTANA_INICIO, tamanioVentanaPx,
												tamanioVentanaLogico,
												INICIAR_FULLSCREEN);

	if (!exito) {
		Logger::getInstance()->error("Error al inicializar la VentanaGrafica");
	}

}

CargadorDeOjbetos::~CargadorDeOjbetos() {

}

map<string, Personaje*>* CargadorDeOjbetos::cargarPersonajes() {

	map<string, Personaje*>* personajes = new map<string, Personaje*>();
	Vector2f posicionTemporalPersonaje(parser->getEscenarioDef()->getAncho()/2, parser->getEscenarioDef()->getYpiso());

	for (list<PersonajeDef*>::iterator it = parser->getPersonajesDef()->begin() ; it != parser->getPersonajesDef()->end(); ++it)
	{
		Personaje* personaje = new Personaje((*it)->getId(), (*it)->getAncho(), (*it)->getAlto(), posicionTemporalPersonaje, VentanaGrafica::Instance(), 1, (*it)->getCajasCol());
		Arma* arma = new Arma((*it)->getArmaDef()->getVelocidad());
		cout<<(*it)->getArmaDef()->getVelocidad()<<endl;
		personaje->agregarArma(arma);
		personajes->insert( pair<string,Personaje*>((*it)->getId(),personaje) );
	}

	return personajes;
}

map<string, PersonajeDibujable*>* CargadorDeOjbetos::cargarPersonajesDibujables() {

	map<string, PersonajeDibujable*>* personajesDibujables = new map<string, PersonajeDibujable*>();
	Vector2f posicionTemporalPersonaje(parser->getEscenarioDef()->getAncho()/2, parser->getEscenarioDef()->getYpiso());

	for (list<PersonajeDef*>::iterator it = parser->getPersonajesDef()->begin() ; it != parser->getPersonajesDef()->end(); ++it)
	{
		PersonajeDibujable* personajeDibujableCargado = new PersonajeDibujable();

		////Inicializacion de PersonajeDibujable////
		Vector2f tamanioPx( (*it)->getAncho() * VentanaGrafica::Instance()->relacion_de_aspectoX(),
							(*it)->getAlto()  * VentanaGrafica::Instance()->relacion_de_aspectoY()
						  );

		list<SpriteDef*>* spritesDef = (*it)->getSpritesDef();
		list<SpriteDef*>::iterator it_sprites = spritesDef->begin();
		SpriteDef* primerSpriteSubQuieto;
		SpriteDef* spriteDefArma;
		spriteDefArma = (*it)->getArmaDef()->getSpriteDefArma();

		for (; it_sprites != spritesDef->end(); ++it_sprites) {
				if((*it_sprites)->getIdSprite() == ID_ZUBZERO_QUIETO){
					primerSpriteSubQuieto = *it_sprites;
				}
		}

		Animacion* SubQuieto = new Animacion(primerSpriteSubQuieto->getImagen(),
		primerSpriteSubQuieto->getCantFotogramas(),
		primerSpriteSubQuieto->getFps(),
		primerSpriteSubQuieto->getIdSprite(),
		Renderizador::Instance()->getRenderer());

		personajeDibujableCargado = new PersonajeDibujable(SubQuieto,posicionTemporalPersonaje, tamanioPx,
												ORIENTACION_IZQUIERDA, (*it)->getColorAlternativoDef());

		//Agrego armaDibujable
		Animacion* animacionArma = new Animacion(spriteDefArma->getImagen(),
		spriteDefArma->getCantFotogramas(),
		spriteDefArma->getFps(),
		spriteDefArma->getIdSprite(),
		Renderizador::Instance()->getRenderer());;
		Vector2f posicionInicialArma(0,0);

		Sprite* spriteArmaDibujable = new Sprite(animacionArma, posicionInicialArma, ORIENTACION_IZQUIERDA);
		ArmaDibujable* armaDibujable = new ArmaDibujable(spriteArmaDibujable);
		personajeDibujableCargado->agregarArma(armaDibujable);

		it_sprites = spritesDef->begin();
		for (; it_sprites != spritesDef->end(); ++it_sprites) {
			Animacion* sub_zero = new Animacion(
										(*it_sprites)->getImagen(),
										(*it_sprites)->getCantFotogramas(),
										(*it_sprites)->getFps(),
										(*it_sprites)->getIdSprite(),
										Renderizador::Instance()->getRenderer());
			personajeDibujableCargado->agregarAnimacion(sub_zero);
		}

		personajesDibujables->insert( pair<string,PersonajeDibujable*>((*it)->getId(),personajeDibujableCargado) );
	}

	return personajesDibujables;
}


void CargadorDeOjbetos::cargarEscenarioGrafico(PersonajeDibujable* personajeDibujable1, PersonajeDibujable* personajeDibujable2) {

	EscenarioGrafico* escenarioGraficoCargado = new EscenarioGrafico();

	// TODO validar que sean los mismo en los 2 jugadores
	int zindex_jugadores = 0;
	for (list<PersonajeDef*>::iterator it_personajesDef = parser->getPersonajesDef()->begin() ; it_personajesDef != parser->getPersonajesDef()->end(); it_personajesDef++)
	{
		zindex_jugadores = (*it_personajesDef)->getZindex();
	}

	Vector2f relacionAspectos =
			VentanaGrafica::Instance()->obtener_relacion_aspectos();

	////Inicializacion de capas////
	list<Capa*>* capas = new list<Capa*>();
	list<Dibujable*>* capasYPersonajes = new list<Dibujable*>();
	list<CapaDef*>* capasDef = parser->getCapasDef();

	for (list<CapaDef*>::iterator it_capas = capasDef->begin();
			it_capas != capasDef->end(); ++it_capas) {
		//Logger::getInstance()->info(*it_capas);
		Animacion* fondoAnim = new Animacion((*it_capas)->getImagenFondo(),
		CANT_FOTOGRAMAS_FONDO, FPS_FONDO, (*it_capas)->getIdCapa(),
				Renderizador::Instance()->getRenderer());
		Vector2f tamIniCapa((*it_capas)->getAncho(), parser->getEscenarioDef()->getAlto());
		Vector2f posInCapa = POSICION_INICIAL_CAPA;

		Capa* fondoCapa = new Capa(fondoAnim, tamIniCapa, posInCapa,
				relacionAspectos);
		capas->push_back(fondoCapa);
		capasYPersonajes->push_back(fondoCapa);

	}
	Logger::getInstance()->debug("Inicialiazación de Capas correcta.");

	list<Dibujable*>::iterator it_dibujables = capasYPersonajes->begin();
	for (int i=0; it_dibujables != capasYPersonajes->end() && i < zindex_jugadores; ++it_dibujables) {
		i++;
	}

	capasYPersonajes->insert(++it_dibujables, personajeDibujable1);
	capasYPersonajes->insert(it_dibujables, personajeDibujable2);

	////Inicializacion de EscenarioGrafico////
	Logger::getInstance()->info(parser->getEscenarioDef());
	escenarioGraficoCargado = new EscenarioGrafico(parser->getEscenarioDef()->getAncho(),
			parser->getEscenarioDef()->getAlto(), parser->getEscenarioDef()->getYpiso(), capasYPersonajes,
			capas);

	VentanaGrafica::Instance()->agregarEscenario(escenarioGraficoCargado);
	VentanaGrafica::Instance()->centrar_ventana();
	escenarioGraficoCargado->centrar_dibujables(zindex_jugadores);

	Logger::getInstance()->debug("Termina la carga del juego correctamente.");

}

Jugador* CargadorDeOjbetos::cargarJugador(JugadorDef* jugadorDef)
{
	string idPersonaje = jugadorDef->getIdPersonaje();

	Personaje* personaje = this->cargarPersonajes()->find(idPersonaje)->second;
	PersonajeDibujable* personajeDibujable = this->cargarPersonajesDibujables()->find(idPersonaje)->second;

	((Arma*)personaje->getArma())->agregarObservador(personajeDibujable->getArma());

	Jugador* jugador = new Jugador(personaje, personajeDibujable);

	return jugador;

}

Jugador* CargadorDeOjbetos::cargarJugador1() {

	list<JugadorDef*>::iterator it = parser->getJugadoresDef()->begin();
	Jugador* jugador = cargarJugador(*it);
	return jugador;
}

Jugador* CargadorDeOjbetos::cargarJugador2() {

	list<JugadorDef*>::iterator it = parser->getJugadoresDef()->begin();
	Jugador* jugador = cargarJugador(*++it);
	return jugador;
}

map<estado_personaje, BVH*>* CargadorDeOjbetos::cargarCajasColision(){
	vector<AABB*>* aabb;
	BVH* bvh = new BVH(aabb);

	//TODO: Val. Falta completar.
}
