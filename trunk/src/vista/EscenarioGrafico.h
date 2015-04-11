#ifndef SRC_VISTA_ESCENARIOGRAFICO_H_
#define SRC_VISTA_ESCENARIOGRAFICO_H_

#include "Dibujable.h"
#include "Sprite.h"
#include "Capa.h"
#include <list>

typedef enum
{
    DERECHA,
    IZQUIERDA
} Sentido;

class EscenarioGrafico : public Dibujable {
private:
	std::list<Dibujable*>* dibujables;
	std::list<Capa*>* capas;

	double ancho_logico;
	double alto_logico;
	double y_piso_logico;


public:
	EscenarioGrafico(double ancho_logico, double alto_logico, double y_piso_logico, std::list<Dibujable*>* dibujables, std::list<Capa*>*);
	virtual ~EscenarioGrafico();
	double getAltoLogico() const;
	double getAnchoLogico() const;
	double getYPisoLogico() const;
	void dibujar();
	void actualizar();
	void centrar_capas();
	void scrollear_capas();
	bool esValida(Vector2f posicion);
};

#include "VentanaGrafica.h"

#endif /* SRC_VISTA_ESCENARIOGRAFICO_H_ */
