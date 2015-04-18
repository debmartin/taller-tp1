
#ifndef SRC_VISTA_SPRITE_H_
#define SRC_VISTA_SPRITE_H_
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <math.h>
#include "../utils/Logger.h"
#include "../modelo/Vector2f.h"
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
	int fps;
	OrientacionSprite orientacion;
	SentidoReproduccion sentidoReproduccion;

public:
	Sprite(Animacion* animInicial, Vector2f& posicion, OrientacionSprite orientacion);
	virtual ~Sprite();

	void setPosicion(Vector2f& posicion);
	void desplazar(Vector2f& posicion);
	void setOrientacion(OrientacionSprite o);
	void escalarConFactor(Vector2f& factor);
	void escalarConTamanio(int anchoNuevoPx, int altoNuevoPx);
	void setFotogramaActual(int nroFotograma);
	void setSentidoReproduccion(SentidoReproduccion sr);
	void dibujar();
	void update();
	void cambiarAnimacion(Animacion* nuevaAnim);
	Vector2f getPosicion();
	int getAnchoPx();
	int getAltoPx();
};

#endif /* SRC_VISTA_SPRITE_H_ */
