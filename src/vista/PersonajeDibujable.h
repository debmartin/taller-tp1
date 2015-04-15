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
#include "../modelo/Personaje.h"
#include "Animacion.h"
#include "Dibujable.h"

#define ID_FONDO "screen-pit"
#define ID_ZUBZERO_QUIETO "sub-zero-reposo"
#define ID_ZUBZERO_CAMINANDO "sub-zero-caminando"
#define ID_ZUBZERO_AGACHADO "sub-zero-agachado"
#define ID_ZUBZERO_SALTANDOVERTICAL "sub-zero-saltando-vertical"
#define ID_ZUBZERO_SALTANDODIAGONAL "sub-zero-saltando-diagonal"


class PersonajeDibujable : public Dibujable, public Observador {
private:
	Sprite* spritePersonaje;
	estado_personaje estado;
	std::string nombre;
    std::map<std::string, Animacion*> animaciones;
public:
	PersonajeDibujable(Animacion* animIni, Vector2f posicionIni, Vector2f tamanioPx, OrientacionSprite orientacion);
	virtual ~PersonajeDibujable();
	void seleccionarSprite();
	void setEstado(estado_personaje unEstado);
	void agregarAnimacion(Animacion* nuevaAnimacion);
	void centrar_en(Vector2f v);
	void dibujar();
	void actualizar();
	void recibirNotificacion(Observable* unObservable);
	Sprite* _getSprite() { return spritePersonaje; }
};

#endif /* SRC_VISTA_PERSONAJEDIBUJABLE_H_ */
