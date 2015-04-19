/*
 * Parser.cpp
 *
 *  Created on: 24/3/2015
 *      Author: ariel
 */

#include "Parser.h"

#include <cstdlib>
#include <iostream>

#include "../json/EscenarioDef.h"
#include "../json/PersonajeDef.h"
#include "../json/VentanaDef.h"
#include "../utils/Logger.h"
#include "../utils/Util.h"




using std::string;

Parser::Parser() {

}

Parser::Parser(string archivo_json)
{
	this->entrada = archivo_json;
	this->ventana = new VentanaDef();
	this->escenario = new EscenarioDef();
	this->capas = new list<CapaDef*>;
	this->personaje = new PersonajeDef();

	this->inicializar();
}

void Parser::inicializar()
{
	string escenario_defecto(JSON_POR_DEFECTO);

	if ( !Util::getInstancia()->existeArchivo(this->entrada) )
	{
		Logger::getInstance()->error("No existe el archivo de configuracion inicial "+this->entrada+
					". Se elije uno nuevo por defecto "+escenario_defecto);

		this->entrada = escenario_defecto;

	}

	ifstream archivo_escenario(this->entrada.c_str());
	if ( !this->reader.parse(archivo_escenario, this->root, false) )
	{
		this->entrada = escenario_defecto;

		Logger::getInstance()->error("No se pudo parsear con JSON por un problema sintactico. "+reader.getFormatedErrorMessages());
		Logger::getInstance()->info("Se va a cargar un escenario por defecto "+escenario_defecto);

		ifstream archivo_escenario2(this->entrada.c_str());
		this->reader.parse(archivo_escenario2, this->root, false);
	}

}

void Parser::cargarJsonPorDefecto(){
    entrada = JSON_POR_DEFECTO;
    ifstream archivo_escenario(this->entrada.c_str());
    reader.parse(archivo_escenario, this->root, false);
}

void Parser::parsearCapas(){
    Json::Value valorCapas;
    valorCapas = root.get(TAG_CAPAS, &valorCapas);

    for (unsigned int idx_capas = 0; idx_capas < valorCapas.size(); ++idx_capas) {
        CapaDef* capa;
        string imagen_fondo;
        string id_capa;
        double ancho = 0;
        for( Json::ValueIterator it3 = valorCapas[idx_capas].begin() ; it3 != valorCapas[idx_capas].end() ; it3++ ) {
            string tag = it3.key().asString();

            if ( tag == TAG_CAPAS_IMAGEN ) {
                imagen_fondo = valorCapas[idx_capas][TAG_CAPAS_IMAGEN].asString();
            } else if ( tag == TAG_CAPAS_ID ) {
                id_capa = valorCapas[idx_capas][TAG_CAPAS_ID].asString();
            } else if ( tag == TAG_CAPAS_ANCHO ) {
                Json::Value valorAncho = valorCapas[idx_capas][TAG_CAPAS_ANCHO];
                ancho = (valorAncho.isNumeric()) ? (valorAncho.asDouble()) : ANCHO_CAPA_DEFAULT;
            } else {
                Logger::getInstance()->error("Dentro de la capa no se encuentra el parametro "+tag);
            }

        }
        capa = new CapaDef(imagen_fondo, id_capa, ancho);
        capas->push_back(capa);
    }
}

void Parser::parsearEscenario(){
    Json::Value valorEsc;
    valorEsc = root.get(TAG_ESCENARIO, &valorEsc);

    //atributos del escenario
    double e_alto = 0;
    double e_ancho = 0;
    double e_ypiso = 0;

    for( Json::ValueIterator it2 = valorEsc.begin() ; it2 != valorEsc.end() ; it2++ ) {
        string tag = it2.key().asString();
        Json::Value subvalor = valorEsc[tag];

        if ( tag == TAG_ESCENARIO_ALTO ) {
            e_alto = (subvalor.isNumeric()) ? (subvalor.asDouble()) : ALTO_ESC_DEFAULT;
        } else if ( tag == TAG_ESCENARIO_ANCHO ) {
            e_ancho = (subvalor.isNumeric()) ? (subvalor.asDouble()) : ANCHO_ESC_DEFAULT;
        } else if ( tag == TAG_ESCENARIO_YPISO) {
            e_ypiso = (subvalor.isNumeric()) ? (subvalor.asDouble()) : Y_PISO_ESC_DEFAULT;
        } else {
            Logger::getInstance()->error("Dentro del escenario no se encuentra el parametro "+tag);
        }
    }
    escenario = new EscenarioDef(e_ancho, e_alto, e_ypiso);
}

