
#ifndef SRC_VISTA_SPRITE_H_
#define SRC_VISTA_SPRITE_H_
#include <SDL2/SDL.h>
#include "../../src/modelo/Vector2.h"
#include <string>

using namespace std;

class Sprite {

private:
	string id_textura;
	Vector2 posicion;
	int anchoPx;
	int altoPx;
	float factorEscalaX;
	float factorEscalaY;
	int cantidadFotogramas;
	int anchoFotogramaPx;
	int fotogramaActual;
	int zIndex;
	SDL_RendererFlip flip;

public:
	Sprite(string id_textura, Vector2 posicionInicial, int cantidadFotogramas, int zIndex, int fps);
	virtual ~Sprite();

	void setSentidoReproduccion(int sentido);
	void setPosicion(Vector2 p);
	void setFlip(SDL_RendererFlip f);
	void avanzarFotograma();
	void escalar(float factor_x, float factor_y);
	void escalar(int anchoNuevoPx, int altoNuevoPx);
	void setFotogramaActual(int nroFotograma);
	void setZindex(int z_index);
	void dibujar();

};

#endif /* SRC_VISTA_SPRITE_H_ */
