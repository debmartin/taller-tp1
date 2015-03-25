
#ifndef SRC_VISTA_SPRITE_H_
#define SRC_VISTA_SPRITE_H_
#include <SDL2/SDL.h>
#include "../../src/modelo/Vector2.h";
#include <string>

using namespace std;

class Sprite {

private:
	string id_textura;
	Vector2 posicion;
	int anchoPx;
	int altoPx;
	int anchoFotogramaPx;
	int fotogramaActual;

public:
	Sprite(string id_textura, Vector2 posicionInicial, int anchoFotogramaPx);
	virtual ~Sprite();

	void dibujar();
	void setPosicion(Vector2 p);
	void setFlip(SDL_RendererFlip f);
	void avanzarFotograma();

protected:
	SDL_Rect* getAreaDibujable();

};

#endif /* SRC_VISTA_SPRITE_H_ */