void Parser::parsearVentana(){
    Json::Value valorVentana;
    valorVentana = root.get(TAG_VENTANA, &valorVentana);

    //atributos de la ventana
    int v_alto_px = 0;
    double v_ancho = 0;
    int v_ancho_px = 0;

    for( Json::ValueIterator it2 = valorVentana.begin() ; it2 != valorVentana.end() ; it2++ ) {
        string tag = it2.key().asString();
        Json::Value subvalor = valorVentana[tag];

        if ( tag == TAG_VENTANA_ALTOPX ) {
            v_alto_px = (subvalor.isInt()) ? subvalor.asInt() : ALTOPX_VENTANA_DEFAULT;
        } else if ( tag == TAG_VENTANA_ANCHO ) {
            v_ancho = (subvalor.isNumeric()) ? (subvalor.asDouble()) : ANCHO_VENTANA_DEFAULT;
        } else if ( tag == TAG_VENTANA_ANCHOPX ) {
            v_ancho_px = (subvalor.isInt()) ? (subvalor.asInt()) : ANCHOPX_VENTANA_DEFAULT;
        } else {
            Logger::getInstance()->error("Dentro de la ventana no se encuentra el parametro "+tag);
        }
    }
    ventana = new VentanaDef(v_ancho_px, v_alto_px, v_ancho);
}

void Parser::parsearPersonaje(){
    Json::Value valorPersonaje;
    valorPersonaje = root.get(TAG_PERSONAJE, &valorPersonaje);

    //atributos del personaje
    double p_alto = 0;
    double p_ancho = 0;
    int p_zindex = 0;
    // del sprites reposo
    string p_sprites_imagen;
    string p_sprites_id;
    int p_sprites_cant_fotogramas = 0;
    int p_sprites_fps = 0;

    int p_direccion = 0;
    list<SpriteDef*> sprites;

    for( Json::ValueIterator it2 = valorPersonaje.begin() ; it2 != valorPersonaje.end() ; it2++ ) {
        string tag = it2.key().asString();
        Json::Value subvalor = valorPersonaje[tag];


        if ( tag == TAG_PERSONAJE_ALTO ) {
            p_alto = (subvalor.isNumeric()) ? (subvalor.asDouble()) : ALTO_PERS_DEFAULT;
        } else if ( tag == TAG_PERSONAJE_ANCHO ) {
            p_ancho = (subvalor.isNumeric()) ? (subvalor.asDouble()) : ANCHO_PERS_DEFAULT;
        } else if ( tag == TAG_PERSONAJE_ZINDEX) {
            p_zindex = (subvalor.isInt()) ? (subvalor.asInt()) : Z_INDEX_PERS_DEFAULT;
        } else if (tag.find(TAG_PERSONAJE_SPRITES) != std::string::npos) {
            p_sprites_imagen = (*it2)[TAG_PERSONAJE_SPRITES_IMAGEN].asString();
            int indiceId = string(TAG_PERSONAJE_SPRITES).size();
            p_sprites_id = (tag).substr(indiceId);

            Json::Value valorFotog = (*it2)[TAG_PERSONAJE_SPRITES_CANT_FOTOGRAMAS];
            Json::Value valorFps = (*it2)[TAG_PERSONAJE_SPRITES_FPS];

            p_sprites_cant_fotogramas = (valorFotog.isInt()) ? (valorFotog.asInt()) : CANT_FOTOGRAMAS_DEFAULT;
            p_sprites_fps = (valorFps.isInt()) ? (valorFps.asInt()) : FPS_DEFAULT;

            SpriteDef* spriteDefAct = new SpriteDef(p_sprites_imagen, p_sprites_id, p_sprites_cant_fotogramas, p_sprites_fps);
            sprites.push_back(spriteDefAct);
        } else if ( tag == TAG_PERSONAJE_DIRECCION ) {
            p_direccion = (subvalor.isInt()) ? (subvalor.asInt()) : DIRECCION_PERS_DERECHA;
        } else {
            Logger::getInstance()->error("Dentro del personaje no se encuentra el parametro "+tag);
        }
    }
    personaje = new PersonajeDef(p_ancho, p_alto, p_zindex, p_direccion);
    for (list<SpriteDef*>::iterator it = sprites.begin(); it != sprites.end(); ++it){
        personaje->agregarSpritesDef(*it);
    }
}

bool Parser::parsearDesdeJson() {
    Logger::getInstance()->info("Se Inicia el parseo desde el JSON "+this->entrada);

    if( root.size() <= 0 )
        return false;
    parsearVentana();
    parsearEscenario();
    parsearPersonaje();
    parsearCapas();

    Logger::getInstance()->info("Inicia la validacion semantica del json");
	this->inciarValidacionSemantica();
	Logger::getInstance()->info("Termina la validacion semantica del json");
    return true;
}

Parser::~Parser() {
	delete personaje;
	delete escenario;
    for (list<CapaDef*>::iterator it_capas = capas->begin() ; it_capas != capas->end(); ++capas)
        delete (*it_capas);
    delete ventana;
}

list<CapaDef*>* Parser::getCapasDef() const {
	return capas;
}

EscenarioDef* Parser::getEscenarioDef() const {
	return escenario;
}

PersonajeDef* Parser::getPersonajeDef() const {
	return personaje;
}

VentanaDef* Parser::getVentanaDef() const {
	return ventana;
}

void Parser::inciarValidacionSemantica() {
    personaje->ajustarZIndex();
    personaje->ajustarAlto(escenario->getAlto());
    escenario->ajustarYPiso(personaje->getAlto());
    ventana->ajustarAncho(escenario->getAncho());
    for (list<CapaDef*>::iterator it_capas = this->capas->begin() ; it_capas != this->capas->end(); it_capas++)
        (*it_capas)->ajustarAncho(escenario->getAncho(), ventana->getAncho());
}

