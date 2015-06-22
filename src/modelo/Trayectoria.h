#ifndef SRC_VISTA_TRAYECTORIA_H_
#define SRC_VISTA_TRAYECTORIA_H_
#include "../modelo/Vector2f.h"

class Trayectoria {
public:
	virtual Vector2f getPosicion(float tActual) = 0;
	virtual Vector2f getVelocidad(float tActual) = 0;
	virtual ~Trayectoria() {}
	virtual void reducirVelocidad(Vector2f velocidadNueva) = 0;
	virtual void actualizar(Vector2f nuevaPosicion) = 0;
};

#endif /* SRC_VISTA_TRAYECTORIA_H_ */
