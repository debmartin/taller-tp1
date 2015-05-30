#ifndef SRC_VISTA_VIBRACION_H_
#define SRC_VISTA_VIBRACION_H_
#include <SDL2/SDL.h>
#include "../modelo/Vector2f.h"

class Vibracion {

private:
	int amplitud;
	bool vibrando;
	double tInicial;
	double T();
public:
	Vibracion();
	Vibracion(float amplitud);
	void iniciar();
	Vector2f getOffset();
	bool estaVibrando();
	virtual ~Vibracion();
};

#endif /* SRC_VISTA_VIBRACION_H_ */
