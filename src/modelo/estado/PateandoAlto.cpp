#include "PateandoAlto.h"
#include "../Reposo.h"

#define DANIO_PATADA_ALTA 10

PateandoAlto::PateandoAlto(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), PATEANDO_ALTO, caja) {
    ataqueEstado = new Ataque(DANIO_PATADA_ALTA);
}

PateandoAlto::~PateandoAlto()
{
    //dtor
}

bool PateandoAlto::estaAtacando(){
    return true;
}

bool PateandoAlto::ejecutandoMovimientoEspecial(){
    return true;
}
