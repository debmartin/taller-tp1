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
#include "../modelo/Vector2f.h"
#include "../modelo/MRU.h"
#include "../modelo/MRUV.h"
#include "Animacion.h"
#include "Dibujable.h"

enum estado_personaje {EN_ESPERA, CAMINANDO_DERECHA, CAMINANDO_IZQUIERDA, SALTANDO};

class PersonajeDibujable : public Dibujable {
private:
	Sprite* personaje;
	estado_personaje estado;
	std::string nombre;
    std::map<std::string, Animacion*> animaciones;
public:
	PersonajeDibujable(Animacion* animIni, Vector2f posicionIni, Vector2f factorEscala);
	virtual ~PersonajeDibujable();
	void seleccionarSprite();
	void setEstado(estado_personaje unEstado);
	void setSprite(Sprite* pSprite);
	void agregarAnimacion(Animacion* nuevaAnimacion);
	void dibujar();
	void actualizar();
};

#endif /* SRC_VISTA_PERSONAJEDIBUJABLE_H_ */
