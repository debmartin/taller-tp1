#include <SDL2/SDL.h>
#include "../../src/modelo/Vector2.h";

#ifndef SRC_VISTA_SPRITE_H_
#define SRC_VISTA_SPRITE_H_

class Sprite {

private:
	Vector2 posicion;
	int anchoPx;
	int altoPx;

public:
	Sprite();
	virtual ~Sprite();

	void dibujar();
	void setPosicion(Vector2 p);
	void setFlip(SDL_RendererFlip f);
	virtual void avanzarFotograma() = 0;

protected:
	virtual SDL_Rect getAreaDibujable() = 0;

};

#endif /* SRC_VISTA_SPRITE_H_ */
