#ifndef SRC_VISTA_ESCENARIOGRAFICO_H_
#define SRC_VISTA_ESCENARIOGRAFICO_H_

#include "Dibujable.h"
#include <list>


class EscenarioGrafico : public Dibujable {
private:
	std::list<Dibujable*>* dibujables;
	double ancho_logico;
	double alto_logico;
	double y_piso_logico;


public:
	EscenarioGrafico(double ancho, double alto, std::list<Dibujable*>* dibujables);
	virtual ~EscenarioGrafico();
	double getAltoLogico() const;
	double getAnchoLogico() const;
	double getYPisoLogico() const;
	void dibujar();
	void actualizar();
};

#endif /* SRC_VISTA_ESCENARIOGRAFICO_H_ */
