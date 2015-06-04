#include "PiniaAlta.h"

#include "../Reposo.h"

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

bool PiniaAlta::estaGolpeando(){
    return true;
}

