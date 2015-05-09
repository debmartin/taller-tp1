#include "Pateando.h"
#include "../Reposo.h"

#define DANIO_PATADA 10

Pateando::Pateando(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), PATEANDO, caja) {
    ataqueEstado = new Ataque(DANIO_PATADA);
}

Pateando::~Pateando()
{
    //dtor
}

bool Pateando::estaAtacando(){
    return true;
}

bool Pateando::estaDefendiendo(){
    return false;
}
