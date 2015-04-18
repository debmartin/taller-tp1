#ifndef SRC_VISTA_MRUV_H_
#define SRC_VISTA_MRUV_H_

#include "../modelo/Vector2f.h"
#include "Trayectoria.h"

class MRUV: public Trayectoria {

private:
	Vector2f posInicial;
	Vector2f velInicial;
	Vector2f gravedad;

public:

	MRUV(Vector2f posInicial, Vector2f velInicial, Vector2f gravedad):
		posInicial(posInicial),
		velInicial(velInicial),
		gravedad(gravedad) {};

	virtual Vector2f getPosicion(float tActual) {
		return posInicial + velInicial * tActual + gravedad * 0.5 * tActual * tActual;
	};

	~MRUV() {}
};

#endif /* SRC_VISTA_MRUV_H_ */
