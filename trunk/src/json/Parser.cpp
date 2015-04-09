/*
 * Parser.cpp
 *
 *  Created on: 24/3/2015
 *      Author: ariel
 */

#include "Parser.h"

#include <iostream>

#include "../modelo/Escenario.h"
#include "../modelo/Personaje.h"
#include "../modelo/Ventana.h"
#include "../utils/Logger.h"
#include "../utils/Util.h"

Parser::Parser() {

}

Parser::Parser(string archivo_json)
{
	this->entrada = archivo_json;
	this->ventana = new Ventana();
	this->escenario = new Escenario();
	this->capas = new list<Capa*>;
	this->personaje = new Personaje();

	this->inicializar();
}

void Parser::inicializar()
{
	string escenario_defecto("src/recursos/escenario_defecto.json");

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

void Parser::parsearDesdeJson() {

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
	string p_sprites_imagen = "";
	double p_sprites_ancho = 0;
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
					Capa* capa;
					string imagen_fondo = "";
					double ancho = 0;
					for( Json::ValueIterator it3 = root2[idx_capas].begin() ; it3 != root2[idx_capas].end() ; it3++ )
					{
						const Json::Value key_nivel2 = it3.key();

						if ( key_nivel2.asString() == "imagen_fondo" )
						{
							imagen_fondo = (*it)[idx_capas]["imagen_fondo"].asString();
						}
						else if ( key_nivel2.asString() == "ancho" )
						{
							ancho = (*it)[idx_capas]["ancho"].asDouble();
						}
						else
						{
							Logger::getInstance()->error("Dentro de la capa no se encuentra el parametro "+key_nivel2.asString());
						}

					}
					capa = new Capa(imagen_fondo, ancho);
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
						v_alto_px = (*it)["altopx"].asInt();
					}
					else if ( key_nivel2.asString() == "ancho" )
					{
						v_ancho = (*it)["ancho"].asDouble();
					}
					else if ( key_nivel2.asString() == "anchopx" )
					{
						v_ancho_px = (*it)["anchopx"].asInt();
					}
					else if ( key_nivel2.asString() == "margen_x" )
					{
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
						e_alto = (*it)["alto"].asDouble();
					}
					else if ( key_nivel2.asString() == "ancho" )
					{
						e_ancho = (*it)["ancho"].asDouble();
					}
					//TODO revisar porque este parametro tiene una longitud mas grande. mide 7 en vez de 5!
					else if ( key_nivel2.asString().compare("ypiso") >= 0 )
					{
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
						p_alto = (*it)["alto"].asDouble();
					}
					else if ( key_nivel2.asString().compare("ancho") == 0 )
					{
						p_ancho = (*it)[key_nivel2.asString()].asDouble();
					}
					else if ( key_nivel2.asString().compare("zindex") >= 0 )
					{
						p_zindex = (*it)[key_nivel2.asString()].asInt();
					}
					else if ( key_nivel2.asString() == "sprites" )
					{
						p_sprites_imagen = (*it2)["imagen"].asString();
						p_sprites_ancho = (*it2)["ancho"].asDouble();
					}
					else if ( key_nivel2.asString() == "direccion" )
					{
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

	this->ventana = new Ventana(v_ancho_px, v_alto_px, v_ancho, v_margen_x);
	this->escenario = new Escenario(e_ancho, e_alto, e_ypiso);
	this->personaje = new Personaje(p_ancho, p_alto, p_zindex, p_sprites_imagen, p_sprites_ancho, p_direccion);

}

	 Logger::getInstance()->info("Inicia la validacion semantica del json");
	 this->inciarValidacionSemantica();
	 Logger::getInstance()->info("Termina la validacion semantica del json");

}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

list<Capa*>* Parser::getCapas() const {
	return capas;
}

Escenario* Parser::getEscenario() const {
	return escenario;
}

Personaje* Parser::getPersonaje() const {
	return personaje;
}

