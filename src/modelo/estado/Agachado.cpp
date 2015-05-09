#include "Agachado.h"

#include "../Reposo.h"

Agachado::Agachado(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), AGACHADO, caja) {
    //ctor
}

Agachado::~Agachado()
{
    //dtor
}

bool Agachado::estaAgachado(){
    return true;
}
