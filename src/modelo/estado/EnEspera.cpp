#include "EnEspera.h"

#include "../Reposo.h"

EnEspera::EnEspera(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), EN_ESPERA, caja) {
    Logger::getInstance()->debug("Personaje: en reposo.");
    ataqueEstado = new Ataque(DANIO_NULO);
}

EnEspera::~EnEspera()
{
    //dtor
}

bool EnEspera::estaEsperando(){
    return true;
}

bool EnEspera::estaAtacando(){
    return false;
}

