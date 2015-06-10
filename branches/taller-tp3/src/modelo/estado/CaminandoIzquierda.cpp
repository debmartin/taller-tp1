#include "CaminandoIzquierda.h"

#include "../Reposo.h"
#include "../MRU.h"

#define VELOCIDAD_DESP_HORIZONTAL_CAMINANDO 215.0f
#define VELOCIDAD_DESP_HORIZONTAL_RETROCEDIENDO 150.0f
#define VELOCIDAD_NULA 0.0f
#define VECTOR_VELOCIDAD_NULA Vector2f(0, 0)
#define D_DERECHA 0

CaminandoIzquierda::CaminandoIzquierda(Vector2f posInicial, BVH* caja, bool direccion) :
    Estado((Trayectoria*) new MRU(posInicial, Vector2f(-VELOCIDAD_DESP_HORIZONTAL_CAMINANDO, VELOCIDAD_NULA)), CAMINANDO_IZQUIERDA, caja, CAMINANDO_IZQUIERDA) {
//	if(direccion == D_DERECHA)
//		    getTrayectoria()->reducirVelocidad(Vector2f(-VELOCIDAD_DESP_HORIZONTAL_RETROCEDIENDO, VELOCIDAD_NULA));
	//ctor
}

CaminandoIzquierda::~CaminandoIzquierda()
{
    //dtor
}

bool CaminandoIzquierda::estaCaminando(){
    return true;
}
