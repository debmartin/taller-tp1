#include "CaminandoIzquierda.h"

#include "../Reposo.h"
#include "../MRU.h"

#define VELOCIDAD_DESP_HORIZONTAL_CAMINANDO 215.0f
#define VELOCIDAD_NULA 0.0f
#define VECTOR_VELOCIDAD_NULA Vector2f(0, 0)

CaminandoIzquierda::CaminandoIzquierda(Vector2f posInicial, bool enLimite, BVH* caja) :
    Estado((enLimite) ? ((Trayectoria*) new Reposo(posInicial)) : ((Trayectoria*) new MRU(posInicial, Vector2f(-VELOCIDAD_DESP_HORIZONTAL_CAMINANDO, VELOCIDAD_NULA))), CAMINANDO_IZQUIERDA, caja) {
    //ctor
}

CaminandoIzquierda::~CaminandoIzquierda()
{
    //dtor
}

bool CaminandoIzquierda::estaCaminando(){
    return true;
}
