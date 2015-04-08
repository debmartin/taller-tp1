/*
 * Personaje.h
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_PERSONAJE_H_
#define SRC_MODELO_PERSONAJE_H_

#include <SDL2/SDL.h>
#include "../vista/VentanaGrafica.h"
#include "../vista/Posicionable.h"
#include "Trayectoria.h"
#include "Reposo.h"
#include "MRU.h"
#include "MRUV.h"
#include "Observable.h"
#include <iostream>
#include <vector>
#include <string.h>

#include "Vector2f.h"

#define DELTA_PASO 1

typedef enum Movimiento
{
	REPOSO,
    CAMINAR_DERECHA,
    CAMINAR_IZQUIERDA,
	SALTAR_VERTICAL
} Movimiento;

typedef enum estado_personaje
{
	EN_ESPERA,
	CAMINANDO_DERECHA,
	CAMINANDO_IZQUIERDA,
	SALTANDO_VERTICAL
} estado_personaje;

using namespace std;

class Personaje: public Observable {
private:
	double ancho;
	double alto;
	double sprites_ancho; //TODO: ¿este ancho de Sprite deberia ir en el personaje dibujable?
	Vector2f posicion;
	Posicionable* limites;
	int z_index;
	int vida;
	estado_personaje estado;
	Trayectoria* trayectoria;
	float tCreacion;

public:
	Personaje();
	Personaje(double ancho, double alto, double sprites_ancho, Vector2f posInicial);
	virtual ~Personaje();
	double getAlto() const;
	double getAncho() const;
	int getZindex() const;
	void setPosicion(int posicion_x, int posicion_y);
	Vector2f getPosicion();
	void setEstado(estado_personaje estado);
	estado_personaje getEstado();
	void setVida(int cantidad);
	int getVida();
	double getSpritesAncho() const;
	Vector2f obtenerPosicionEnVentana();
	//void actualizar();
	void mover(Movimiento unMovimiento);
	void setTrayectoria(Trayectoria* t);
	void agregarObservador(Observador* unObservador);
	void notificarObservadores();
	void update();
	friend ostream& operator<<(ostream &o, const Personaje &p);

};

#endif /* SRC_MODELO_PERSONAJE_H_ */
