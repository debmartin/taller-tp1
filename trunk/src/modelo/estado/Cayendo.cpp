#include "Cayendo.h"
#include "../MRUV.h"

#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)

Cayendo::Cayendo(Vector2f posInicial, Vector2f velocidad, estado_personaje id, BVH* caja) :
    Estado(new MRUV(posInicial, velocidad, VECTOR_GRAVEDAD), id, caja) {
    //ctor
}

Cayendo::~Cayendo()
{
    //dtor
}

bool Cayendo::estaSaltando(){
    return true;
}

bool Cayendo::estaDesplazandoVertical() {
    return true;
}
