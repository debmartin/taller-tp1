#ifndef SRC_VISTA_VENTANAGRAFICA_H_
#define SRC_VISTA_VENTANAGRAFICA_H_

#include <map>
#include "Renderizador.h"
#include "Sprite.h"
#include "EscenarioGrafico.h"
#include "Posicionable.h"
#include "LimitesLogicos.h"
#include "../modelo/Observador.h"
#include "../modelo/Personaje.h"

using namespace std;

class VentanaGrafica: public Posicionable, public Observador{
private:
	EscenarioGrafico* escenario;
	double ancho_ventanaPx;
	double ancho_logico_ventana;
	//TODO: Val. borrar uno de los limites.
	double limite_logico_izquierdo;
	double limite_logico_derecho;

	// SINGLETON
	VentanaGrafica();
	static VentanaGrafica* instancia_unica;

public:
	virtual ~VentanaGrafica();
	bool init(string titulo, int xpos, int ypos, int alto, int anchoPx, int ancho_logico, bool fullscreen);
	void setEscenario(EscenarioGrafico* unEscenario);
	void dibujarTodo();
	void cerrar();
	void actualizar();
	float getLimiteLogicoIzquierdo();
	float getLimiteLogicoDerecho();
	LimitesLogicos getLimitesLogicos();
	bool esPosicionValida(Vector2f posicion);
	void recibirNotificacion(Observable* unObservable);
	float relacion_de_aspectoX();
	static VentanaGrafica* Instance();
};

#endif /* SRC_VISTA_VENTANAGRAFICA_H_ */
