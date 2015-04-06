#ifndef SRC_VISTA_VENTANAGRAFICA_H_
#define SRC_VISTA_VENTANAGRAFICA_H_

#include <SDL2/SDL.h>
#include <string>
#include <map>
#include "Sprite.h"
#include "EscenarioGrafico.h"
#include "Posicionable.h"
#include "LimitesLogicos.h"
#include "../modelo/Personaje.h"

using namespace std;

class VentanaGrafica: public Posicionable, public Observador{
private:
	SDL_Window* vWindow;
	SDL_Renderer* vRenderer;
	EscenarioGrafico* escenario;
	double limite_izquierdo;
	double limite_derecho;

	// SINGLETON
	VentanaGrafica();
	static VentanaGrafica* instancia_unica;

public:
	virtual ~VentanaGrafica();
	bool init(string titulo, int xpos, int ypos, int height, int width, bool fullscreen, Personaje unPersonaje);
	void setEscenario(EscenarioGrafico* unEscenario);
	SDL_Renderer* getRenderer();
	void dibujarTodo();
	void cerrar();
	void actualizar();
	LimitesLogicos getLimitesLogicos();
	bool esPosicionValida(Vector2f posicion);
	void actualizarNotificacion();
	static VentanaGrafica* Instance();
};

#endif /* SRC_VISTA_VENTANAGRAFICA_H_ */
