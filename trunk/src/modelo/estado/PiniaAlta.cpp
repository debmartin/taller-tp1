#include "PiniaAlta.h"

#include "../Reposo.h"

#define DANIO_PINIA_ALTA 10

PiniaAlta::PiniaAlta(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), PINIA_ALTA, caja){
    ataqueEstado = new Ataque(DANIO_PINIA_ALTA);
}

PiniaAlta::~PiniaAlta()
{
    //dtor
}

bool PiniaAlta::estaAtacando(){
    return true;
}

bool PiniaAlta::estaDefendiendo(){
    return false;
}
