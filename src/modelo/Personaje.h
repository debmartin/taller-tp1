/*
 * Personaje.h
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_PERSONAJE_H_
#define SRC_MODELO_PERSONAJE_H_

#include <iostream>
#include <vector>
#include <string.h>

#include "Vector2.h"

#define DELTA_PASO 1

enum estado{en_espera, caminando_derecha, caminando_izquierda, saltando};

using namespace std;

class Personaje {
private:
	float ancho;
	float alto;
	int z_index;
	int limite_superior;
	int limite_inferior;
	int limite_derecho;
	int limite_izquierdo;
	vector<string> sprites;
	Vector2 unaCoordenada;
	Vector2 velocidad;
	int vida;
	int estado;

public:
	Personaje();
	virtual ~Personaje();
	float getAlto() const;
	void setAlto(float alto);
	float getAncho() const;
	void setAncho(float ancho);
	vector<string> getSprites() const;
	void setSprites(vector<string> sprites);
	int getZindex() const;
	void setZindex(int z_index);
	void setPosicion(int posicion_x, int posicion_y);
	Vector2 getPosicion();
	void setLimiteSuperior(int limite);
	int getLimiteSuperior();
	void setLimiteInferior(int limite);
	int getLimiteInferior();
	void setLimiteDerecho(int limite);
	int getLimiteDerecho();
	void setLimiteIzquierdo(int limite);
	int getLimiteIzquierdo();
	void setEstado(int estado);
	int getEstado();
	void setVida(int cantidad);
	int getVida();
	void aumentar_velocidadX();
	void disminuir_velocidadX();
	void aumentar_velocidadY();
	void disminuir_velocidadY();
	void mover();
};

#endif /* SRC_MODELO_PERSONAJE_H_ */
