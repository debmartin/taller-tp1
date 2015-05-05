#ifndef SRC_VISTA_HUD_H_
#define SRC_VISTA_HUD_H_

#include <string>
#include <SDL2/SDL.h>
#include "../../modelo/Vector2f.h"
#include "BarraEnergia.h"
#include "../../modelo/Observador.h"
#include "../../modelo/Personaje.h"

#define POSICION_PORCENTUAL_BARRA1 Vector2f(10, 10)
#define POSICION_PORCENTUAL_BARRA2 Vector2f(60, 10)
#define DIMENSION_PORCENTUAL_BARRA Vector2f(30, 10)

class HUD: public Observador {
public:
	HUD() {};
	HUD(SDL_Window* gWindow, string nombre_personaje1, string nombre_personaje2);
	void disminuirEnergia1(float offset);
	void disminuirEnergia2(float offset);
	void setEnergia1(float nuevaEnergia);
	void setEnergia2(float nuevaEnergia);
	SDL_Texture* updateTexture();
	void recibirNotificacion(Observable* unObservable);
	void dibujar();
	virtual ~HUD();

private:
	SDL_Texture*  crearTexturaTransparente(int ancho, int alto);
	SDL_Window*   gWindow;
	SDL_Renderer* gRenderer;
	BarraEnergia* barraDeEnergia1;
	BarraEnergia* barraDeEnergia2;
	SDL_Texture*  tHUD;
};

#endif /* SRC_VISTA_HUD_H_ */
