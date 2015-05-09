#include "GolpeandoBajo.h"
#include "../Reposo.h"

#define DANIO_GOLPE_BAJO 10

GolpeandoBajo::GolpeandoBajo(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), GOLPEANDO_BAJO, caja){
    ataqueEstado = new Ataque(DANIO_GOLPE_BAJO);
}

GolpeandoBajo::~GolpeandoBajo()
{
    //dtor
}

bool GolpeandoBajo::estaAtacando(){
    return true;
}

bool GolpeandoBajo::estaDefendiendo(){
    return false;
}
