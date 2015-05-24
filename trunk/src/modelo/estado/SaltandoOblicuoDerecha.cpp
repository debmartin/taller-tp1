#include "SaltandoOblicuoDerecha.h"
#include "../MRUV.h"

#define VELOCIDAD_DESP_HORIZONTAL_SALTANDO 320.0f
#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)

SaltandoOblicuoDerecha::SaltandoOblicuoDerecha(Vector2f posInicial, BVH* caja) :
    Estado(new MRUV(posInicial, Vector2f(VELOCIDAD_DESP_HORIZONTAL_SALTANDO, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD), SALTANDO_OBLICUO_DERECHA, caja){
}

SaltandoOblicuoDerecha::~SaltandoOblicuoDerecha()
{
    //dtor
}

bool SaltandoOblicuoDerecha::estaSaltando(){
    return true;
}

bool SaltandoOblicuoDerecha::estaSaltandoDiagonalDerecha(){
    return true;
}
