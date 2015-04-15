/*
 * Capa.h
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_CAPA_H_
#define SRC_MODELO_CAPA_H_

#include <iostream>
#include <string.h>
#include "Dibujable.h"
#include "Animacion.h"
#include "Sprite.h"
#include "../modelo/Vector2f.h"

using namespace std;

class Capa : public Dibujable{
private:
	Animacion* animacionCapa;
	Vector2f tamanioLogico;
	float limite_logico_izquierdo;
	Vector2f relacionAspectos;
	Sprite* sprite;
public:
	Capa(Animacion* animCapa, Vector2f& tamInicial, Vector2f& posInicial, Vector2f& relacionAspectos);
	virtual ~Capa();
	double getAnchoLogico();
	double getLimiteLogicoIzquierdo();
	double getLimiteLogicoDerecho();
	void centrar_en(Vector2f posicion, float limiteLogicoIzquierdoVentana, float relacion_de_aspectoX);
    void dibujar();
    void actualizar();
    Sprite* getSprite();
    void setPosicionX(float nuevoX);
};

#endif /* SRC_MODELO_CAPA_H_ */
