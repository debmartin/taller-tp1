/*
 * Parser.cpp
 *
 *  Created on: 24/3/2015
 *      Author: ariel
 */

#include "Parser.h"

Parser::Parser() {
	// TODO Auto-generated constructor stub

}

void Parser::inicializar()
{
	ifstream archivo_escenario(this->entrada.c_str());

	 this->bienParseado = this->reader.parse(archivo_escenario, this->root, false);
}

bool Parser::ejecutar() {

	 if( !this->bienParseado )
	 {
	   // Report failures and their locations in the document.
	   cout<<"Failed to parse JSON"<<endl
	       <<reader.getFormatedErrorMessages()
	       <<endl;
	   return false;
	 }

	 if( root.size() > 0 ) {
	 		for( Json::ValueIterator it = root.begin() ; it != root.end() ; it++ )
	 		{
	 			const Json::Value key_nivel1 = it.key();
	 			//cout<<key_nivel1.asString()<<endl;

	 			const Json::Value root2 = root[key_nivel1.asString()];
	 			if ( root2.isArray() )
	 			{
	 				for (int index = 0; index < root2.size(); ++index)
	 				{
	 					if ( root2[index].isObject() )
	 					{
	 						for( Json::ValueIterator it3 = root2[index].begin() ; it3 != root2[index].end() ; it3++ )
	 						{
	 							const Json::Value key_nivel_ = it3.key();
	 							//cout<<"valor["<<index<<"]"<<key_nivel_.asString()<<endl;
	 						}

	 					}

	 					//cout << "/n " << root2[index].asString() << endl;
	 				}
	 			}
	 			else
	 			{
	 				for( Json::ValueIterator it2 = root2.begin() ; it2 != root2.end() ; it2++ )
	 				{
	 					const Json::Value key_nivel2 = it2.key();
	 					//cout<<"/n "<<key_nivel2.asString()<<endl;
	 				}
	 			}
	 		}
	 	}

	 return true;
}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

bool Parser::isBienParseado() const {
	return bienParseado;
}

const vector<capa>& Parser::getCapas() const {
	return capas;
}

float Parser::getEscenarioAlto() const {
	return escenario_alto;
}

float Parser::getEscenarioAncho() const {
	return escenario_ancho;
}

int Parser::getPersonajeAlto() const {
	return personaje_alto;
}

int Parser::getPersonajeAncho() const {
	return personaje_ancho;
}

const vector<string>& Parser::getPersonajeSprites() const {
	return personaje_sprites;
}

int Parser::getPersonajeZindex() const {
	return personaje_zindex;
}

const Json::Reader& Parser::getReader() const {
	return reader;
}

const Json::Value& Parser::getRoot() const {
	return root;
}

int Parser::getVentanaAltopx() const {
	return ventana_altopx;
}

int Parser::getVentanaAncho() const {
	return ventana_ancho;
}

int Parser::getVentanaAnchopx() const {
	return ventana_anchopx;
}

const string& Parser::getEntrada() const {
	return entrada;
}

void Parser::setEntrada(const string& entrada) {
	this->entrada = entrada;
}

int Parser::getEscenarioYpiso() const {
	return escenario_ypiso;
}
