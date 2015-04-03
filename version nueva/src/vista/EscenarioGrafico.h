#ifndef SRC_VISTA_ESCENARIOGRAFICO_H_
#define SRC_VISTA_ESCENARIOGRAFICO_H_

#include "Dibujable.h"
#include <list>


class EscenarioGrafico : public Dibujable {
private:
	std::list<Dibujable*>* dibujables;
	double ancho;
	double alto;

public:
	EscenarioGrafico(double ancho, double alto, std::list<Dibujable*>* dibujables);
	virtual ~EscenarioGrafico();
	double getAlto() const;
	double getAncho() const;
	void dibujar();
};

#endif /* SRC_VISTA_ESCENARIOGRAFICO_H_ */
