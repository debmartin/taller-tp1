#ifndef SRC_VISTA_TRAYECTORIA_H_
#define SRC_VISTA_TRAYECTORIA_H_
#include "../modelo/Vector2f.h"

class Trayectoria {
public:
	virtual Vector2f getPosicion(float tActual) = 0;
	virtual Vector2f getVelocidad(float tActual) = 0;
	virtual ~Trayectoria() {}
};

#endif /* SRC_VISTA_TRAYECTORIA_H_ */
