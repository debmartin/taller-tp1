/*
 * LimitesLogicos.cpp
 *
 *  Created on: 3/4/2015
 *      Author: val
 */

#include "LimitesLogicos.h"

LimitesLogicos::LimitesLogicos(double ancho, double alto, double y_piso){
	this->ancho_logico = ancho;
	this->alto_logico = alto;
	this->y_piso_logico = y_piso;
}

double LimitesLogicos::getAltoLogico(){
	return this->alto_logico;
}

double LimitesLogicos::getYPisoLogico(){
	return this->y_piso_logico;
}

double LimitesLogicos::getAnchoLogico(){
	return this->ancho_logico;
}

LimitesLogicos::~LimitesLogicos(){
}
