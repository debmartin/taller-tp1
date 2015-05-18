/*
 * AABB.cpp
 *
 *  Created on: 27/4/2015
 *      Author: val
 */

#include "AABB.h"

AABB::AABB(Vector2f Vmin, Vector2f Vmax) :
    puntoSupDer(Vmax), puntoInfIzq(Vmin) {
}

AABB::~AABB() {
}

bool AABB::interseccion(AABB* otro) {
    if (puntoInfIzq.X() > otro->puntoSupDer.X() || otro->puntoInfIzq.X() > puntoSupDer.X())
        return false;
    if (puntoInfIzq.X() <= otro->puntoSupDer.X() && puntoInfIzq.X() >= otro->puntoInfIzq.X()) {
        if (puntoInfIzq.Y() <= otro->puntoSupDer.Y() && puntoInfIzq.Y() >= otro->puntoInfIzq.Y())
            return true;
        if (puntoSupDer.Y() <= otro->puntoSupDer.Y() && puntoInfIzq.Y() >= otro->puntoInfIzq.Y())
            return true;
        return (puntoInfIzq.Y() <= otro->puntoInfIzq.Y() && puntoSupDer.Y() >= otro->puntoSupDer.Y());
    }
    if (puntoSupDer.X() <= otro->puntoSupDer.X() && puntoInfIzq.X() >= otro->puntoInfIzq.X()) {
        if (puntoSupDer.Y() <= otro->puntoSupDer.Y() && puntoInfIzq.Y() >= otro->puntoInfIzq.Y())
            return true;
        if (puntoInfIzq.Y() <= otro->puntoSupDer.Y() && puntoInfIzq.Y() >= otro->puntoInfIzq.Y())
            return true;
        return (puntoInfIzq.Y() <= otro->puntoInfIzq.Y() && puntoSupDer.Y() >= otro->puntoSupDer.Y());
    }
    return false;
}

void AABB::desplazarAABB(Vector2f v) {
    puntoInfIzq = puntoInfIzq + v;
    puntoSupDer = puntoSupDer + v;
}

void AABB::espejarAABB(float posMedia){
    float dif = posMedia - puntoInfIzq.X();
    puntoInfIzq.setCoordenada(posMedia + dif, puntoInfIzq.Y());
    dif = puntoSupDer.X() - posMedia;
    puntoSupDer.setCoordenada(posMedia - dif, puntoSupDer.Y());
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
