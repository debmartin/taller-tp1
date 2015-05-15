#include "Bloqueado.h"

#include "EnEspera.h"

Bloqueado::Bloqueado(Trayectoria* trayActual, BVH* caja) :
    Estado(trayActual, BLOQUEADO, caja){
}

Bloqueado::Bloqueado(estado_personaje estadoInicial,Trayectoria* trayActual, BVH* caja) :
    Estado(trayActual, estadoInicial, caja){
}

Bloqueado::~Bloqueado(){
}

bool Bloqueado::estaBloqueado(){
    return true;
}
