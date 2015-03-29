
#ifndef SRC_VISTA_SPRITE_H_
#define SRC_VISTA_SPRITE_H_
#include <SDL2/SDL.h>
#include "../../src/modelo/Vector2.h"
#include <string>
#include "Trayectoria.h"
#include "Reposo.h"

typedef enum
{
    HACIA_ADELANTE,
    HACIA_ATRAS
} SentidoReproduccion;


using namespace std;

class Sprite {

public:

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
	float zIndex;
	int fps;
	SDL_RendererFlip flip;
	SentidoReproduccion sentidoReproduccion;
	Trayectoria* trayectoria;
	float tCreacion;

public:
	Sprite(string id_textura, Vector2 posicionInicial, int cantidadFotogramas, int zIndex, int fps);
	virtual ~Sprite();

	void setPosicion(Vector2 p);
	void desplazar(Vector2 p);
	void setFlip(SDL_RendererFlip f); //OK
	//void avanzarFotograma();
	void escalarConFactor(float factor_x, float factor_y); //OK
	void escalarConTamanio(int anchoNuevoPx, int altoNuevoPx); //OK
	void setFotogramaActual(int nroFotograma);
	void setSentidoReproduccion(SentidoReproduccion sr);
	void setZindex(float z_index);
	float getZindex() { return zIndex; }
	void dibujar(); // OK
	void update();
	void setTrayectoria(Trayectoria* t);
	Vector2 getPosicion() { return this->posicion; };
};

#endif /* SRC_VISTA_SPRITE_H_ */
