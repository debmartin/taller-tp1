#ifndef SRC_VISTA_MRU_H_
#define SRC_VISTA_MRU_H_
#include "../modelo/Vector2f.h"

class MRU: public Trayectoria {

private:
	Vector2f posInicial;
	Vector2f velInicial;
	float deltaTiempo;
	float tActual;

public:

	MRU(Vector2f posInicial, Vector2f velInicial, float deltaTiempo):
		posInicial(posInicial),
		velInicial(velInicial),
		deltaTiempo(deltaTiempo),
		tActual(0) {};

	virtual void avanzarTiempo() {
		tActual += deltaTiempo;
	};

	virtual Vector2f getPosicion() {
		Vector2f posActual= posInicial + velInicial * tActual;
		return posActual;
	};

};

#endif /* SRC_VISTA_REPOSO_H_ */
