/*
 * Personaje.h
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_PERSONAJE_H_
#define SRC_MODELO_PERSONAJE_H_

#include "../vista/Posicionable.h"
#include "Observable.h"
#include <iostream>
#include <vector>
#include <string.h>

#include "Vector2f.h"

#define DELTA_PASO 1

enum estado{en_espera, caminando_derecha, caminando_izquierda, saltando};

using namespace std;

class Personaje: public Observable {
private:
	double ancho;
	double alto;
	double sprites_ancho; //TODO: ¿este ancho de Sprite deberia ir en el personaje dibujable?
	Vector2f unaCoordenada;
	Vector2f velocidad;
	Posicionable* limites;
	int z_index;
	int vida;
	int estado;

public:
	Personaje();
	Personaje(double ancho, double alto, Posicionable* limites, double sprites_ancho);
	virtual ~Personaje();
	double getAlto() const;
	double getAncho() const;
	int getZindex() const;
	void setPosicion(int posicion_x, int posicion_y);
	Vector2f getPosicion();
	void setEstado(int estado);
	int getEstado();
	void setVida(int cantidad);
	int getVida();
	void aumentar_velocidadX();
	void disminuir_velocidadX();
	void aumentar_velocidadY();
	void disminuir_velocidadY();
	void mover();
	double getSpritesAncho() const;
	Vector2f obtenerPosicionEnVentana();
	void actualizar();
	friend ostream& operator<<(ostream &o, const Personaje &p);

};

#endif /* SRC_MODELO_PERSONAJE_H_ */
