#ifndef SRC_VISTA_REPOSO_H_
#define SRC_VISTA_REPOSO_H_
#include "../modelo/Vector2.h"

class Reposo: public Trayectoria {

private:
	Vector2 posInicial;

public:

	Reposo(Vector2 posInicial):posInicial(posInicial) {};

	virtual void avanzarTiempo() {};

	virtual Vector2 getPosicion() {	return this->posInicial; };

};

#endif /* SRC_VISTA_REPOSO_H_ */
