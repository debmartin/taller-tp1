#include "CaminandoDerecha.h"
#include "../Reposo.h"
#include "../MRU.h"

#define VELOCIDAD_DESP_HORIZONTAL_CAMINANDO 215.0f
#define VELOCIDAD_DESP_HORIZONTAL_RETROCEDIENDO 150.0f
#define VELOCIDAD_NULA 0.0f
#define VECTOR_VELOCIDAD_NULA Vector2f(0, 0)
#define D_IZQUIERDA 1

CaminandoDerecha::CaminandoDerecha(Vector2f posInicial, bool enLimite, BVH* caja, bool direccion) :
    Estado((enLimite) ? ((Trayectoria*) new Reposo(posInicial)) : ((Trayectoria*) new MRU(posInicial, Vector2f(VELOCIDAD_DESP_HORIZONTAL_CAMINANDO, VELOCIDAD_NULA))), CAMINANDO_DERECHA, caja) {
    if(direccion == D_IZQUIERDA)
    	getTrayectoria()->reducirVelocidad(Vector2f(VELOCIDAD_DESP_HORIZONTAL_RETROCEDIENDO, VELOCIDAD_NULA));
    	//ctor
}

CaminandoDerecha::~CaminandoDerecha()
{
    //dtor
}

bool CaminandoDerecha::estaCaminando(){
    return true;
}

