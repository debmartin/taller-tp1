/*
 * CargadorDeObjetos.cpp
 *
 *  Created on: 14/4/2015
 *      Author: val
 */

#include "CargadorDeObjetos.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <list>
#include <utility>
#include <vector>

#include "../controlador/ControladorJoystick.h"
#include "../controlador/ControlJoystick.h"
#include "../controlador/ControlTeclado.h"
#include "../json/ArmaDef.h"
#include "../json/CapaDef.h"
#include "../json/ControlDef.h"
#include "../json/EscenarioDef.h"
#include "../json/JugadorDef.h"
#include "../json/Parser.h"
#include "../json/PersonajeDef.h"
#include "../json/SpriteDef.h"
#include "../json/VentanaDef.h"
#include "../menus/PantallaSeleccionarModo.h"
#include "../menus/PantallaSeleccionarPersonaje.h"
#include "../utils/Logger.h"
#include "../vista/Animacion.h"
#include "../vista/ArmaDibujable.h"
#include "../vista/Capa.h"
#include "../vista/EscenarioGrafico.h"
#include "../vista/Renderizador.h"
#include "../vista/Sprite.h"
#include "../vista/VentanaGrafica.h"
#include "Arma.h"
#include "CajasColision.h"
#include "fisica/AABB.h"
#include "Jugador.h"
#include "Objeto.h"
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
		//cout<<"Ancho personaje:"<<(*it)->getAncho()<<";;;; Alto personaje:"<<(*it)->getAlto()<<endl;
		(*it)->agregarCajasDeColisiones(cargarCajasColisionPersonaje((*it)->getAncho(), (*it)->getAlto()));
		Personaje* personaje = new Personaje((*it)->getId(), (*it)->getAncho(), (*it)->getAlto(), posicionTemporalPersonaje, VentanaGrafica::Instance(), NUMERO_DE_PERSONAJE_1, (*it)->getCajasCol());
		Arma* arma = new Arma((*it)->getArmaDef()->getVelocidad(), (*it)->getArmaDef()->getAncho(), (*it)->getArmaDef()->getAlto(), cargarCajasColisionArmaPersonaje((*it)->getArmaDef()->getAncho(),(*it)->getArmaDef()->getAlto()));
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
				if((*it_sprites)->getIdSprite() == ID_PERSONAJE_REPOSO){
					primerSpriteSubQuieto = *it_sprites;
				}
		}

		Animacion* SubQuieto = new Animacion(
										Renderizador::Instance()->getRenderer(),
										primerSpriteSubQuieto->getImagen(),
										primerSpriteSubQuieto->getCantFotogramas(),
										primerSpriteSubQuieto->getFps(),
										primerSpriteSubQuieto->getIdSprite());

		personajeDibujableCargado = new PersonajeDibujable(
													SubQuieto,
													posicionTemporalPersonaje,
													tamanioPx,
													ORIENTACION_IZQUIERDA,
													(*it)->getColorAlternativoDef());

		//Agrego armaDibujable
		Animacion* animacionArma = new Animacion(
										Renderizador::Instance()->getRenderer(),
										spriteDefArma->getImagen(),
										spriteDefArma->getCantFotogramas(),
										spriteDefArma->getFps(),
										spriteDefArma->getIdSprite());

		Vector2f posicionInicialArma(0,0);
		Vector2f tamanioArmaPx( (*it)->getArmaDef()->getAncho() * VentanaGrafica::Instance()->relacion_de_aspectoX(),
											(*it)->getArmaDef()->getAlto()  * VentanaGrafica::Instance()->relacion_de_aspectoY()
										  );

		ArmaDibujable* armaDibujable = new ArmaDibujable(animacionArma, posicionInicialArma, tamanioArmaPx, ORIENTACION_IZQUIERDA);
		personajeDibujableCargado->agregarArma(armaDibujable);

		it_sprites = spritesDef->begin();
		for (; it_sprites != spritesDef->end(); ++it_sprites) {
			Animacion* sub_zero = new Animacion(
										Renderizador::Instance()->getRenderer(),
										(*it_sprites)->getImagen(),
										(*it_sprites)->getCantFotogramas(),
										(*it_sprites)->getFps(),
										(*it_sprites)->getIdSprite());
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
		Animacion* fondoAnim = new Animacion(
									Renderizador::Instance()->getRenderer(),
									(*it_capas)->getImagenFondo(),
									CANT_FOTOGRAMAS_FONDO,
									FPS_FONDO,
									(*it_capas)->getIdCapa());
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
/*
	if(this->modo_juego == "P1_vs_CPU"){
		PersonajeInteligente* personaje = this->cargarPersonajes()->find(idPersonaje)->second;
		PersonajeDibujable* personajeDibujable = this->cargarPersonajesDibujables()->find(idPersonaje)->second;

		((Arma*)personaje->getArma())->agregarObservador(personajeDibujable->getArma());

		// by ariel: se puede usar tambien ControlTeclado
		string tipo_control = jugadorDef->getTipoControl();
		Control* control;
		if ( tipo_control == "TECLADO" )
		{
			control = new ControlTeclado(jugadorDef->getControlDef());
		}
		else
		{
			control = new ControlJoystick(jugadorDef->getControlDef());
		}

		//Cargo los combos del jugador.
		vector<Combo*>* vectorDeCombos = cargarCombos(idPersonaje);
		MapaDeCombos* mapaDeCombos = new MapaDeCombos(vectorDeCombos, jugadorDef->getTolerancia());
		Jugador* jugador = new Jugador(personaje, personajeDibujable, control, tipo_control, mapaDeCombos);

		return jugador;
	}else{*/
		Personaje* personaje = this->cargarPersonajes()->find(idPersonaje)->second;
		PersonajeDibujable* personajeDibujable = this->cargarPersonajesDibujables()->find(idPersonaje)->second;

		((Arma*)personaje->getArma())->agregarObservador(personajeDibujable->getArma());

		// by ariel: se puede usar tambien ControlTeclado
		string tipo_control = jugadorDef->getTipoControl();
		Control* control;
		if ( tipo_control == "TECLADO" )
		{
			control = new ControlTeclado(jugadorDef->getControlDef());
		}
		else
		{
			control = new ControlJoystick(jugadorDef->getControlDef());
		}

		//Cargo los combos del jugador.
		vector<Combo*>* vectorDeCombos = cargarCombos(idPersonaje);
		MapaDeCombos* mapaDeCombos = new MapaDeCombos(vectorDeCombos, jugadorDef->getTolerancia());
		Jugador* jugador = new Jugador(personaje, personajeDibujable, control, tipo_control, mapaDeCombos);

		return jugador;
	//}
}

