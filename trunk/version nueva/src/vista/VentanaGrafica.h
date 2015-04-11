#ifndef SRC_VISTA_VENTANAGRAFICA_H_
#define SRC_VISTA_VENTANAGRAFICA_H_

#include <map>
#include "Renderizador.h"
#include "Sprite.h"
#include "EscenarioGrafico.h"
#include "Posicionable.h"
#include "../modelo/Observador.h"
#include "../modelo/Personaje.h"

using namespace std;

class VentanaGrafica: public Posicionable, public Observador{
private:
	EscenarioGrafico* escenario;
	double ancho_ventanaPx;
	double ancho_logico_ventana;
	double limite_logico_izquierdo;

	// SINGLETON
	VentanaGrafica();
	static VentanaGrafica* instancia_unica;

public:
	virtual ~VentanaGrafica();
	bool init(string titulo, Vector2f posicion, Vector2f tamanioPixels, int ancho_logico, bool fullscreen);
	void agregarEscenario(EscenarioGrafico* unEscenario);
	void dibujarTodo();
	void actualizar();
	float getLimiteLogicoIzquierdo();
	float getLimiteLogicoDerecho();
	bool esPosicionValida(Vector2f posicion);
	void recibirNotificacion(Observable* unObservable);
	float relacion_de_aspectoX();
	static VentanaGrafica* Instance();
    bool esValida(Vector2f posicion);
    Vector2f calcularPosicionEnVentana(Vector2f posicionLogica);
};

#endif /* SRC_VISTA_VENTANAGRAFICA_H_ */
