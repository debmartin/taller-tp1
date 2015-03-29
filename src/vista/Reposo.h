#ifndef SRC_VISTA_REPOSO_H_
#define SRC_VISTA_REPOSO_H_
#include "../modelo/Vector2f.h"

class Reposo: public Trayectoria {

private:
	Vector2f posInicial;

public:

	Reposo(Vector2f posInicial):posInicial(posInicial) {};

	Vector2f getPosicion(float tActual) {
		return this->posInicial;
	};

	~Reposo() {}
};

#endif /* SRC_VISTA_REPOSO_H_ */
