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

class Posicionable;
class Trayectoria;

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
    SALTANDO_OBLICUO_IZQUIERDA
} estado_personaje;

using namespace std;

class Personaje: public Observable, public Loggeable {
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
	Vector2f posicionSalto;
	Personaje* oponente;
	bool estaEnLimite;

public:
	Personaje();
	Personaje(double ancho, double alto, Vector2f posInicial, Posicionable* posc);
	virtual ~Personaje();
	double getAlto() const;
	double getAncho() const;
	Vector2f getDimensionesLogicas() const;
	void setPosicion(int posicion_x, int posicion_y);
	Vector2f getPosicion();
	void setEstado(estado_personaje estado);
	estado_personaje getEstado();
	int getVida();
	Vector2f obtenerPosicionEnVentana();
	bool llegoAlLimiteIzquierdo();
	bool llegoAlLimiteDerecho();
	void centrar_en(Vector2f& v);
	void cambiarTrayectoria(Trayectoria* t);
	void agregarObservador(Observador* unObservador);
	void notificarObservadores();
	void update();
	bool estaSaltando();
	bool estaAgachado();
	bool estaEnReposo();
	void cambiarOrientacion();
	bool llegoAlLimite();
	void recibirDanio(int danio);

	//Movimientos y poderes
	void caminarDerecha();
	void caminarIzquierda();
	void saltarVertical();
	void saltarOblicuoDerecha();
	void saltarOblicuoIzquierda();
	void mantenerReposo();
	void agacharse();
	void golpeAlto();
	void golpeBajo();
	void patadaAlta();
	void patadaBaja();
	void defensa();
	void ejecutarPoder(Poder* poder, Objeto* objeto);

	friend ostream& operator<<(ostream &o, const Personaje &p);
	string toString();

	void agregarOponente( Personaje* p) {}
};

#endif /* SRC_MODELO_PERSONAJE_H_ */
