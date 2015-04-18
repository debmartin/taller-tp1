/*
 * Parser.cpp
 *
 *  Created on: 24/3/2015
 *      Author: ariel
 */

#include "Parser.h"

#include <iostream>

#include "../json/EscenarioDef.h"
#include "../json/PersonajeDef.h"
#include "../json/VentanaDef.h"
#include "../utils/Logger.h"
#include "../utils/Util.h"

#define JSON_POR_DEFECTO "src/recursos/escenario_defecto.json"

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

bool Parser::parsearDesdeJson() {

    Logger::getInstance()->info("Se Inicia el parseo desde el JSON "+this->entrada);

    if( root.size() > 0 ) {

        //atributos de la ventana
        int v_alto_px = 0;
        double v_ancho = 0;
        int v_ancho_px = 0;
        double v_margen_x = 0;

        //atributos del escenario
        double e_alto = 0;
        double e_ancho = 0;
        double e_ypiso = 0;

        //atributos del personaje
        double p_alto = 0;
        double p_ancho = 0;
        int p_zindex = 0;
        // del sprites reposo
        string p_sprites_imagen_1 = "";
        string p_sprites_id_1 = "";
        int p_sprites_cant_fotogramas_1 = 0;
        int p_sprites_fps_1 = 0;
        // del sprites caminando
        string p_sprites_imagen_2 = "";
        string p_sprites_id_2 = "";
        int p_sprites_cant_fotogramas_2 = 0;
        int p_sprites_fps_2 = 0;
        // del sprites agachado
        string p_sprites_imagen_3 = "";
        string p_sprites_id_3 = "";
        int p_sprites_cant_fotogramas_3 = 0;
        int p_sprites_fps_3 = 0;
        // del sprites salto vertical
        string p_sprites_imagen_4 = "";
        string p_sprites_id_4 = "";
        int p_sprites_cant_fotogramas_4 = 0;
        int p_sprites_fps_4 = 0;
        // del sprites salto oblicuo
        string p_sprites_imagen_5 = "";
        string p_sprites_id_5 = "";
        int p_sprites_cant_fotogramas_5 = 0;
        int p_sprites_fps_5 = 0;

        int p_direccion = 0;

        for( Json::ValueIterator it = root.begin() ; it != root.end() ; it++ )
        {
            const Json::Value key_nivel1 = it.key();
            //tag padre es el tag que esta en el nivel de las deficiones
            string tag_padre = key_nivel1.asString();

            const Json::Value root2 = root[tag_padre];

            if ( root2.isArray() )
            {
                if ( tag_padre == "capas" )
                {
                    for (unsigned int idx_capas = 0; idx_capas < root2.size(); ++idx_capas)
                    {
                        CapaDef* capa;
                        string imagen_fondo = "";
                        string id_capa = "";
                        double ancho = 0;
                        for( Json::ValueIterator it3 = root2[idx_capas].begin() ; it3 != root2[idx_capas].end() ; it3++ )
                        {
                            const Json::Value key_nivel2 = it3.key();

                            if ( key_nivel2.asString() == "imagen_fondo" )
                            {
                                imagen_fondo = (*it)[idx_capas]["imagen_fondo"].asString();
                            }
                            else if ( key_nivel2.asString() == "id_capa" )
                            {
                                id_capa = (*it)[idx_capas]["id_capa"].asString();
                            }
                            else if ( key_nivel2.asString() == "ancho" )
                            {
                            	if ( (*it)[idx_capas]["ancho"].isNumeric() )
                            		ancho = (*it)[idx_capas]["ancho"].asDouble();
                            }
                            else
                            {
                                Logger::getInstance()->error("Dentro de la capa no se encuentra el parametro "+key_nivel2.asString());
                            }

                        }
                        try {
                            capa = new CapaDef(imagen_fondo, id_capa, ancho);
                        } catch (exception) {
                            return false;
                        }
                        capas->push_back(capa);
                    }
                }
            }
            else
            {
                for( Json::ValueIterator it2 = root2.begin() ; it2 != root2.end() ; it2++ )
                {
                    const Json::Value key_nivel2 = it2.key();

                    if ( tag_padre == "ventana" )
                    {
                        if ( key_nivel2.asString() == "altopx" )
                        {
                        	if ( (*it)["altopx"].isInt() )
                        		v_alto_px = (*it)["altopx"].asInt();
                        }
                        else if ( key_nivel2.asString() == "ancho" )
                        {
                        	if ( (*it)["ancho"].isNumeric() )
                        		v_ancho = (*it)["ancho"].asDouble();
                        }
                        else if ( key_nivel2.asString() == "anchopx" )
                        {
                        	if ( (*it)["anchopx"].isInt() )
                        		v_ancho_px = (*it)["anchopx"].asInt();
                        }
                        else if ( key_nivel2.asString() == "margen_x" )
                        {
                        	if ( (*it)["margen_x"].isNumeric() )
                            v_margen_x= (*it)["margen_x"].asDouble();
                        }
                        else
                        {
                            Logger::getInstance()->error("Dentro de la ventana no se encuentra el parametro "+key_nivel2.asString());
                        }

                    }
                    else if ( tag_padre == "escenario" )
                    {
                        if ( key_nivel2.asString() == "alto" )
                        {
                        	if ( (*it)["alto"].isNumeric() )
                        		e_alto = (*it)["alto"].asDouble();
                        }
                        else if ( key_nivel2.asString() == "ancho" )
                        {
                        	if ( (*it)["ancho"].isNumeric() )
                        		e_ancho = (*it)["ancho"].asDouble();
                        }
                        //TODO revisar porque este parametro tiene una longitud mas grande. mide 7 en vez de 5!
                        else if ( key_nivel2.asString().compare("ypiso") >= 0 )
                        {
                        	if ( (*it)[key_nivel2.asString()].isNumeric() )
                        		e_ypiso = (*it)[key_nivel2.asString()].asDouble();
                        }
                        else
                        {
                            Logger::getInstance()->error("Dentro del escenario no se encuentra el parametro "+key_nivel2.asString());
                        }
                    }
                    else if ( tag_padre == "personaje" )
                    {
                        if ( key_nivel2.asString() == "alto" )
                        {
                        	if ( (*it)["alto"].isNumeric() )
                        		p_alto = (*it)["alto"].asDouble();
                        }
                        else if ( key_nivel2.asString().compare("ancho") == 0 )
                        {
                        	if ( (*it)[key_nivel2.asString()].isNumeric() )
                        		p_ancho = (*it)[key_nivel2.asString()].asDouble();
                        }
                        else if ( key_nivel2.asString().compare("zindex") >= 0 )
                        {
                        	if ( (*it)[key_nivel2.asString()].isInt() )
                        		p_zindex = (*it)[key_nivel2.asString()].asInt();
                        }
                        else if ( key_nivel2.asString() == "sprites_reposo" )
                        {
                            p_sprites_imagen_1 = (*it2)["imagen"].asString();
                            p_sprites_id_1 = (*it2)["id_sprite"].asString();
                            p_sprites_cant_fotogramas_1 = (*it2)["cant_fotogramas"].asInt();
                            p_sprites_fps_1 = (*it2)["fps"].asInt();
                        }
                        else if ( key_nivel2.asString() == "sprites_caminando" )
                        {
                            p_sprites_imagen_2 = (*it2)["imagen"].asString();
                            p_sprites_id_2 = (*it2)["id_sprite"].asString();
                            p_sprites_cant_fotogramas_2 = (*it2)["cant_fotogramas"].asInt();
                            p_sprites_fps_2 = (*it2)["fps"].asInt();
                        }
                        else if ( key_nivel2.asString() == "sprites_agachado" )
                        {
                            p_sprites_imagen_3 = (*it2)["imagen"].asString();
                            p_sprites_id_3 = (*it2)["id_sprite"].asString();
                            p_sprites_cant_fotogramas_3 = (*it2)["cant_fotogramas"].asInt();
                            p_sprites_fps_3 = (*it2)["fps"].asInt();
                        }
                        else if ( key_nivel2.asString() == "sprites_salto_vertical" )
                        {
                            p_sprites_imagen_4 = (*it2)["imagen"].asString();
                            p_sprites_id_4 = (*it2)["id_sprite"].asString();
                            p_sprites_cant_fotogramas_4 = (*it2)["cant_fotogramas"].asInt();
                            p_sprites_fps_4 = (*it2)["fps"].asInt();
                        }
                        else if ( key_nivel2.asString() == "sprites_salto_oblicuo" )
                        {
                            p_sprites_imagen_5 = (*it2)["imagen"].asString();
                            p_sprites_id_5 = (*it2)["id_sprite"].asString();
                            p_sprites_cant_fotogramas_5 = (*it2)["cant_fotogramas"].asInt();
                            p_sprites_fps_5 = (*it2)["fps"].asInt();
                        }
                        else if ( key_nivel2.asString() == "direccion" )
                        {
                        	if ( (*it)["direccion"].isInt() )
                        		p_direccion = (*it)["direccion"].asInt();
                        }
                        else
                        {
                            Logger::getInstance()->error("Dentro del personaje no se encuentra el parametro "+key_nivel2.asString());
                        }
                    }
                    else
                    {
                        Logger::getInstance()->error("Se hace la lectura de un tag invalido: "+tag_padre);
                    }
                }
            }
        }

        try {
            this->ventana = new VentanaDef(v_ancho_px, v_alto_px, v_ancho, v_margen_x);
            this->escenario = new EscenarioDef(e_ancho, e_alto, e_ypiso);
            this->personaje = new PersonajeDef(p_ancho, p_alto, p_zindex, p_direccion);
        } catch (exception) {
            return false;
        }
        //se cargan los sprites del personaje
        try {
            SpriteDef* spriteDef_reposo = new SpriteDef(p_sprites_imagen_1, p_sprites_id_1, p_sprites_cant_fotogramas_1, p_sprites_fps_1);
            SpriteDef* spriteDef_caminando = new SpriteDef(p_sprites_imagen_2, p_sprites_id_2, p_sprites_cant_fotogramas_2, p_sprites_fps_2);
            SpriteDef* spriteDef_agachado = new SpriteDef(p_sprites_imagen_3, p_sprites_id_3, p_sprites_cant_fotogramas_3, p_sprites_fps_3);
            SpriteDef* spriteDef_saltando_vert = new SpriteDef(p_sprites_imagen_4, p_sprites_id_4, p_sprites_cant_fotogramas_4, p_sprites_fps_4);
            SpriteDef* spriteDef_saltando_obli = new SpriteDef(p_sprites_imagen_5, p_sprites_id_5, p_sprites_cant_fotogramas_5, p_sprites_fps_5);

            this->personaje->agregarSpritesDef(spriteDef_reposo);
            this->personaje->agregarSpritesDef(spriteDef_caminando);
            this->personaje->agregarSpritesDef(spriteDef_agachado);
            this->personaje->agregarSpritesDef(spriteDef_saltando_vert);
            this->personaje->agregarSpritesDef(spriteDef_saltando_obli);
        } catch (exception) {
            return false;
        }

    }

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

	double escenario_ancho_nuevo = this->escenario->getAncho();
	double escenario_alto_nuevo = this->escenario->getAlto();
	double escenario_ypiso_nuevo = this->escenario->getYpiso();

	int ventana_anchopx_nuevo = this->ventana->getAnchoPx();
	int ventana_altopx_nuevo = this->ventana->getAltoPx();
	double ventana_ancho_nuevo = this->ventana->getAncho();
	double ventana_margenx_nuevo = this->ventana->getMargenX();

	double personaje_ancho_nuevo = this->personaje->getAncho();
	double personaje_alto_nuevo = this->personaje->getAlto();
	int personale_zindex_nuevo = this->personaje->getZindex();

	double personaje_direccion_nuevo = this->personaje->getDireccion();

	//validar el escenario
	if ( escenario_ancho_nuevo <= 0 )
	{
		escenario_ancho_nuevo = 1200;
		Logger::getInstance()->info("El ancho del escenario es negativo. Se elije uno nuevo: 1200");
	}

	if ( escenario_alto_nuevo <= 0 )
	{
		escenario_alto_nuevo = 180;
		Logger::getInstance()->info("El alto del escenario es negativo. Se elije uno nuevo: 800");
	}

	//validacion de la altura del personaje
	if ( personaje_alto_nuevo <= 0 )
	{
		//la eligo como la tercera parte de la altura del escenario
		personaje_alto_nuevo = escenario_alto_nuevo / 3;
		Logger::getInstance()->info("El alto del personaje es negativo. Se elije uno nuevo que sea la tercera parte del alto del escenario");
	}

	if ( escenario_ypiso_nuevo < 0 || (escenario_alto_nuevo - escenario_ypiso_nuevo) < personaje_alto_nuevo)
	{

		if ( escenario_ypiso_nuevo < 0 )
		{
			Logger::getInstance()->info("El y del piso del personaje es negativo. Se elije uno nuevo con el valor de cero");
		}
		if ( (escenario_alto_nuevo - escenario_ypiso_nuevo) < personaje_alto_nuevo )
		{
			Logger::getInstance()->info("El y del piso del personaje sobrepasa al escenario con respecto a su altura. Se elije uno nuevo con el valor de cero");
		}

		escenario_ypiso_nuevo = 0;
	}

	delete this->escenario;
	this->escenario = NULL;
	this->escenario = new EscenarioDef(escenario_ancho_nuevo, escenario_alto_nuevo, escenario_ypiso_nuevo);

	//validar la ventana
	if ( ventana_anchopx_nuevo <= 0 )
	{
		ventana_anchopx_nuevo = 800;
		Logger::getInstance()->info("El ancho en pixeles de la ventana es negativa. Se elije uno nuevo: 800");
	}

	if ( ventana_altopx_nuevo <= 0 )
	{
		ventana_altopx_nuevo = 600;
		Logger::getInstance()->info("El alto en pixeles de la ventana es negativa. Se elije uno nuevo: 600");
	}

	if ( ventana_ancho_nuevo <= 0 || ventana_ancho_nuevo > escenario_ancho_nuevo)
	{
		if ( ventana_ancho_nuevo <= 0 )
		{
			Logger::getInstance()->info("El ancho de la ventana es menor o igual a cero. Se elije uno nuevo que es la mitad del ancho del escenario");
		}
		if ( ventana_ancho_nuevo > escenario_ancho_nuevo )
		{
			Logger::getInstance()->info("El ancho de la ventana es mas grande que el ancho del escenario. Se elije uno nuevo que es la mitad del ancho del escenario");
		}

		ventana_ancho_nuevo = escenario_ancho_nuevo / 2;

	}

	if ( ventana_margenx_nuevo <= 0 )
	{
		ventana_margenx_nuevo = ventana_ancho_nuevo / 100;
		Logger::getInstance()->info("El margen en x de la ventana es menor o igual a cero. Se elije uno nuevo que es la centecima del ancho de la ventana");
	}

	delete this->ventana;
	this->ventana = NULL;
	this->ventana = new VentanaDef(ventana_anchopx_nuevo, ventana_altopx_nuevo, ventana_ancho_nuevo, ventana_margenx_nuevo);

	//validar las capas

	list<CapaDef*>* capas_nuevas = new list<CapaDef*>;

	for (list<CapaDef*>::iterator it_capas = this->capas->begin() ; it_capas != this->capas->end(); it_capas++)
	{
		string nuevo_fondo = (*it_capas)->getImagenFondo();
		string nuevo_id = (*it_capas)->getIdCapa();
		double nuevo_ancho = (*it_capas)->getAncho();

		if ( !Util::getInstancia()->existeArchivo(nuevo_fondo) )
		{
			Logger::getInstance()->info("No existe la imagen de fondo para la capa "+nuevo_fondo+". Por defecto se usa fondo_capa_defecto.png");
			nuevo_fondo = "img/fondo_capa_defecto.png";
		}

		//Falta validacion del id_capa//

		if ( nuevo_ancho <= 0 || nuevo_ancho > escenario_ancho_nuevo )
		{

			if ( nuevo_ancho <= 0 )
			{
				Logger::getInstance()->info("El ancho de la capa es negativo. Se elije un nuevo ancho igual al ancho del escenario");
			}
			if ( nuevo_ancho > escenario_ancho_nuevo )
			{
				Logger::getInstance()->info("El ancho de la capa es mayor al ancho del escenario. Se elije un nuevo ancho igual al ancho del escenario");
			}

			nuevo_ancho = escenario_ancho_nuevo;
		}

		CapaDef* capa_nueva = new CapaDef(nuevo_fondo, nuevo_id, nuevo_ancho);
		capas_nuevas->push_back(capa_nueva);
	}

	this->capas = capas_nuevas;


	//validar el personaje
	if ( personaje_ancho_nuevo <= 0 )
	{
		personaje->setAncho(15);
		Logger::getInstance()->info("El ancho del personaje es menor o igual a cero. Se elije uno nuevo con el valor de 15");
	}

	int cant_capas = this->capas->size();
	if ( personale_zindex_nuevo < 0 || personale_zindex_nuevo > cant_capas)
	{
		if ( personale_zindex_nuevo < 0 )
		{
			Logger::getInstance()->info("El zindex del personaje es menor a cero. Se elije uno nuevo para que el personaje este adelante de todas las capas");
		}
		if ( personale_zindex_nuevo > cant_capas )
		{
			Logger::getInstance()->info("El zindex del Personaje es mayor al valor posible. Se elije uno nuevo para que el personaje este adelante de todas las capas");
		}

		personaje->setZIndex(cant_capas);
	}

	if ( personaje_direccion_nuevo != -1 && personaje_direccion_nuevo != 1 )
	{
		personaje->setDireccion(1);
		Logger::getInstance()->info("La configuracion de la direccion del personaje no es la correcta. Se lo dirije en direccion derecha");
	}

	//validar los sprites def del personaje

	list<SpriteDef*>* spritesDef_actual = this->personaje->getSpritesDef();

	for (list<SpriteDef*>::iterator it_sprites = spritesDef_actual->begin() ; it_sprites != spritesDef_actual->end(); ++it_sprites)
	{
		string nueva_imagen = (*it_sprites)->getImagen();
		string nuevo_id = (*it_sprites)->getIdSprite();
		int nuevo_cant_fotograma = (*it_sprites)->getCantFotogramas();
		int nuevo_fps = (*it_sprites)->getFps();

		if ( !Util::getInstancia()->existeArchivo(nueva_imagen) )
		{
			Logger::getInstance()->info("No existen las imagenes del sprites "+nueva_imagen+". Por defecto se usa sprites_defecto.png");
			(*it_sprites)->setImagen("img/sprites_defecto.png");
		}

		if ( nuevo_cant_fotograma <= 0 )
		{
			(*it_sprites)->setCantFotogramas(1);
			Logger::getInstance()->info("la cant. de fotogramas de la imagen del sprite del personaje es menor o igual a cerop. Se elije uno nuevo con el valor de 1");
		}

		if ( nuevo_fps <= 0 )
		{
			(*it_sprites)->setFps(10);
			Logger::getInstance()->info("el valor de los fps del sprite del personaje es menor o igual a cerop. Se elije uno nuevo con el valor de 10");
		}

//		SpriteDef* spriteDef = new SpriteDef(nueva_imagen, nuevo_id, nuevo_ancho, nuevo_cant_fotograma, nuevo_fps);
//		this->personaje->agregarSpritesDef(spriteDef);
	}

}

