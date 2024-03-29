#ifndef SRC_VISTA_MRU_H_
#define SRC_VISTA_MRU_H_
#include "../modelo/Vector2f.h"

class MRU: public Trayectoria {

private:
	Vector2f posInicial;
	Vector2f velInicial;

public:

	MRU(Vector2f posInicial, Vector2f velInicial):
		posInicial(posInicial),
		velInicial(velInicial) {};

	virtual Vector2f getPosicion(float tActual) {
		return posInicial + velInicial*tActual;
	};
	virtual Vector2f getVelocidad(float tActual) {
		return velInicial;
	}
	void reducirVelocidad(Vector2f velocidadNueva) {
        velInicial = velocidadNueva;
    }
	~MRU() {}
};

#endif /* SRC_VISTA_REPOSO_H_ */
