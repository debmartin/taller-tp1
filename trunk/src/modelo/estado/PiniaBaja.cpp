#include "PiniaBaja.h"
#include "../Reposo.h"

#define DANIO_PINIA_BAJA 10

PiniaBaja::PiniaBaja(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), PINIA_BAJA, caja){
    ataqueEstado = new Ataque(DANIO_PINIA_BAJA);
}

PiniaBaja::~PiniaBaja()
{
    //dtor
}

bool PiniaBaja::estaAtacando(){
    return true;
}

bool PiniaBaja::estaDefendiendo(){
    return false;
}
