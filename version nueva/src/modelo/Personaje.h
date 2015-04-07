/*
 * Personaje.h
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_PERSONAJE_H_
#define SRC_MODELO_PERSONAJE_H_

#include <SDL2/SDL.h>
#include "../vista/Posicionable.h"
#include "Trayectoria.h"
#include "Reposo.h"
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
	Vector2f posicion;
	Vector2f velocidad;
	Posicionable* limites;
	int z_index;
	int vida;
	int estado;
	Trayectoria* trayectoria;
	float tCreacion;

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
	double getSpritesAncho() const;
	Vector2f obtenerPosicionEnVentana();
	void actualizar();
	void setTrayectoria(Trayectoria* t);
	friend ostream& operator<<(ostream &o, const Personaje &p);

};

#endif /* SRC_MODELO_PERSONAJE_H_ */
