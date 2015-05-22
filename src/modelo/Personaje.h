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
#include "Colisionable.h"
#include "../vista/Posicionable.h"
#include "estado/Estado.h"

#define DELTA_PASO 1
#define ENERGIA_INICIAL 100
#define NUMERO_DE_PERSONAJE_1 1
#define NUMERO_DE_PERSONAJE_2 2

using namespace std;

class Personaje: public Observable, public Loggeable, public Colisionable {
private:
	string id;
	string nombre;
    Vector2f posicionInicial;
	Posicionable* posicionable;
	int energia;
	Objeto* arma;
	Estado* estado;
    map<estado_personaje, BVH*>* cajasPorEstado;
	int numeroJugador;
	float tiempoBloqueo;
	double ancho;
	double alto;
	DireccionObjeto direccion;

public:
	Personaje(
			string id,
			double ancho,
			double alto,
			Vector2f posInicial,
			Posicionable* posc,
			int numJugador,
			map<estado_personaje, BVH*>* cajas_orientacion_derecha,
			DireccionObjeto orientacionInicialPersonaje = DIRECCION_DERECHA);

	virtual ~Personaje();
	double getAlto() const;
	double getAncho() const;
	int getNumeroJugador();
	Vector2f getDimensionesLogicas() const;
	void setPosicion(double x, double y);
	Vector2f getPosicion();
	estado_personaje getEstado();
	int getEnergia();
	void agregarArma(Objeto* unArma);
	Objeto* getArma();
	Vector2f obtenerPosicionEnVentana();
	bool llegoAlLimiteIzquierdo();
	bool llegoAlLimiteDerecho();
	void cambiarTrayectoria(Trayectoria* t);
	void agregarObservador(Observador* unObservador);
	void notificarObservadores();
	void update(Colisionable* enemigo);
	bool estaSaltando();
	bool estaSaltandoVertical();
	bool estaSaltandoDiagonalDerecha();
	bool estaSaltandoDiagonalIzquierda();
	bool estaAgachado();
	bool estaEnReposo();
	bool estaAtacando();
	bool estaDefendiendo();
	bool estaBloqueado();
	bool estaCaminando();
	bool estaMuerto();
	bool ejecutandoMovimientoEspecial();
	void recibirDanio(int danio);
	void bloquearPersonaje(float segundos);
	void calcularNuevaPosicion(Colisionable* enemigo);
	void calcularPosicionSinColision(Colisionable* enemigo);
	void cambiarDireccion();
	void cambiarNumeroPersonaje();
	Estado* verEstado();

	//Movimientos y poderes
	void caminarDerecha();
	void caminarIzquierda();
	void saltarVertical();
	void saltarOblicuoDerecha();
	void saltarOblicuoIzquierda();
	void mantenerReposo();
	void agacharse();
	void piniaAlta();
	void piniaBaja();
	void piniaSaltandoDiagonalDerecha();
	void piniaSaltandoDiagonalIzquierda();
	void piniaSaltandoVertical();
	void patadaAlta();
	void patadaBaja();
	void patadaAltaAgachado();
	void patadaSaltandoVertical();
	void patadaSaltandoDiagonalDerecha();
	void patadaSaltandoDiagonalIzquierda();
	void gancho();
	void defender();
	void defenderAgachado();
	void ejecutarPoder(Poder* poder, Objeto* objeto);
	void arrojarArma();
	void caer();
	void arrastrar(Colisionable* otro);
	bool empujar(Direccion direccionEmpuje, Vector2f diferencia);
	float getAnchoEnvolvente();

	// CAJAS DE COLISION
	virtual void colisionar(Colisionable* otro);
	void cambiarEstado(Estado* nuevo);
	void corregirPorColision(Colisionable* enemigo);
    BVH* obtenerCajaColision();
    bool vaAColisionar(Colisionable* enemigo);
    void espejarBVH();
    void orientar(DireccionObjeto nuevaOrientacion);
    Vector2f getPivote() { return this->obtenerCajaColision()->getPivote(); }

	friend ostream& operator<<(ostream &o, const Personaje &p);
	string toString();
	string getId() const;
	void definirPosicionIncial_enX(double x);
};

#endif /* SRC_MODELO_PERSONAJE_H_ */
