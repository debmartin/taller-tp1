#include "GolpeandoAlto.h"
#include "../Reposo.h"

#define DANIO_GOLPE_ALTO 10

GolpeandoAlto::GolpeandoAlto(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), GOLPEANDO_ALTO, caja){
    ataqueEstado = new Ataque(DANIO_GOLPE_ALTO);
}

GolpeandoAlto::~GolpeandoAlto()
{
    //dtor
}

bool GolpeandoAlto::estaAtacando(){
    return true;
}

bool GolpeandoAlto::ejecutandoMovimientoEspecial(){
    return true;
}