Ventana* Parser::getVentana() const {
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
	string personaje_sprites_imagen_nuevo = this->personaje->getSpritesImagen();
	double personaje_sprites_ancho_nuevo = this->personaje->getSpritesAncho();
	double personaje_direccion_nuevo = this->personaje->getDireccion();

	//validar el escenario
	if ( escenario_ancho_nuevo <= 0 )
	{
		escenario_ancho_nuevo = 1200;
		Logger::getInstance()->debug("El ancho del escenario es negativo. Se elije uno nuevo: 1200");
	}

	if ( escenario_alto_nuevo <= 0 )
	{
		escenario_alto_nuevo = 180;
		Logger::getInstance()->debug("El alto del escenario es negativo. Se elije uno nuevo: 800");
	}

	//validacion de la altura del personaje
	if ( personaje_alto_nuevo <= 0 )
	{
		//la eligo como la tercera parte de la altura del escenario
		personaje_alto_nuevo = escenario_alto_nuevo / 3;
		Logger::getInstance()->debug("El alto del personaje es negativo. Se elije uno nuevo que sea la tercera parte del alto del escenario");
	}

	if ( escenario_ypiso_nuevo < 0 || (escenario_alto_nuevo - escenario_ypiso_nuevo) < personaje_alto_nuevo)
	{

		if ( escenario_ypiso_nuevo < 0 )
		{
			Logger::getInstance()->debug("El y del piso del personaje es negativo. Se elije uno nuevo con el valor de cero");
		}
		if ( (escenario_alto_nuevo - escenario_ypiso_nuevo) < personaje_alto_nuevo )
		{
			Logger::getInstance()->debug("El y del piso del personaje sobrepasa al escenario con respecto a su altura. Se elije uno nuevo con el valor de cero");
		}

		escenario_ypiso_nuevo = 0;
	}

	delete this->escenario;
	this->escenario = NULL;
	this->escenario = new Escenario(escenario_ancho_nuevo, escenario_alto_nuevo, escenario_ypiso_nuevo);

	//validar la ventana
	if ( ventana_anchopx_nuevo <= 0 )
	{
		ventana_anchopx_nuevo = 800;
		Logger::getInstance()->debug("El ancho en pixeles de la ventana es negativa. Se elije uno nuevo: 800");
	}

	if ( ventana_altopx_nuevo <= 0 )
	{
		ventana_altopx_nuevo = 600;
		Logger::getInstance()->debug("El alto en pixeles de la ventana es negativa. Se elije uno nuevo: 600");
	}

	if ( ventana_ancho_nuevo <= 0 || ventana_ancho_nuevo > escenario_ancho_nuevo)
	{
		if ( ventana_ancho_nuevo <= 0 )
		{
			Logger::getInstance()->debug("El ancho de la ventana es menor o igual a cero. Se elije uno nuevo que es la mitad del ancho del escenario");
		}
		if ( ventana_ancho_nuevo > escenario_ancho_nuevo )
		{
			Logger::getInstance()->debug("El ancho de la ventana es mas grande que el ancho del escenario. Se elije uno nuevo que es la mitad del ancho del escenario");
		}

		ventana_ancho_nuevo = escenario_ancho_nuevo / 2;

	}

	if ( ventana_margenx_nuevo <= 0 )
	{
		ventana_margenx_nuevo = ventana_ancho_nuevo / 100;
		Logger::getInstance()->debug("El margen en x de la ventana es menor o igual a cero. Se elije uno nuevo que es la centecima del ancho de la ventana");
	}

	delete this->ventana;
	this->ventana = NULL;
	this->ventana = new Ventana(ventana_anchopx_nuevo, ventana_altopx_nuevo, ventana_ancho_nuevo, ventana_margenx_nuevo);

	//validar el personaje
	if ( personaje_ancho_nuevo <= 0 )
	{
		personaje_ancho_nuevo = 15;
		Logger::getInstance()->debug("El ancho del personaje es menor o igual a cero. Se elije uno nuevo con el valor de 15");
	}

	if ( personale_zindex_nuevo < 0 )
	{
		personale_zindex_nuevo = 0;
		Logger::getInstance()->debug("El zindex del personaje es menor a cero. Se elije uno nuevo con el valor de 0");
	}

	if ( !Util::getInstancia()->existeArchivo(personaje_sprites_imagen_nuevo) )
	{
		Logger::getInstance()->info("No existes las imagenes del sprites "+personaje_sprites_imagen_nuevo+". Por defecto se usa sprites_defecto.png");
		personaje_sprites_imagen_nuevo = "sprites_defecto.png";
	}

	if ( personaje_sprites_ancho_nuevo < 0)
	{
		personaje_sprites_ancho_nuevo = 20;
		Logger::getInstance()->debug("el ancho del sprite del personaje es negativo. Se elije uno nuevo con el valor de 20");
	}

	if ( personaje_direccion_nuevo != -1 && personaje_direccion_nuevo != 1 )
	{
		personaje_direccion_nuevo = 1;
		Logger::getInstance()->debug("La configuracion de la direccion del personaje no es la correcta. Se lo dirije en direccion derecha");
	}

	delete this->personaje;
	this->personaje = NULL;
	this->personaje = new Personaje(personaje_ancho_nuevo, personaje_alto_nuevo, personale_zindex_nuevo,
										personaje_sprites_imagen_nuevo, personaje_sprites_ancho_nuevo,
											personaje_direccion_nuevo);


	//validar las capas

	list<Capa*>* capas_nuevas = new list<Capa*>;

	for (list<Capa*>::iterator it_capas = this->capas->begin() ; it_capas != this->capas->end(); it_capas++)
	{
		string nuevo_fondo = (*it_capas)->getImagenFondo();
		double nuevo_ancho = (*it_capas)->getAncho();

		if ( !Util::getInstancia()->existeArchivo(nuevo_fondo) )
		{
			Logger::getInstance()->info("No existe la imagen de fondo para la capa "+nuevo_fondo+". Por defecto se usa fondo_capa_defecto.png");
			nuevo_fondo = "fondo_capa_defecto.png";
		}

		if ( nuevo_ancho <= 0 || nuevo_ancho > escenario_ancho_nuevo )
		{

			if ( nuevo_ancho <= 0 )
			{
				Logger::getInstance()->debug("El ancho de la capa es negativo. Se elije un nuevo ancho igual al ancho del escenario");
			}
			if ( nuevo_ancho > escenario_ancho_nuevo )
			{
				Logger::getInstance()->debug("El ancho de la capa es mayor al ancho del escenario. Se elije un nuevo ancho igual al ancho del escenario");
			}

			nuevo_ancho = escenario_ancho_nuevo;
		}

		Capa* capa_nueva = new Capa(nuevo_fondo, nuevo_ancho);
		capas_nuevas->push_back(capa_nueva);
	}

	this->capas = capas_nuevas;

}