Jugador* CargadorDeOjbetos::cargarJugador1() {

	list<JugadorDef*>::iterator it = parser->getJugadoresDef()->begin();
	JugadorDef* jugadorDef1 = *it;

	jugadorDef1->cargarIdPersonajeDesdeMenu(this->getIdPersonaje1Elegido());

	Jugador* jugador = cargarJugador(jugadorDef1);
	jugador->getPersonaje()->getArma()->orientar(DIRECCION_IZQUIERDA);
	return jugador;
}

Jugador* CargadorDeOjbetos::cargarJugador2() {

	list<JugadorDef*>::iterator it = parser->getJugadoresDef()->begin();
	JugadorDef* jugadorDef2 = *++it;

	jugadorDef2->cargarIdPersonajeDesdeMenu(this->getIdPersonaje2Elegido());

	Jugador* jugador = cargarJugador(jugadorDef2);
	jugador->getPersonaje()->cambiarNumeroPersonaje();
	return jugador;
}

map<estado_personaje, BVH*>* CargadorDeOjbetos::cargarCajasColisionPersonaje(float ancho_logico_personaje, float alto_logico_personaje){
	vector<AABB*>* cajasAABB_reposo = new vector<AABB*>;
	vector<AABB*>* cajasAABB_salto_diagonal = new vector<AABB*>;
	vector<AABB*>* cajasAABB_salto_vertical = new vector<AABB*>;
	vector<AABB*>* cajasAABB_patada_alta = new vector<AABB*>;
	vector<AABB*>* cajasAABB_patada_baja = new vector<AABB*>;
	vector<AABB*>* cajasAABB_patada_alta_agachado = new vector<AABB*>;
	vector<AABB*>* cajasAABB_patada_saltando_vertical = new vector<AABB*>;
	vector<AABB*>* cajasAABB_patada_saltando_diagonal_derecha = new vector<AABB*>;
	vector<AABB*>* cajasAABB_patada_saltando_diagonal_izquierda = new vector<AABB*>;
	vector<AABB*>* cajasAABB_pinia_alta = new vector<AABB*>;
	vector<AABB*>* cajasAABB_pinia_baja = new vector<AABB*>;
	vector<AABB*>* cajasAABB_pinia_saltando_diagonal_derecha = new vector<AABB*>;
	vector<AABB*>* cajasAABB_pinia_saltando_diagonal_izquierda = new vector<AABB*>;
	vector<AABB*>* cajasAABB_pinia_saltando_vertical = new vector<AABB*>;
	vector<AABB*>* cajasAABB_agachado = new vector<AABB*>;
	vector<AABB*>* cajasAABB_defendiendo_agachado = new vector<AABB*>;
	vector<AABB*>* cajasAABB_gancho = new vector<AABB*>;
	vector<AABB*>* cajasAABB_golpeado = new vector<AABB*>;
	vector<AABB*>* cajasAABB_caida_derecha = new vector<AABB*>;
	vector<AABB*>* cajasAABB_caida_izquierda = new vector<AABB*>;
	vector<AABB*>* cajasAABB_tirando_poder = new vector<AABB*>;

	//REPOSO//
	Vector2f reposo_caja1_PuntoMin(REPOSO_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, REPOSO_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f reposo_caja1_PuntoMax(REPOSO_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, REPOSO_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	Vector2f reposo_caja2_PuntoMin(REPOSO_CAJA2_X1_PORCENTUAL*ancho_logico_personaje, REPOSO_CAJA2_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f reposo_caja2_PuntoMax(REPOSO_CAJA2_X2_PORCENTUAL*ancho_logico_personaje, REPOSO_CAJA2_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* reposo_caja1 = new AABB(reposo_caja1_PuntoMin, reposo_caja1_PuntoMax);
	AABB* reposo_caja2 = new AABB(reposo_caja2_PuntoMin, reposo_caja2_PuntoMax);
	cajasAABB_reposo->push_back(reposo_caja1);
	cajasAABB_reposo->push_back(reposo_caja2);

	//PATADA ALTA//
	Vector2f patada_alta_caja1_PuntoMin(PATADA_ALTA_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, PATADA_ALTA_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f patada_alta_caja1_PuntoMax(PATADA_ALTA_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, PATADA_ALTA_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	Vector2f patada_alta_caja2_PuntoMin(PATADA_ALTA_CAJA2_X1_PORCENTUAL*ancho_logico_personaje, PATADA_ALTA_CAJA2_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f patada_alta_caja2_PuntoMax(PATADA_ALTA_CAJA2_X2_PORCENTUAL*ancho_logico_personaje, PATADA_ALTA_CAJA2_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* patada_alta_caja1 = new AABB(patada_alta_caja1_PuntoMin, patada_alta_caja1_PuntoMax);
	AABB* patada_alta_caja2 = new AABB(patada_alta_caja2_PuntoMin, patada_alta_caja2_PuntoMax);

	cajasAABB_patada_alta->push_back(patada_alta_caja1);
	cajasAABB_patada_alta->push_back(patada_alta_caja2);

	//PINIA ALTA//
	Vector2f pinia_alta_caja1_PuntoMin(PINIA_ALTA_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, PINIA_ALTA_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f pinia_alta_caja1_PuntoMax(PINIA_ALTA_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, PINIA_ALTA_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	Vector2f pinia_alta_caja2_PuntoMin(PINIA_ALTA_CAJA2_X1_PORCENTUAL*ancho_logico_personaje, PINIA_ALTA_CAJA2_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f pinia_alta_caja2_PuntoMax(PINIA_ALTA_CAJA2_X2_PORCENTUAL*ancho_logico_personaje, PINIA_ALTA_CAJA2_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* pinia_alta_caja1 = new AABB(pinia_alta_caja1_PuntoMin, pinia_alta_caja1_PuntoMax);
	AABB* pinia_alta_caja2 = new AABB(pinia_alta_caja2_PuntoMin, pinia_alta_caja2_PuntoMax);

	cajasAABB_pinia_alta->push_back(pinia_alta_caja1);
	cajasAABB_pinia_alta->push_back(pinia_alta_caja2);

	//AGACHADO//
	Vector2f agachado_caja1_PuntoMin(AGACHADO_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, AGACHADO_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f agachado_caja1_PuntoMax(AGACHADO_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, AGACHADO_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* agachado_caja1 = new AABB(agachado_caja1_PuntoMin, agachado_caja1_PuntoMax);
	cajasAABB_agachado->push_back(agachado_caja1);

	//SALTANDO DIAGONAL//
	Vector2f salto_diagonal_caja1_PuntoMin(SALTANDO_DIAGONAL_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, SALTANDO_DIAGONAL_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f salto_diagonal_caja1_PuntoMax(SALTANDO_DIAGONAL_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, SALTANDO_DIAGONAL_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* salto_diagonal_caja1 = new AABB(salto_diagonal_caja1_PuntoMin, salto_diagonal_caja1_PuntoMax);
	cajasAABB_salto_diagonal->push_back(salto_diagonal_caja1);

	//SALTANDO VERTICAL//
	Vector2f salto_vertical_caja1_PuntoMin(SALTANDO_VERTICAL_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, SALTANDO_VERTICAL_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f salto_vertical_caja1_PuntoMax(SALTANDO_VERTICAL_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, SALTANDO_VERTICAL_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	Vector2f salto_vertical_caja2_PuntoMin(SALTANDO_VERTICAL_CAJA2_X1_PORCENTUAL*ancho_logico_personaje, SALTANDO_VERTICAL_CAJA2_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f salto_vertical_caja2_PuntoMax(SALTANDO_VERTICAL_CAJA2_X2_PORCENTUAL*ancho_logico_personaje, SALTANDO_VERTICAL_CAJA2_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* salto_vertical_caja1 = new AABB(salto_vertical_caja1_PuntoMin, salto_vertical_caja1_PuntoMax);
	AABB* salto_vertical_caja2 = new AABB(salto_vertical_caja2_PuntoMin, salto_vertical_caja2_PuntoMax);

	cajasAABB_salto_vertical->push_back(salto_vertical_caja1);
	cajasAABB_salto_vertical->push_back(salto_vertical_caja2);

	//PATADA BAJA//
	Vector2f patada_baja_caja1_PuntoMin(PATADA_BAJA_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, PATADA_BAJA_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f patada_baja_caja1_PuntoMax(PATADA_BAJA_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, PATADA_BAJA_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	Vector2f patada_baja_caja2_PuntoMin(PATADA_BAJA_CAJA2_X1_PORCENTUAL*ancho_logico_personaje, PATADA_BAJA_CAJA2_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f patada_baja_caja2_PuntoMax(PATADA_BAJA_CAJA2_X2_PORCENTUAL*ancho_logico_personaje, PATADA_BAJA_CAJA2_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* patada_baja_caja1 = new AABB(patada_baja_caja1_PuntoMin, patada_baja_caja1_PuntoMax);
	AABB* patada_baja_caja2 = new AABB(patada_baja_caja2_PuntoMin, patada_baja_caja2_PuntoMax);

	cajasAABB_patada_baja->push_back(patada_baja_caja1);
	cajasAABB_patada_baja->push_back(patada_baja_caja2);

	//PATADA ALTA AGACHADO//
	Vector2f patada_alta_agachado_caja1_PuntoMin(PATADA_ALTA_AGACHADO_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, PATADA_ALTA_AGACHADO_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f patada_alta_agachado_caja1_PuntoMax(PATADA_ALTA_AGACHADO_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, PATADA_ALTA_AGACHADO_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	Vector2f patada_alta_agachado_caja2_PuntoMin(PATADA_ALTA_AGACHADO_CAJA2_X1_PORCENTUAL*ancho_logico_personaje, PATADA_ALTA_AGACHADO_CAJA2_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f patada_alta_agachado_caja2_PuntoMax(PATADA_ALTA_AGACHADO_CAJA2_X2_PORCENTUAL*ancho_logico_personaje, PATADA_ALTA_AGACHADO_CAJA2_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* patada_alta_agachado_caja1 = new AABB(patada_alta_agachado_caja1_PuntoMin, patada_alta_agachado_caja1_PuntoMax);
	AABB* patada_alta_agachado_caja2 = new AABB(patada_alta_agachado_caja2_PuntoMin, patada_alta_agachado_caja2_PuntoMax);

	cajasAABB_patada_alta_agachado->push_back(patada_alta_agachado_caja1);
	cajasAABB_patada_alta_agachado->push_back(patada_alta_agachado_caja2);

	//PATADA SALTANDO VERTICAL//
	Vector2f patada_saltando_vertical_caja1_PuntoMin(PATADA_SALTANDO_VERTICAL_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, PATADA_SALTANDO_VERTICAL_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f patada_saltando_vertical_caja1_PuntoMax(PATADA_SALTANDO_VERTICAL_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, PATADA_SALTANDO_VERTICAL_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	Vector2f patada_saltando_vertical_caja2_PuntoMin(PATADA_SALTANDO_VERTICAL_CAJA2_X1_PORCENTUAL*ancho_logico_personaje, PATADA_SALTANDO_VERTICAL_CAJA2_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f patada_saltando_vertical_caja2_PuntoMax(PATADA_SALTANDO_VERTICAL_CAJA2_X2_PORCENTUAL*ancho_logico_personaje, PATADA_SALTANDO_VERTICAL_CAJA2_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* patada_saltando_vertical_caja1 = new AABB(patada_saltando_vertical_caja1_PuntoMin, patada_saltando_vertical_caja1_PuntoMax);
	AABB* patada_saltando_vertical_caja2 = new AABB(patada_saltando_vertical_caja2_PuntoMin, patada_saltando_vertical_caja2_PuntoMax);

	cajasAABB_patada_saltando_vertical->push_back(patada_saltando_vertical_caja1);
	cajasAABB_patada_saltando_vertical->push_back(patada_saltando_vertical_caja2);

	//PATADA SALTANDO DIAGONAL DERECHA//
	Vector2f patada_saltando_diagonal_derecha_caja1_PuntoMin(PATADA_SALTANDO_DIAGONAL_DERECHA_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, PATADA_SALTANDO_DIAGONAL_DERECHA_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f patada_saltando_diagonal_derecha_caja1_PuntoMax(PATADA_SALTANDO_DIAGONAL_DERECHA_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, PATADA_SALTANDO_DIAGONAL_DERECHA_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	Vector2f patada_saltando_diagonal_derecha_caja2_PuntoMin(PATADA_SALTANDO_DIAGONAL_DERECHA_CAJA2_X1_PORCENTUAL*ancho_logico_personaje, PATADA_SALTANDO_DIAGONAL_DERECHA_CAJA2_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f patada_saltando_diagonal_derecha_caja2_PuntoMax(PATADA_SALTANDO_DIAGONAL_DERECHA_CAJA2_X2_PORCENTUAL*ancho_logico_personaje, PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* patada_saltando_diagonal_derecha_caja1 = new AABB(patada_saltando_diagonal_derecha_caja1_PuntoMin, patada_saltando_diagonal_derecha_caja1_PuntoMax);
	AABB* patada_saltando_diagonal_derecha_caja2 = new AABB(patada_saltando_diagonal_derecha_caja2_PuntoMin, patada_saltando_diagonal_derecha_caja2_PuntoMax);

	cajasAABB_patada_saltando_diagonal_derecha->push_back(patada_saltando_diagonal_derecha_caja1);
	cajasAABB_patada_saltando_diagonal_derecha->push_back(patada_saltando_diagonal_derecha_caja2);

	//PATADA SALTANDO DIAGONAL IZQUIERDA//
	Vector2f patada_saltando_diagonal_izquierda_caja1_PuntoMin(PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f patada_saltando_diagonal_izquierda_caja1_PuntoMax(PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	Vector2f patada_saltando_diagonal_izquierda_caja2_PuntoMin(PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_X1_PORCENTUAL*ancho_logico_personaje, PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f patada_saltando_diagonal_izquierda_caja2_PuntoMax(PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_X2_PORCENTUAL*ancho_logico_personaje, PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* patada_saltando_diagonal_izquierda_caja1 = new AABB(patada_saltando_diagonal_izquierda_caja1_PuntoMin, patada_saltando_diagonal_izquierda_caja1_PuntoMax);
	AABB* patada_saltando_diagonal_izquierda_caja2 = new AABB(patada_saltando_diagonal_izquierda_caja2_PuntoMin, patada_saltando_diagonal_izquierda_caja2_PuntoMax);

	cajasAABB_patada_saltando_diagonal_izquierda->push_back(patada_saltando_diagonal_izquierda_caja1);
	cajasAABB_patada_saltando_diagonal_izquierda->push_back(patada_saltando_diagonal_izquierda_caja2);

	//PINIA BAJA//
	Vector2f pinia_baja_caja1_PuntoMin(PINIA_BAJA_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, PINIA_BAJA_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f pinia_baja_caja1_PuntoMax(PINIA_BAJA_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, PINIA_BAJA_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	Vector2f pinia_baja_caja2_PuntoMin(PINIA_BAJA_CAJA2_X1_PORCENTUAL*ancho_logico_personaje, PINIA_BAJA_CAJA2_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f pinia_baja_caja2_PuntoMax(PINIA_BAJA_CAJA2_X2_PORCENTUAL*ancho_logico_personaje, PINIA_BAJA_CAJA2_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* pinia_baja_caja1 = new AABB(pinia_baja_caja1_PuntoMin, pinia_baja_caja1_PuntoMax);
	AABB* pinia_baja_caja2 = new AABB(pinia_baja_caja2_PuntoMin, pinia_baja_caja2_PuntoMax);

	cajasAABB_pinia_baja->push_back(pinia_baja_caja1);
	cajasAABB_pinia_baja->push_back(pinia_baja_caja2);

	//PINIA SALTANDO DIAGONAL DERECHA(es el mismo sprite que saltando vertical)//
	Vector2f pinia_saltando_diagonal_derecha_caja1_PuntoMin(PINIA_SALTANDO_DIAGONAL_DERECHA_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, PINIA_SALTANDO_DIAGONAL_DERECHA_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f pinia_saltando_diagonal_derecha_caja1_PuntoMax(PINIA_SALTANDO_DIAGONAL_DERECHA_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, PINIA_SALTANDO_DIAGONAL_DERECHA_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	Vector2f pinia_saltando_diagonal_derecha_caja2_PuntoMin(PINIA_SALTANDO_DIAGONAL_DERECHA_CAJA2_X1_PORCENTUAL*ancho_logico_personaje, PINIA_SALTANDO_DIAGONAL_DERECHA_CAJA2_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f pinia_saltando_diagonal_derecha_caja2_PuntoMax(PINIA_SALTANDO_DIAGONAL_DERECHA_CAJA2_X2_PORCENTUAL*ancho_logico_personaje, PINIA_SALTANDO_DIAGONAL_DERECHA_CAJA2_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* pinia_saltando_diagonal_derecha_caja1 = new AABB(pinia_saltando_diagonal_derecha_caja1_PuntoMin, pinia_saltando_diagonal_derecha_caja1_PuntoMax);
	AABB* pinia_saltando_diagonal_derecha_caja2 = new AABB(pinia_saltando_diagonal_derecha_caja2_PuntoMin, pinia_saltando_diagonal_derecha_caja2_PuntoMax);

	cajasAABB_pinia_saltando_diagonal_derecha->push_back(pinia_saltando_diagonal_derecha_caja1);
	cajasAABB_pinia_saltando_diagonal_derecha->push_back(pinia_saltando_diagonal_derecha_caja2);

	//PINIA SALTANDO DIAGONAL IZQUIERDA(es el mismo sprite que saltando vertical)//
	Vector2f pinia_saltando_diagonal_izquierda_caja1_PuntoMin(PINIA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, PINIA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f pinia_saltando_diagonal_izquierda_caja1_PuntoMax(PINIA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, PINIA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	Vector2f pinia_saltando_diagonal_izquierda_caja2_PuntoMin(PINIA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_X1_PORCENTUAL*ancho_logico_personaje, PINIA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f pinia_saltando_diagonal_izquierda_caja2_PuntoMax(PINIA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_X2_PORCENTUAL*ancho_logico_personaje, PINIA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* pinia_saltando_diagonal_izquierda_caja1 = new AABB(pinia_saltando_diagonal_izquierda_caja1_PuntoMin, pinia_saltando_diagonal_izquierda_caja1_PuntoMax);
	AABB* pinia_saltando_diagonal_izquierda_caja2 = new AABB(pinia_saltando_diagonal_izquierda_caja2_PuntoMin, pinia_saltando_diagonal_izquierda_caja2_PuntoMax);

	cajasAABB_pinia_saltando_diagonal_izquierda->push_back(pinia_saltando_diagonal_izquierda_caja1);
	cajasAABB_pinia_saltando_diagonal_izquierda->push_back(pinia_saltando_diagonal_izquierda_caja2);

	//PINIA SALTANDO VERTICAL//
	Vector2f pinia_saltando_vertical_caja1_PuntoMin(PINIA_SALTANDO_VERTICAL_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, PINIA_SALTANDO_VERTICAL_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f pinia_saltando_vertical_caja1_PuntoMax(PINIA_SALTANDO_VERTICAL_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, PINIA_SALTANDO_VERTICAL_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	Vector2f pinia_saltando_vertical_caja2_PuntoMin(PINIA_SALTANDO_VERTICAL_CAJA2_X1_PORCENTUAL*ancho_logico_personaje, PINIA_SALTANDO_VERTICAL_CAJA2_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f pinia_saltando_vertical_caja2_PuntoMax(PINIA_SALTANDO_VERTICAL_CAJA2_X2_PORCENTUAL*ancho_logico_personaje, PINIA_SALTANDO_VERTICAL_CAJA2_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* pinia_saltando_vertical_caja1 = new AABB(pinia_saltando_vertical_caja1_PuntoMin, pinia_saltando_vertical_caja1_PuntoMax);
	AABB* pinia_saltando_vertical_caja2 = new AABB(pinia_saltando_vertical_caja2_PuntoMin, pinia_saltando_vertical_caja2_PuntoMax);

	cajasAABB_pinia_saltando_vertical->push_back(pinia_saltando_vertical_caja1);
	cajasAABB_pinia_saltando_vertical->push_back(pinia_saltando_vertical_caja2);

	//DEFENDIENDO AGACHADO//
	Vector2f defendiendo_agachado_caja1_PuntoMin(DEFENDIENDO_AGACHADO_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, DEFENDIENDO_AGACHADO_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f defendiendo_agachado_caja1_PuntoMax(DEFENDIENDO_AGACHADO_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, DEFENDIENDO_AGACHADO_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	Vector2f defendiendo_agachado_caja2_PuntoMin(DEFENDIENDO_AGACHADO_CAJA2_X1_PORCENTUAL*ancho_logico_personaje, DEFENDIENDO_AGACHADO_CAJA2_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f defendiendo_agachado_caja2_PuntoMax(DEFENDIENDO_AGACHADO_CAJA2_X2_PORCENTUAL*ancho_logico_personaje, DEFENDIENDO_AGACHADO_CAJA2_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* defendiendo_agachado_caja1 = new AABB(defendiendo_agachado_caja1_PuntoMin, defendiendo_agachado_caja1_PuntoMax);
	AABB* defendiendo_agachado_caja2 = new AABB(defendiendo_agachado_caja2_PuntoMin, defendiendo_agachado_caja2_PuntoMax);

	cajasAABB_defendiendo_agachado->push_back(defendiendo_agachado_caja1);
	cajasAABB_defendiendo_agachado->push_back(defendiendo_agachado_caja2);

	//GANCHO//
	Vector2f gancho_caja1_PuntoMin(GANCHO_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, GANCHO_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f gancho_caja1_PuntoMax(GANCHO_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, GANCHO_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	Vector2f gancho_caja2_PuntoMin(GANCHO_CAJA2_X1_PORCENTUAL*ancho_logico_personaje, GANCHO_CAJA2_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f gancho_caja2_PuntoMax(GANCHO_CAJA2_X2_PORCENTUAL*ancho_logico_personaje, GANCHO_CAJA2_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* gancho_caja1 = new AABB(gancho_caja1_PuntoMin, gancho_caja1_PuntoMax);
	AABB* gancho_caja2 = new AABB(gancho_caja2_PuntoMin, gancho_caja2_PuntoMax);

	cajasAABB_gancho->push_back(gancho_caja1);
	cajasAABB_gancho->push_back(gancho_caja2);

	//RECIBIENDO GOLPE//
	Vector2f recibiendo_golpe_caja1_PuntoMin(REPOSO_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, REPOSO_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f recibiendo_golpe_caja1_PuntoMax(REPOSO_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, REPOSO_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	Vector2f recibiendo_golpe_caja2_PuntoMin(REPOSO_CAJA2_X1_PORCENTUAL*ancho_logico_personaje, REPOSO_CAJA2_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f recibiendo_golpe_caja2_PuntoMax(REPOSO_CAJA2_X2_PORCENTUAL*ancho_logico_personaje, REPOSO_CAJA2_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* recibiendo_golpe_caja1 = new AABB(recibiendo_golpe_caja1_PuntoMin, recibiendo_golpe_caja1_PuntoMax);
	AABB* recibiendo_golpe_caja2 = new AABB(recibiendo_golpe_caja2_PuntoMin, recibiendo_golpe_caja2_PuntoMax);
	cajasAABB_golpeado->push_back(recibiendo_golpe_caja1);
	cajasAABB_golpeado->push_back(recibiendo_golpe_caja2);

	//CAIDA DERECHA//
	Vector2f caida_derecha_caja1_PuntoMin(CAIDA_DERECHA_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, CAIDA_DERECHA_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f caida_derecha_caja1_PuntoMax(CAIDA_DERECHA_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, CAIDA_DERECHA_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* caida_derecha_caja1 = new AABB(caida_derecha_caja1_PuntoMin, caida_derecha_caja1_PuntoMax);
	cajasAABB_caida_derecha->push_back(caida_derecha_caja1);

	//CAIDA IZQUIERDA//
	Vector2f caida_izquierda_caja1_PuntoMin(CAIDA_IZQUIERDA_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, CAIDA_IZQUIERDA_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f caida_izquierda_caja1_PuntoMax(CAIDA_IZQUIERDA_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, CAIDA_IZQUIERDA_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* caida_izquierda_caja1 = new AABB(caida_izquierda_caja1_PuntoMin, caida_izquierda_caja1_PuntoMax);
	cajasAABB_caida_izquierda->push_back(caida_izquierda_caja1);

	//TIRANDO PODER//
	Vector2f tirando_poder_caja1_PuntoMin(TIRANDO_PODER_CAJA1_X1_PORCENTUAL*ancho_logico_personaje, TIRANDO_PODER_CAJA1_Y1_PORCENTUAL*alto_logico_personaje);
	Vector2f tirando_poder_caja1_PuntoMax(TIRANDO_PODER_CAJA1_X2_PORCENTUAL*ancho_logico_personaje, TIRANDO_PODER_CAJA1_Y2_PORCENTUAL*alto_logico_personaje);

	AABB* tirando_poder_caja1 = new AABB(tirando_poder_caja1_PuntoMin, tirando_poder_caja1_PuntoMax);
	cajasAABB_tirando_poder->push_back(tirando_poder_caja1);

	Vector2f pivote(ancho_logico_personaje/2, 0);
	//Armo los BVH de cada estado
	BVH* BVH_reposo = new BVH(cajasAABB_reposo, pivote);
	BVH* BVH_patada_alta = new BVH(cajasAABB_patada_alta, pivote);
	BVH* BVH_pinia_alta = new BVH(cajasAABB_pinia_alta, pivote);
	BVH* BVH_agachado = new BVH(cajasAABB_agachado, pivote);
	BVH* BVH_salto_diagonal = new BVH(cajasAABB_salto_diagonal, pivote);
	BVH* BVH_salto_vertical = new BVH(cajasAABB_salto_vertical, pivote);
	BVH* BVH_patada_baja = new BVH(cajasAABB_patada_baja, pivote);
	BVH* BVH_patada_alta_agachado = new BVH(cajasAABB_patada_alta_agachado, pivote);
	BVH* BVH_patada_saltando_vertical = new BVH(cajasAABB_patada_saltando_vertical, pivote);
	BVH* BVH_patada_saltando_diagonal_derecha = new BVH(cajasAABB_patada_saltando_diagonal_derecha, pivote);
	BVH* BVH_patada_saltando_diagonal_izquierda = new BVH(cajasAABB_patada_saltando_diagonal_izquierda, pivote);
	BVH* BVH_pinia_baja = new BVH(cajasAABB_pinia_baja, pivote);
	BVH* BVH_pinia_saltando_diagonal_derecha = new BVH(cajasAABB_pinia_saltando_diagonal_derecha, pivote);
	BVH* BVH_pinia_saltando_diagonal_izquierda = new BVH(cajasAABB_pinia_saltando_diagonal_izquierda, pivote);
	BVH* BVH_pinia_saltando_vertical = new BVH(cajasAABB_pinia_saltando_vertical, pivote);
	BVH* BVH_defendiendo_agachado = new BVH(cajasAABB_defendiendo_agachado, pivote);
	BVH* BVH_gancho = new BVH(cajasAABB_gancho, pivote);
	BVH* BVH_golpeado = new BVH(cajasAABB_golpeado, pivote);
	BVH* BVH_caida_derecha = new BVH(cajasAABB_caida_derecha, pivote);
	BVH* BVH_caida_izquierda = new BVH(cajasAABB_caida_izquierda, pivote);
	BVH* BVH_tirando_poder = new BVH(cajasAABB_tirando_poder, pivote);

	map<estado_personaje, BVH*>* mapa_BVH = new map<estado_personaje, BVH*>;
	mapa_BVH->insert(pair<estado_personaje, BVH*>(EN_ESPERA, BVH_reposo));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(CAMINANDO_DERECHA, BVH_reposo));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(CAMINANDO_IZQUIERDA, BVH_reposo));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(SALTANDO_OBLICUO_DERECHA, BVH_salto_diagonal));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(SALTANDO_OBLICUO_IZQUIERDA, BVH_salto_diagonal));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(SALTANDO_VERTICAL, BVH_salto_vertical));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(PATEANDO_ALTO, BVH_patada_alta));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(PATEANDO_BAJO, BVH_patada_baja));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(PATEANDO_ALTO_AGACHADO, BVH_patada_alta_agachado));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(PATEANDO_SALTANDO_DIAGONAL_DERECHA, BVH_patada_saltando_diagonal_derecha));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(PATEANDO_SALTANDO_DIAGONAL_IZQUIERDA, BVH_patada_saltando_diagonal_izquierda));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(PATEANDO_SALTANDO_VERTICAL, BVH_patada_saltando_vertical));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(PINIA_ALTA, BVH_pinia_alta));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(PINIA_BAJA, BVH_pinia_baja));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(PINIA_SALTANDO_DIAGONAL_DERECHA, BVH_pinia_saltando_diagonal_derecha));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(PINIA_SALTANDO_DIAGONAL_IZQUIERDA, BVH_pinia_saltando_diagonal_izquierda));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(PINIA_SALTANDO_VERTICAL, BVH_pinia_saltando_vertical));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(AGACHADO, BVH_agachado));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(DEFENDIENDO, BVH_reposo));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(DEFENDIENDO_AGACHADO, BVH_defendiendo_agachado));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(GANCHO, BVH_gancho));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(RECIBIENDO_GOLPE, BVH_golpeado));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(CAIDA_DERECHA, BVH_caida_derecha));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(CAIDA_IZQUIERDA, BVH_caida_izquierda));
	mapa_BVH->insert(pair<estado_personaje, BVH*>(TIRANDO_PODER, BVH_tirando_poder));

	return mapa_BVH;
}

BVH* CargadorDeOjbetos::cargarCajasColisionArmaPersonaje(float ancho_logico_arma, float alto_logico_arma){
	//ARMA//
	vector<AABB*>* cajasAABB_arma = new vector<AABB*>;

	Vector2f arma_caja1_PuntoMin(ARMA_CAJA1_X1_PORCENTUAL*ancho_logico_arma, ARMA_CAJA1_Y1_PORCENTUAL*alto_logico_arma);
	Vector2f arma_caja1_PuntoMax(ARMA_CAJA1_X2_PORCENTUAL*ancho_logico_arma, ARMA_CAJA1_Y2_PORCENTUAL*alto_logico_arma);

	AABB* arma_caja1 = new AABB(arma_caja1_PuntoMin, arma_caja1_PuntoMax);
	cajasAABB_arma->push_back(arma_caja1);

	Vector2f pivote(ancho_logico_arma/2, 0);

	BVH* BVH_arma = new BVH(cajasAABB_arma, pivote);

	return BVH_arma;
}

void CargadorDeOjbetos::cargarInfo_desdeMenus() {

	ControladorJoystickMenu::Instance()->initialiseJoysticks( parser->getControlJugador1()->getCorrespondenciaTeclas(),
														  parser->getControlJugador1()->getCorrespondenciaEjes(),
														  parser->getControlJugador2()->getCorrespondenciaTeclas(),
														  parser->getControlJugador2()->getCorrespondenciaEjes()
														 );

	string tipoDeControl_jugador1 = parser->getTipoControlJugador1();
	string tipoDeControl_jugador2 = parser->getTipoControlJugador2();
	int anchopx = parser->getVentanaDef()->getAnchoPx();
	int altopx = parser->getVentanaDef()->getAltoPx();

	PantallaSeleccionarModo* pantallaSeleccionarModo = new PantallaSeleccionarModo(anchopx, altopx, tipoDeControl_jugador1,
																tipoDeControl_jugador2);
	pantallaSeleccionarModo->iniciar();
	string modo_juego_elegido = pantallaSeleccionarModo->getModoDeJuegoElegido();
	this->modo_juego = modo_juego_elegido;

	PantallaSeleccionarPersonaje* pantallaSeleccionarPersonajes = new PantallaSeleccionarPersonaje(anchopx, altopx, modo_juego_elegido,
																		tipoDeControl_jugador1,tipoDeControl_jugador2);
	pantallaSeleccionarPersonajes->iniciar();

	this->idPersonaje1Elegido = pantallaSeleccionarPersonajes->getIdPersonaje1Elegido();
	this->idPersonaje2Elegido = pantallaSeleccionarPersonajes->getIdPersonaje2Elegido();

	string titulo_ventana_pelea(TITULO_VENTANA_INICIO);
	titulo_ventana_pelea.append("(Modo: ");
	titulo_ventana_pelea.append(modo_juego_elegido);
	titulo_ventana_pelea.append(")");
	SDL_SetWindowTitle( Renderizador::Instance()->getWindow(), titulo_ventana_pelea.c_str() );

	ControladorJoystickMenu::Instance()->clean();
}

string CargadorDeOjbetos::getIdPersonaje1Elegido() const {
	return idPersonaje1Elegido;
}

string CargadorDeOjbetos::getIdPersonaje2Elegido() const {
	return idPersonaje2Elegido;
}

vector<Combo*>* CargadorDeOjbetos::cargarCombos(string nombrePersonaje){

	vector<string>* vectorTeclasCombo1 = new vector<string>;
	vector<string>* vectorTeclasCombo2 = new vector<string>;
	vector<string>* vectorTeclasCombo3 = new vector<string>;
	vector<string>* vectorTeclasCombo4 = new vector<string>;
	vector<string>* vectorTeclasCombo5 = new vector<string>;
	vector<string>* vectorTeclasCombo6 = new vector<string>;
	vector<Combo*>* vectorDeCombos = new vector<Combo*>;


	if(nombrePersonaje == "sub-zero"){
		vectorTeclasCombo1->push_back("JOY_ABAJO");
		vectorTeclasCombo1->push_back("JOY_DERECHA");
		vectorTeclasCombo1->push_back("JOY_PINIA_BAJA");
		Combo* combo1 = new Combo(vectorTeclasCombo1, "Ice Freeze", 1);

		vectorTeclasCombo2->push_back("JOY_IZQUIERDA");
		vectorTeclasCombo2->push_back("JOY_PINIA_BAJA");
		vectorTeclasCombo2->push_back("JOY_PATADA_BAJA");
		vectorTeclasCombo2->push_back("JOY_DEFENSA");
		Combo* combo2 = new Combo(vectorTeclasCombo2, "Slide", 2);

		vectorTeclasCombo3->push_back("JOY_DERECHA");
		vectorTeclasCombo3->push_back("JOY_ABAJO");
		vectorTeclasCombo3->push_back("JOY_DERECHA");
		vectorTeclasCombo3->push_back("JOY_PINIA_ALTA");
		Combo* combo3 = new Combo(vectorTeclasCombo3, "Fatality1", 3);

		vectorTeclasCombo4->push_back("JOY_DERECHA");
		vectorTeclasCombo4->push_back("JOY_PATADA_BAJA");
		Combo* combo4 = new Combo(vectorTeclasCombo4, "Patada Giratoria", 4);

		vectorTeclasCombo5->push_back("JOY_DERECHA");
		vectorTeclasCombo5->push_back("JOY_DERECHA");
		vectorTeclasCombo5->push_back("JOY_DEFENSA");
		Combo* combo5 = new Combo(vectorTeclasCombo5, "Babality", 5);

		vectorDeCombos->push_back(combo1);
		vectorDeCombos->push_back(combo2);
		vectorDeCombos->push_back(combo3);
		vectorDeCombos->push_back(combo4);
		vectorDeCombos->push_back(combo5);
	}else{

		vectorTeclasCombo1->push_back("JOY_IZQUIERDA");
		vectorTeclasCombo1->push_back("JOY_IZQUIERDA");
		vectorTeclasCombo1->push_back("JOY_PINIA_BAJA");
		Combo* combo1 = new Combo(vectorTeclasCombo1, "Ring Toss", 1);

		vectorTeclasCombo2->push_back("JOY_PINIA_BAJA");
		vectorTeclasCombo2->push_back("JOY_DEFENSA");
		vectorTeclasCombo2->push_back("JOY_PATADA_BAJA");
		Combo* combo2 = new Combo(vectorTeclasCombo2, "Leg Grab", 2);

		vectorTeclasCombo3->push_back("JOY_DERECHA");
		vectorTeclasCombo3->push_back("JOY_IZQUIERDA");
		vectorTeclasCombo3->push_back("JOY_PINIA_BAJA");
		Combo* combo3 = new Combo(vectorTeclasCombo3, "Square Flight", 3);

		vectorTeclasCombo4->push_back("JOY_DERECHA");
		vectorTeclasCombo4->push_back("JOY_DERECHA");
		vectorTeclasCombo4->push_back("JOY_IZQUIERDA");
		vectorTeclasCombo4->push_back("JOY_IZQUIERDA");
		vectorTeclasCombo4->push_back("JOY_DEFENSA");
		Combo* combo4 = new Combo(vectorTeclasCombo4, "Fatality1", 4);

		vectorTeclasCombo5->push_back("JOY_DERECHA");
		vectorTeclasCombo5->push_back("JOY_PATADA_BAJA");
		Combo* combo5 = new Combo(vectorTeclasCombo5, "Patada Giratoria", 5);

		vectorTeclasCombo6->push_back("JOY_DERECHA");
		vectorTeclasCombo6->push_back("JOY_DERECHA");
		vectorTeclasCombo6->push_back("JOY_DEFENSA");
		Combo* combo6 = new Combo(vectorTeclasCombo6, "Babality", 6);

		vectorDeCombos->push_back(combo1);
		vectorDeCombos->push_back(combo2);
		vectorDeCombos->push_back(combo3);
		vectorDeCombos->push_back(combo4);
		vectorDeCombos->push_back(combo5);
		vectorDeCombos->push_back(combo6);
	}

	return vectorDeCombos;
}

string CargadorDeOjbetos::verModoDeJuego(){
	return this->modo_juego;
}
