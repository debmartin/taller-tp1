#include "PateandoBajo.h"
#include "../Reposo.h"

#define DANIO_PATADA_BAJA 10

PateandoBajo::PateandoBajo(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), PATEANDO_BAJO, caja) {
    ataqueEstado = new Ataque(DANIO_PATADA_BAJA);
}

PateandoBajo::~PateandoBajo()
{
    //dtor
}

bool PateandoBajo::estaAtacando(){
    return true;
}

bool PateandoBajo::estaDefendiendo(){
    return false;
}
