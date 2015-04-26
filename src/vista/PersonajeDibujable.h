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
#define ID_ZUBZERO_QUIETO "reposo"
#define ID_ZUBZERO_CAMINANDO "caminando"
#define ID_ZUBZERO_AGACHADO "agachado"
#define ID_ZUBZERO_SALTANDOVERTICAL "saltando-vertical"
#define ID_ZUBZERO_SALTANDODIAGONAL "saltando-diagonal"


class PersonajeDibujable : public Dibujable, public Observador {
private:
	Sprite* spritePersonaje;
	estado_personaje estado;
	std::string nombre;
    std::map<std::string, Animacion*> animaciones;
public:
    PersonajeDibujable();
	PersonajeDibujable(Animacion* animIni, Vector2f posicionIni, Vector2f tamanioPx, OrientacionSprite orientacion);
	virtual ~PersonajeDibujable();
	void seleccionarSprite();
	void setEstado(estado_personaje unEstado);
	void agregarAnimacion(Animacion* nuevaAnimacion);
	void centrar_en(Vector2f v, float limiteLogicoIzquierdoVentana, float relacion_de_aspectoX);
	void dibujar();
	void actualizar();
	void recibirNotificacion(Observable* unObservable);
	Sprite* _getSprite() { return spritePersonaje; }
	void cambiarOrientacion();
};

#endif /* SRC_VISTA_PERSONAJEDIBUJABLE_H_ */
