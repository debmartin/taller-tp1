/*
 * PersonajeDibujable.h
 *
 *  Created on: 25/3/2015
 *      Author: val
 */

#ifndef SRC_VISTA_PERSONAJEDIBUJABLE_H_
#define SRC_VISTA_PERSONAJEDIBUJABLE_H_

#include "VentanaGrafica.h"

#include "Sprite.h"
#include <iostream>
#include <vector>
#include <string.h>
#include "../modelo/Vector2.h"
#include "../modelo/Vector2f.h"
#include "MRU.h"
#include "MRUV.h"
#include "Animacion.h"


enum estado_personaje {EN_ESPERA, CAMINANDO_DERECHA, CAMINANDO_IZQUIERDA, SALTANDO};

class PersonajeDibujable{
private:
	Sprite* personaje;
	estado_personaje estado;
	std::string nombre;
    std::map<std::string, Animacion*> animaciones;
public:
	PersonajeDibujable(std::pair<double,double> posicionIni, Animacion* animIni);
	virtual ~PersonajeDibujable();
	void seleccionarSprite();
	void setEstado(estado_personaje unEstado);
	void setSprite(Sprite* pSprite);
	void agregarAnimacion(Animacion* nuevaAnimacion);
};

#endif /* SRC_VISTA_PERSONAJEDIBUJABLE_H_ */
