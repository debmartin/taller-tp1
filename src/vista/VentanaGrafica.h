#ifndef SRC_VISTA_VENTANAGRAFICA_H_
#define SRC_VISTA_VENTANAGRAFICA_H_

#include <SDL2/SDL.h>
#include <string>
#include "Sprite.h"

using namespace std;

class VentanaGrafica {
private:
	//SRL_Renderer* vRenderer;
	SDL_Window* vWindow;

	// SINGLETON
	VentanaGrafica();
	static VentanaGrafica* instancia_unica;

public:
	virtual ~VentanaGrafica();
	void init(string titulo, SDL_Rect disposicion, bool fullscreen);
	SDL_Renderer* getRenderer();
	void agregarSprite(Sprite* unSprite, string s);
	void quitarSprite(string id);
	void cambiarSprite(string id, Sprite* nuevoSprite);
	void getSprite(string id);
	void dibujarTodo();

	static VentanaGrafica* Instance();
};

#endif /* SRC_VISTA_VENTANAGRAFICA_H_ */
