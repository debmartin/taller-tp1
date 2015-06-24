#ifndef SRC_VISTA_VENTANAGRAFICA_H_
#define SRC_VISTA_VENTANAGRAFICA_H_

#include <map>
#include "Renderizador.h"
#include "Sprite.h"
#include "EscenarioGrafico.h"
#include "Posicionable.h"
#include "../modelo/Observador.h"
#include "../modelo/Personaje.h"
#include "Vibracion.h"

#define MOSTRAR_CAJAS_COLISION false
#define DELTA_X2 110
#define DELTA_X 10
#define DELTA 20
#define PORCENTAJE_TAMANIO_VENTANA 0.98f
#define PORCENTAJE_ESPACIO_INFERIOR_VENTANA (1.0f - PORCENTAJE_TAMANIO_VENTANA)
using namespace std;

class VentanaGrafica: public Posicionable, public Observador{
private:
	EscenarioGrafico* escenario;
	Vector2f tamPixels;
	Vector2f tamLogico;
	Vector2f posLogico;
	Vibracion vibracion;

	// SINGLETON
	VentanaGrafica();
	static VentanaGrafica* instancia_unica;
	
public:
	virtual ~VentanaGrafica();
	bool init(string titulo, Vector2f posicionVentanaPrograma, Vector2f tamanioPixels, Vector2f tamanioLogico, bool fullscreen);
	void agregarEscenario(EscenarioGrafico* unEscenario);
	void dibujarTodo();
	void actualizar();
	void centrar_ventana();
	float getLimiteLogicoIzquierdo();
	float getLimiteLogicoDerecho();
	float getLimiteLogicoSuperior();
	float getAnchoLogico();
	float getAnchoPx();
	bool llegoAlLimiteDerecho(Vector2f posicion);
	bool llegoAlLimiteIzquierdo(Vector2f posicion);
	bool esPosicionValida(Vector2f posicion);
	void recibirNotificacion(Observable* unObservable);
	float relacion_de_aspectoX();
	float relacion_de_aspectoY();
	Vector2f obtener_relacion_aspectos();
	static VentanaGrafica* Instance();
    bool esValida(Vector2f posicion, double ancho);
    Vector2f calcularPosicionEnVentana(Vector2f posicionLogica);
    bool enExtremos(float distanciaEntreElementos, double ancho);
	EscenarioGrafico* getEscenario() const;
	void vibrar();
	Vector2f getPosLogico();
	friend ostream& operator<<(ostream &o, const VentanaGrafica &c);
};

#endif /* SRC_VISTA_VENTANAGRAFICA_H_ */
