#include "SaltandoVertical.h"
#include "../MRUV.h"

#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VELOCIDAD_NULA 0.0f
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)

SaltandoVertical::SaltandoVertical(Vector2f posInicial, BVH* caja) :
    Estado(new MRUV(posInicial, Vector2f(VELOCIDAD_NULA, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD), SALTANDO_VERTICAL, caja, PATEANDO_SALTANDO_VERTICAL){
    //ctor
}

SaltandoVertical::~SaltandoVertical()
{
    //dtor
}

bool SaltandoVertical::estaSaltando(){
    return true;
}

bool SaltandoVertical::estaSaltandoVertical(){
    return true;
}
