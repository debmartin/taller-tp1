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
#include "Colisionable.h"
#include <SDL2/SDL_timer.h>

#define DANIO_ARMA	10
#define VELOCIDAD_ARMA_NULA 0.0f

class Arma: public Objeto, public Observable, public Colisionable{
private:
	int damage;
	int velocidad_arma;
	double anchoArma;
	double altoArma;
	estado_objeto estado;
	Trayectoria* trayectoria;
	float tCreacion;
	DireccionObjeto direccionArma;
	BVH* cajaBVH_arma;

public:
	Arma(int velocidad, double ancho, double alto, BVH* caja);
	virtual ~Arma();
	int quitarEnergia();
	int obtenerDanio();
	void posicionar(Vector2f);
	Vector2f obtenerPosicionEnVentana();
	void update(Colisionable* enemigo);
	void agregarObservador(Observador* unObservador);
	void notificarObservadores();
	DireccionObjeto getDireccion();
	void cambiarEstado(estado_objeto estado);
	void orientar(DireccionObjeto dir);
	void cambiarTrayectoria(Trayectoria* unaTrayectoria);
	void arrojar();
	estado_objeto getEstado();
	Estado* verEstado();

	void colisionar(Colisionable* otro);
    bool vaAColisionar(Colisionable* otro);
    BVH* obtenerCajaColision();
    bool haySuperposicion(BVH* otraCaja);
    bool empujar(Vector2f& diferencia);
    bool estaEnReposo();
    bool estaAtacando();
};

#endif /* SRC_MODELO_ARMA_H_ */
