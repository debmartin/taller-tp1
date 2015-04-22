/*
 * CargadorDeObjetos.cpp
 *
 *  Created on: 14/4/2015
 *      Author: val
 */
#include "CargadorDeObjetos.h"

CargadorDeOjbetos::CargadorDeOjbetos() {

}

CargadorDeOjbetos::~CargadorDeOjbetos() {

}

void CargadorDeOjbetos::cargarObjetos(string escenario_path) {

	////Inicialización desde Parser////
	Parser* parser = new Parser(escenario_path);
	if (!parser->parsearDesdeJson()) {
		parser->cargarJsonPorDefecto();
		parser->parsearDesdeJson();
	}
	VentanaDef* ventanaDef = parser->getVentanaDef();
	EscenarioDef* escenarioDef = parser->getEscenarioDef();
	PersonajeDef* personajeDef = parser->getPersonajeDef();

	////Inicializacion de VentanaGrafica////
	Logger::getInstance()->info(ventanaDef);

	Vector2f tamanioVentanaPx(ventanaDef->getAnchoPx(),
			ventanaDef->getAltoPx());
	Vector2f tamanioVentanaLogico(ventanaDef->getAncho(),
			escenarioDef->getAlto());

	bool exito = VentanaGrafica::Instance()->init(TITULO_VENTANA_INICIO,
	POS_VENTANA_INICIO, tamanioVentanaPx, tamanioVentanaLogico,
	INICIAR_FULLSCREEN);

	if (!exito) {
		Logger::getInstance()->error("Error al inicializar la VentanaGrafica");
	} else {
		Logger::getInstance()->info(
				"Inicialiazación de VentanaGrafica correcta.");
	}

	Vector2f relacionAspectos =
			VentanaGrafica::Instance()->obtener_relacion_aspectos();

	////Inicializacion de capas////
	list<Capa*>* capas = new list<Capa*>();
	list<Dibujable*>* capasYPersonajes = new list<Dibujable*>();
	list<CapaDef*>* capasDef = parser->getCapasDef();
	for (list<CapaDef*>::iterator it_capas = capasDef->begin();
			it_capas != capasDef->end(); ++it_capas) {
		Logger::getInstance()->info(*it_capas);
		Animacion* fondoAnim = new Animacion((*it_capas)->getImagenFondo(),
		CANT_FOTOGRAMAS_FONDO, FPS_FONDO, (*it_capas)->getIdCapa(),
				Renderizador::Instance()->getRenderer());
		Vector2f tamIniCapa((*it_capas)->getAncho(), escenarioDef->getAlto());
		Vector2f posInCapa = POSICION_INICIAL_CAPA;

		Capa* fondoCapa = new Capa(fondoAnim, tamIniCapa, posInCapa,
				relacionAspectos);
		capas->push_back(fondoCapa);
		capasYPersonajes->push_back(fondoCapa);

	}
	Logger::getInstance()->info("Inicialiazación de Capas correcta.");

	////Inicializacion de Personaje////
	Logger::getInstance()->info(personajeDef);
	jugador = new Personaje(personajeDef->getAncho(), personajeDef->getAlto(),
	personajeDef->getPosicionInicial(), VentanaGrafica::Instance());

	////Inicializacion de PersonajeDibujable////
	Vector2f tamanioPx(
			jugador->getAncho()
					* VentanaGrafica::Instance()->relacion_de_aspectoX(),
			jugador->getAlto()
					* VentanaGrafica::Instance()->relacion_de_aspectoY());

	list<SpriteDef*>* spritesDef = personajeDef->getSpritesDef();
	list<SpriteDef*>::iterator it_sprites = spritesDef->begin();
	SpriteDef* primerSpriteSubQuieto = *it_sprites;
	Animacion* SubQuieto = new Animacion(primerSpriteSubQuieto->getImagen(),
	primerSpriteSubQuieto->getCantFotogramas(),
	primerSpriteSubQuieto->getFps(),
	primerSpriteSubQuieto->getIdSprite(),
	Renderizador::Instance()->getRenderer());

	OrientacionSprite direccion;
	if (personajeDef->getDireccion() == 1) {
		direccion = ORIENTACION_DERECHA;
	} else {
		direccion = ORIENTACION_IZQUIERDA;
	}
	personajeDibujable = new PersonajeDibujable(SubQuieto,
	personajeDef->getPosicionInicial(), tamanioPx, direccion);

	for (; it_sprites != spritesDef->end(); ++it_sprites) {
		Animacion* sub_zero = new Animacion((*it_sprites)->getImagen(),
		(*it_sprites)->getCantFotogramas(), (*it_sprites)->getFps(),
		(*it_sprites)->getIdSprite(),
		Renderizador::Instance()->getRenderer());
		personajeDibujable->agregarAnimacion(sub_zero);
	}

	Logger::getInstance()->info(
			"Inicialización de Personaje correcta.");

	list<Dibujable*>::iterator it_dibujables = capasYPersonajes->begin();
	for (int i=0; it_dibujables != capasYPersonajes->end() && i < personajeDef->getZindex(); ++it_dibujables) {
		i++;
	}

	capasYPersonajes->insert(it_dibujables, personajeDibujable);

	////Inicializacion de EscenarioGrafico////
	Logger::getInstance()->info(escenarioDef);
	escenario = new EscenarioGrafico(escenarioDef->getAncho(),
			escenarioDef->getAlto(), escenarioDef->getYpiso(), capasYPersonajes,
			capas);
	Logger::getInstance()->info("Inicializacion de EscenarioGrafico correcta.");

	VentanaGrafica::Instance()->agregarEscenario(escenario);
	VentanaGrafica::Instance()->centrar_ventana();
	escenario->centrar_dibujables();

	Logger::getInstance()->info("Termina la carga del juego correctamente.");
//		    delete parser;
}

EscenarioGrafico* CargadorDeOjbetos::getEscenarioGrafico() {
	return escenario;
}

Personaje* CargadorDeOjbetos::getPersonaje() {
	return jugador;
}

PersonajeDibujable* CargadorDeOjbetos::getPersonajeDibujable() {
	return personajeDibujable;
}

