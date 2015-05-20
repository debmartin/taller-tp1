#include "DefendiendoAgachado.h"
#include "../Reposo.h"

DefendiendoAgachado::DefendiendoAgachado(Vector2f posInicial, BVH* caja) :
    Estado(new Reposo(posInicial), DEFENDIENDO_AGACHADO, caja) {
	ataqueEstado = new Ataque(DANIO_NULO);
    //ctor
}

DefendiendoAgachado::~DefendiendoAgachado()
{
    //dtor
}

bool DefendiendoAgachado::estaAtacando(){
    return false;
}

bool DefendiendoAgachado::estaDefendiendo(){
    return true;
}
