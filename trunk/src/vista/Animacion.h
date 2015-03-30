#ifndef SRC_VISTA_ANIMACION_H_
#define SRC_VISTA_ANIMACION_H_
#include <SDL2/SDL.h>

class Animacion {

private:
	SDL_Texture* textura;
	int cantidadFotogramas;
	int fps;
public:
	Animacion(SDL_Texture* textura, int cantidadFotogramas, int fps);
	SDL_Texture* getTextura();
	int getCantidadFotogramas();
	int getFps();

	virtual ~Animacion();
};

#endif /* SRC_VISTA_ANIMACION_H_ */
