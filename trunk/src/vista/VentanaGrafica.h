#ifndef SRC_VISTA_VENTANAGRAFICA_H_
#define SRC_VISTA_VENTANAGRAFICA_H_

#include <SDL2/SDL.h>
#include <string>
#include <map>
#include "Sprite.h"

using namespace std;

class VentanaGrafica {
private:
	SDL_Window* vWindow;
	SDL_Renderer* vRenderer;
	map<string, Sprite*> mapaSprites;

	// SINGLETON
	VentanaGrafica();
	static VentanaGrafica* instancia_unica;

public:
	virtual ~VentanaGrafica();
	bool init(string titulo, int xpos, int ypos, int height, int width, bool fullscreen);
	SDL_Renderer* getRenderer();
	void setSprite(Sprite* unSprite, string nombre);
	void quitarSprite(string id);
	void cambiarSprite(string id, Sprite* nuevoSprite);
	Sprite* getSprite(string id);
	void dibujarTodo();
	void cerrar();
	void update();
	static VentanaGrafica* Instance();
};

#endif /* SRC_VISTA_VENTANAGRAFICA_H_ */
