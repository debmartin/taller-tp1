/*
 * Configuracion.cpp
 *
 *  Created on: 20/3/2015
 *      Author: ariel
 */

#include "Configuracion.h"
#include <fstream>

Configuracion* Configuracion::configuracion = NULL;

Configuracion::Configuracion()
{
	this->cargar();
}

Configuracion* Configuracion::getInstance(){
	if (  Configuracion::configuracion == NULL )
		Configuracion::configuracion = new Configuracion();

	return Configuracion::configuracion;
}

void Configuracion::cargar() {
	string nivel_log = "";
	Json::Value root;
	Json::Reader reader;
	ifstream archivo_configuracion("src/recursos/configuracion.json");
	bool ok_parser = reader.parse(archivo_configuracion, root, false);
	if( !ok_parser )
	{
	// Report failures and their locations in the document.
	cout<<"Fallo el parseo del JSON de configuracion"<<endl
	   <<reader.getFormatedErrorMessages()
	   <<endl;
	}
	else
	{
		if( root.size() > 0 ) {

			string nivel_debug = "";
			string pisar_logs = "";

			for( Json::ValueIterator it = root.begin() ; it != root.end() ; it++ )
			{
				const Json::Value clave = it.key();
				if ( clave.asString() == "nivel_debug" )
				{
					nivel_debug = root[clave.asString()].asString();
				}
				else if ( clave.asString() == "pisar_logs" )
				{
					pisar_logs = root[clave.asString()].asString();
				}
			}

			this->nivel_logger = nivel_debug;
			this->pisar_logs = pisar_logs;
		}
	}
}

string Configuracion::getNivelLogger()
{
	return this->nivel_logger;
}

string Configuracion::getPisarLogs() {
	return pisar_logs;
}


Configuracion::~Configuracion() {
}

