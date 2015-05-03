/*
 * Personaje.h
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_PERSONAJE_H_
#define SRC_MODELO_PERSONAJE_H_

#include <iostream>
#include <string>

#include "../utils/Loggeable.h"
#include "Observable.h"
#include "Vector2f.h"
#include "Poder.h"
#include "Objeto.h"
//#include "Colisionable.h"
#include "../vista/Posicionable.h"

//class Posicionable;
//class Trayectoria;

#define DELTA_PASO 1
#define DELTA_X 10

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
	AGACHADO,
	CAMINANDO_DERECHA,
	CAMINANDO_IZQUIERDA,
	SALTANDO_VERTICAL,
    SALTANDO_OBLICUO_DERECHA,
    SALTANDO_OBLICUO_IZQUIERDA,
	GOLPEANDO_ALTO,
	GOLPEANDO_BAJO,
	PATEANDO,
	PATEANDO_ALTO,
	PATEANDO_BAJO,
	DEFENDIENDO,
	DEFENDIENDO_AGACHADO
} estado_personaje;

using namespace std;

class Personaje: public Observable, public Loggeable {
private:
    Vector2f posicionInicial;
	double ancho;
	double alto;
	Vector2f posicion;
	Posicionable* posicionable;
	int z_index;
	int energia;
	Objeto* arma;
	estado_personaje estado;
	Trayectoria* trayectoria;
	float tCreacion;

public:
	Personaje();
	Personaje(double ancho, double alto, Vector2f posInicial, Posicionable* posc);
	Personaje& operator=(const Personaje& v2);
	virtual ~Personaje();
	double getAlto() const;
	double getAncho() const;
	Vector2f getDimensionesLogicas() const;
	void setPosicion(int posicion_x, int posicion_y);
	Vector2f getPosicion();
	void setEstado(estado_personaje estado);
	estado_personaje getEstado();
	int getEnergia();
	Vector2f obtenerPosicionEnVentana();
	bool llegoAlLimiteIzquierdo();
	bool llegoAlLimiteDerecho();
	void centrar_en(Vector2f& v);
	void cambiarTrayectoria(Trayectoria* t);
	void agregarObservador(Observador* unObservador);
	void notificarObservadores();
	void update(Vector2f posicionObjetivo);
	bool estaSaltando();
	bool estaAgachado();
	bool estaEnReposo();
	void recibirDanio(int danio);

	//Movimientos y poderes
	void caminarDerecha();
	void caminarIzquierda();
	void saltarVertical();
	void saltarOblicuoDerecha();
	void saltarOblicuoIzquierda();
	void mantenerReposo();
	void agacharse();
	void patada();
	void golpeAlto();
	void golpeBajo();
	void patadaAlta();
	void patadaBaja();
	void defender();
	void defender_agachado();
	void ejecutarPoder(Poder* poder, Objeto* objeto);

	friend ostream& operator<<(ostream &o, const Personaje &p);
	string toString();
};

#endif /* SRC_MODELO_PERSONAJE_H_ */
