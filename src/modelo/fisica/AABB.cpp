/*
 * AABB.cpp
 *
 *  Created on: 27/4/2015
 *      Author: val
 */

#include "AABB.h"

AABB::AABB(Vector2f Vmin, Vector2f Vmax) :
    puntoInfIzq(Vmin), puntoSupDer(Vmax) {
}

AABB::~AABB() {
}

bool AABB::interseccion(AABB* otro) {
    return (puntoInfIzq.X() <= otro->puntoSupDer.X() &&
            otro->puntoInfIzq.X() <= puntoSupDer.X() &&
            puntoInfIzq.Y() <= otro->puntoSupDer.Y() &&
            otro->puntoInfIzq.Y() <= puntoSupDer.Y());
}

void AABB::desplazarAABB(Vector2f v) {
    puntoInfIzq.setCoordenada(puntoInfIzq.X() + v.X(), puntoInfIzq.Y() + v.Y());
    puntoSupDer.setCoordenada(puntoSupDer.X() + v.X(), puntoSupDer.Y() + v.Y());
}

void AABB::espejarAABB(float posicionX){
}

float AABB::getLimiteInferior(){
    return puntoInfIzq.Y();
}

float AABB::getLimiteSuperior(){
    return puntoSupDer.Y();
}

float AABB::getLimiteDerecho(){
    return puntoSupDer.X();
}

float AABB::getLimiteIzquierdo(){
    return puntoInfIzq.X();
}
