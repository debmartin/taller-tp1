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
	SALTANDO_VERTICAL,
    SALTANDO_OBLICUO
} estado_personaje;

using namespace std;

class Personaje: public Observable {
private:
    const Vector2f posicionInicial;
	double ancho;
	double alto;
	Vector2f posicion;
	Posicionable* posicionable;
	int z_index;
	int vida;
	estado_personaje estado;
	Trayectoria* trayectoria;
	float tCreacion;

public:
	Personaje();
	Personaje(double ancho, double alto, Vector2f posInicial, Posicionable* posc);
	virtual ~Personaje();
	double getAlto() const;
	double getAncho() const;
	void setPosicion(int posicion_x, int posicion_y);
	Vector2f getPosicion();
	void setEstado(estado_personaje estado);
	estado_personaje getEstado();
	void setVida(int cantidad);
	int getVida();
	Vector2f obtenerPosicionEnVentana();
	void centrar_en(Vector2f& v);
    void caminarDerecha();
    void caminarIzquierda();
    void saltarVertical();
    void saltarOblicuo();
    void mantenerReposo();
	void cambiarTrayectoria(Trayectoria* t);
	void agregarObservador(Observador* unObservador);
	void notificarObservadores();
	void update();
	bool estaSaltando();
//	friend ostream& operator<<(ostream &o, const Personaje &p);

};

#endif /* SRC_MODELO_PERSONAJE_H_ */
