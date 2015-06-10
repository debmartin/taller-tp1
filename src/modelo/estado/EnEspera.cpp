#include "EnEspera.h"

#include "../Reposo.h"

EnEspera::EnEspera(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), EN_ESPERA, caja, PATEANDO_ALTO) {
    Logger::getInstance()->debug("Personaje: en reposo.");
}

EnEspera::EnEspera(Vector2f posInicial, estado_personaje estado,BVH* caja) :
    Estado(new Reposo(posInicial), estado, caja, PATEANDO_ALTO) {
}

EnEspera::~EnEspera()
{
    //dtor
}

bool EnEspera::estaEsperando(){
    return true;
}

