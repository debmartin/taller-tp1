#include "Defendiendo.h"
#include "../Reposo.h"

Defendiendo::Defendiendo(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), DEFENDIENDO, caja) {
	ataqueEstado = new Ataque(DANIO_NULO);
    //ctor
}

Defendiendo::~Defendiendo()
{
    //dtor
}

bool Defendiendo::estaAtacando(){
    return false;
}

bool Defendiendo::estaDefendiendo(){
    return true;
}
