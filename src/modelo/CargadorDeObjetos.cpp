/*
 * CargadorDeObjetos.cpp
 *
 *  Created on: 14/4/2015
 *      Author: val
 */

#include "CargadorDeObjetos.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>

#include "../json/CapaDef.h"
#include "../json/ColorAlternativoDef.h"
#include "../json/EscenarioDef.h"
#include "../json/JugadorDef.h"
#include "../json/Parser.h"
#include "../json/PersonajeDef.h"
#include "../json/SpriteDef.h"
#include "../json/VentanaDef.h"
#include "../utils/Logger.h"
#include "../vista/Animacion.h"
#include "../vista/Capa.h"
#include "../vista/EscenarioGrafico.h"
#include "../vista/Renderizador.h"
#include "../vista/Sprite.h"
#include "../vista/VentanaGrafica.h"
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

list<Personaje*>* CargadorDeOjbetos::cargarPersonajes() {
	list<Personaje*>* personajes = new list<Personaje*>();

	for (list<PersonajeDef*>::iterator it = parser->getPersonajesDef()->begin() ; it != parser->getPersonajesDef()->end(); ++it)
	{
		//Logger::getInstance()->info(*it);
		Personaje* personaje = new Personaje((*it)->getAncho(), (*it)->getAlto(), (*it)->getPosicionInicial(), VentanaGrafica::Instance());
		personajes->push_back(personaje);
	}


	return personajes;
}

list<PersonajeDibujable*>* CargadorDeOjbetos::cargarPersonajesDibujables() {

	//para test de elegir el color alternativo al personaje cuando corresponda
	for (list<JugadorDef*>::iterator it = parser->getJugadoresDef()->begin() ; it != parser->getJugadoresDef()->end(); ++it)
	{
		Logger::getInstance()->error(*it);
	}

	list<PersonajeDibujable*>* personajesDibujables = new list<PersonajeDibujable*>();

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

		for (; it_sprites != spritesDef->end(); ++it_sprites) {
				if((*it_sprites)->getIdSprite() == ID_ZUBZERO_QUIETO){
					primerSpriteSubQuieto = *it_sprites;
				}
		}

		//cout << "*CargadorDeOjbetos::cargarObjetos>getIdSprite:" << primerSpriteSubQuieto->getIdSprite() << endl;
		Animacion* SubQuieto = new Animacion(primerSpriteSubQuieto->getImagen(),
		primerSpriteSubQuieto->getCantFotogramas(),
		primerSpriteSubQuieto->getFps(),
		primerSpriteSubQuieto->getIdSprite(),
		Renderizador::Instance()->getRenderer());

		OrientacionSprite direccion;
		if ((*it)->getDireccion() == 1) {
			direccion = ORIENTACION_DERECHA;
		} else {
			direccion = ORIENTACION_IZQUIERDA;
		}

		personajeDibujableCargado = new PersonajeDibujable(SubQuieto,
				(*it)->getPosicionInicial(), tamanioPx, direccion);

		Uint16 color_alternativo_hinicial = (*it)->getColorAlternativoDef()->getHinicial();
		Uint16 color_alternativo_hfinal = (*it)->getColorAlternativoDef()->getHfinal();
		Uint16 color_alternativo_desplazamiento = (*it)->getColorAlternativoDef()->getDesplazamiento();

		//TODO: Val. Separar la carga de los personajes para poder setearles el color.
		it_sprites = spritesDef->begin();
		for (; it_sprites != spritesDef->end(); ++it_sprites) {
			//cout << "FOR-ID:" << (*it_sprites)->getIdSprite() << endl;
			Animacion* sub_zero = new Animacion(
										(*it_sprites)->getImagen(),
										(*it_sprites)->getCantFotogramas(),
										(*it_sprites)->getFps(),
										(*it_sprites)->getIdSprite(),
										Renderizador::Instance()->getRenderer(),
										color_alternativo_hinicial,
										color_alternativo_hfinal,
										color_alternativo_desplazamiento);
			personajeDibujableCargado->agregarAnimacion(sub_zero);
		}

		personajesDibujables->push_back(personajeDibujableCargado);
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

