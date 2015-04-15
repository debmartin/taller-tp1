/*
 * CargadorDeObjetos.cpp
 *
 *  Created on: 14/4/2015
 *      Author: val
 */
#include "CargadorDeObjetos.h"

CargadorDeOjbetos::CargadorDeOjbetos(){

}

CargadorDeOjbetos::~CargadorDeOjbetos(){

}

void CargadorDeOjbetos::cargarObjetos(){

			////Inicialización desde Parser////
			string nombre_escenario("src/recursos/escenario.json");
			Parser* parser = new Parser(nombre_escenario.c_str());
			parser->parsearDesdeJson();

			VentanaDef* ventanaDef = parser->getVentanaDef();
			cout<<*ventanaDef<<endl;

			EscenarioDef* escenarioDef = parser->getEscenarioDef();
			cout<<*escenarioDef<<endl;

			PersonajeDef* personajeDef = parser->getPersonajeDef();
			cout<<*personajeDef<<endl;

			Logger::getInstance()->info("Inicialiazación desde Parser finalizada.");


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
			this->jugador = &jugador1;


			////Inicializacion de PersonajeDibujable////
			Vector2f tamanioPx(
		    		jugador->getAncho()*VentanaGrafica::Instance()->relacion_de_aspectoX(),
					jugador->getAlto()*VentanaGrafica::Instance()->relacion_de_aspectoY());

			SpriteDef* primerSpriteSubQuieto = *(personajeDef->getSpritesDef()->begin());
			Animacion SubQuieto(primerSpriteSubQuieto->getImagen(), primerSpriteSubQuieto->getCantFotogramas(), primerSpriteSubQuieto->getFps(),  primerSpriteSubQuieto->getIdSprite(), Renderizador::Instance()->getRenderer());
			PersonajeDibujable personajeDibujable1(&SubQuieto, POSICION_INICIAL_PERSONAJE, tamanioPx);

			for (list<SpriteDef*>::iterator it_sprites = personajeDef->getSpritesDef()->begin() ; it_sprites != personajeDef->getSpritesDef()->end(); it_sprites++)
			{
				Animacion sub_zero((*it_sprites)->getImagen(), (*it_sprites)->getCantFotogramas(), (*it_sprites)->getFps(), primerSpriteSubQuieto->getIdSprite(), Renderizador::Instance()->getRenderer());
				personajeDibujable1.agregarAnimacion(&sub_zero);
			}

			this->personajeDibujable = &personajeDibujable1;
			Logger::getInstance()->info("Inicialiazación de PersonajeDibujable correcta.");

			capasYPersonajes.push_back(&personajeDibujable1);

			////Inicializacion de EscenarioGrafico////
			EscenarioGrafico escenarioDibujable(escenarioDef->getAncho(), escenarioDef->getAlto(), escenarioDef->getYpiso(), &capasYPersonajes, &capas);
		    this->escenario = &escenarioDibujable;
			Logger::getInstance()->info("Inicializacion de EscenarioGrafico correcta.");


			VentanaGrafica::Instance()->agregarEscenario(&escenarioDibujable);
		    VentanaGrafica::Instance()->centrar_ventana();
		    escenario->centrar_dibujables();
		    Vector2f vector_centrado(escenarioDef->getAncho()/2.0, escenarioDef->getYpiso());
		    jugador->centrar_en(vector_centrado);
		    Logger::getInstance()->info("Carga correcta.");
		    cout << "carga correcta" << endl;
}

EscenarioGrafico* CargadorDeOjbetos::getEscenarioGrafico(){
	return escenario;
}

Personaje* CargadorDeOjbetos::getPersonaje(){
	return jugador;
}

PersonajeDibujable* CargadorDeOjbetos::getPersonajeDibujable(){
	return personajeDibujable;
}
