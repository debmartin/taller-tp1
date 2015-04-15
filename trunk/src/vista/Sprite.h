
#ifndef SRC_VISTA_SPRITE_H_
#define SRC_VISTA_SPRITE_H_
#include <SDL2/SDL.h>
#include "../../src/modelo/Vector2f.h"
#include <string>
#include "../modelo/Trayectoria.h"
#include "../modelo/Reposo.h"
#include "Animacion.h"

typedef enum SentidoReproduccion
{
    HACIA_ADELANTE,
    HACIA_ATRAS
} SentidoReproduccion;

typedef enum OrientacionSprite
{
    ORIENTACION_DERECHA,
	ORIENTACION_IZQUIERDA
} OrientacionSprite;

class Sprite {

public:

private:
	Animacion* animacionAct;
	Vector2f posicion;
	int anchoPx;
	int altoPx;
	float factorEscalaX;
	float factorEscalaY;
	int anchoFotogramaPx;
	int fotogramaActual;
//	float zIndex;
	int fps;
	SDL_RendererFlip flip;
	SentidoReproduccion sentidoReproduccion;
	float tCreacion;

public:
	Sprite(Animacion* animInicial, Vector2f& posicion, OrientacionSprite orientacion);
	virtual ~Sprite();

	void setPosicion(Vector2f& posicion);
	void desplazar(Vector2f& posicion);
	void setFlip(SDL_RendererFlip f); //OK
	//void avanzarFotograma();
	void escalarConFactor(Vector2f& factor); //OK
	void escalarConTamanio(int anchoNuevoPx, int altoNuevoPx); //OK
	void setFotogramaActual(int nroFotograma);
	void setSentidoReproduccion(SentidoReproduccion sr);
	void dibujar(); // OK
	void update();
	void cambiarAnimacion(Animacion* nuevaAnim);
	Vector2f getPosicion();
	int getAnchoPx();
	int getAltoPx();
};

#endif /* SRC_VISTA_SPRITE_H_ */
