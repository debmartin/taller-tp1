#ifndef SRC_VISTA_VENTANAGRAFICA_H_
#define SRC_VISTA_VENTANAGRAFICA_H_

#include <map>
#include "Renderizador.h"
#include "Sprite.h"
#include "EscenarioGrafico.h"
#include "Posicionable.h"
#include "LimitesLogicos.h"
#include "../modelo/Personaje.h"

using namespace std;

class VentanaGrafica: public Posicionable, public Observador{
private:
	EscenarioGrafico* escenario;
	double ancho;
	double limite_izquierdo;
	double limite_derecho;

	// SINGLETON
	VentanaGrafica();
	static VentanaGrafica* instancia_unica;

public:
	virtual ~VentanaGrafica();
	bool init(string titulo, int xpos, int ypos, int height, int width, bool fullscreen);
	void setEscenario(EscenarioGrafico* unEscenario);
	void dibujarTodo();
	void cerrar();
	void actualizar();
	LimitesLogicos getLimitesLogicos();
	bool esPosicionValida(Vector2f posicion);
	void recibirNotificacion(Observable* unObservable);
	static VentanaGrafica* Instance();
};

#endif /* SRC_VISTA_VENTANAGRAFICA_H_ */
