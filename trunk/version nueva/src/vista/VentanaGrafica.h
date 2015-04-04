#ifndef SRC_VISTA_VENTANAGRAFICA_H_
#define SRC_VISTA_VENTANAGRAFICA_H_

#include <SDL2/SDL.h>
#include <string>
#include <map>
#include "Sprite.h"
#include "EscenarioGrafico.h"
#include "Posicionable.h"
#include "LimitesLogicos.h"

using namespace std;

class VentanaGrafica: public Posicionable{
private:
	SDL_Window* vWindow;
	SDL_Renderer* vRenderer;
	EscenarioGrafico* escenario;

	// SINGLETON
	VentanaGrafica();
	static VentanaGrafica* instancia_unica;

public:
	virtual ~VentanaGrafica();
	bool init(string titulo, int xpos, int ypos, int height, int width, bool fullscreen, EscenarioGrafico* unEscenario);
	SDL_Renderer* getRenderer();
	void dibujarTodo();
	void cerrar();
	void actualizar();
	LimitesLogicos getLimitesLogicos();
	static VentanaGrafica* Instance();
};

#endif /* SRC_VISTA_VENTANAGRAFICA_H_ */
