#include "PiniaBaja.h"
#include "../Reposo.h"

PiniaBaja::PiniaBaja(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), PINIA_BAJA, caja, SALTANDO_VERTICAL){
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
