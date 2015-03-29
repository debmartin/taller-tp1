#ifndef SRC_VISTA_MRUV_H_
#define SRC_VISTA_MRUV_H_

#include "../modelo/Vector2.h"

class MRUV: public Trayectoria {

private:
	Vector2f posInicial;
	Vector2f velInicial;
	Vector2f gravedad;
	float deltaTiempo;
	float tActual;

public:

	MRUV(Vector2f posInicial, Vector2f velInicial, Vector2f gravedad, float deltaTiempo):
		posInicial(posInicial),
		velInicial(velInicial),
		gravedad(gravedad),
		deltaTiempo(deltaTiempo),
		tActual(0) {};

	virtual void avanzarTiempo() {
		tActual += deltaTiempo;
	};

	virtual Vector2f getPosicion() {
		Vector2f posActual= posInicial + velInicial * tActual + 0.5 * tActual * tActual *  gravedad;
		return posActual;
	};

};

#endif /* SRC_VISTA_MRUV_H_ */
