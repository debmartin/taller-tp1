/*
 * Arma.h
 *
 *  Created on: 2/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ARMA_H_
#define SRC_MODELO_ARMA_H_

#include "Objeto.h"
#include "Observable.h"
#include "MRU.h"
#include "../vista/VentanaGrafica.h"
#include <SDL2/SDL_timer.h>

#define DANIO_ARMA	10
#define VELOCIDAD_ARMA_NULA 0.0f

class Arma: public Objeto, public Observable {
private:
	int damage;
	Vector2f posicion;
	int velocidad_arma;
	estado_objeto estado;
	Trayectoria* trayectoria;
	float tCreacion;
public:
	Arma();
	Arma(int velocidad);
	virtual ~Arma();
	int quitarEnergia();
	void posicionar(Vector2f);
	Vector2f obtenerPosicionEnVentana();
	void update();
	void agregarObservador(Observador* unObservador);
	void notificarObservadores();
	void cambiarEstado(estado_objeto estado);
	void cambiarTrayectoria(Trayectoria* unaTrayectoria);
	void arrojar();
	estado_objeto getEstado();
};

#endif /* SRC_MODELO_ARMA_H_ */
