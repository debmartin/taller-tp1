#ifndef SRC_VISTA_MRUV_H_
#define SRC_VISTA_MRUV_H_

#include "../modelo/Vector2.h"

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
		return posInicial + velInicial * tActual + 0.5 * tActual * tActual *  gravedad;
	};

	~MRUV() {}
};

#endif /* SRC_VISTA_MRUV_H_ */
