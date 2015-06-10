#include "Defendiendo.h"
#include "../Reposo.h"

Defendiendo::Defendiendo(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), DEFENDIENDO, caja, GANCHO) {
    //ctor
}

Defendiendo::~Defendiendo()
{
    //dtor
}

bool Defendiendo::estaDefendiendo(){
    return true;
}
