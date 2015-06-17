#ifndef SRC_VISTA_SPRITE_H_
#define SRC_VISTA_SPRITE_H_

#define FACTOR_ESCALA_INICIAL Vector2f(1.0f, .10f)
#define FOTOGRAMA_INICIAL 1

#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>
#include <cmath>
#include "../modelo/Vector2f.h"
#include "Animacion.h"


typedef enum LoopMode {
    LOOP_MOD,
    LOOP_REPEAT,
	LOOP_NO_REPEAT
} LoopMode;

typedef enum UbicacionPivote {
	SPR_ARRIBA_IZQUIERDA,
	SPR_ARRIBA_CENTRO,
	SPR_ABAJO_IZQUIERDA,
	SPR_ABAJO_CENTRO
} UbicacionPivote;

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
	SDL_Renderer* pRenderer;
	Vector2f posicion;
	OrientacionSprite orientacion;
	UbicacionPivote ubicacionDibujado;
	Vector2f factorEscala;

	// PERTENECIENTE A LA ANIMACION
	Vector2f dimensionesImagen;
	int anchoFotogramaPx;
	int fotogramaActual;
	int fps;
	SentidoReproduccion sentidoReproduccion;
	// LOOP
	LoopMode loopMode;
	float tInicial;

public:
	Sprite(
		Animacion* animInicial,
		SDL_Renderer* pRenderer,
		Vector2f posicion,
		OrientacionSprite orientacion = ORIENTACION_DERECHA,
		UbicacionPivote ubicacion = SPR_ARRIBA_IZQUIERDA);

	virtual ~Sprite();

	void setPosicion(Vector2f& posicion);
	void desplazar(Vector2f& posicion);
	void setOrientacion(OrientacionSprite o);
	void escalarConFactor(Vector2f factor);
	void escalarConTamanio(int anchoNuevoPx, int altoNuevoPx);
	void escalarConTamanio(Vector2f nuevoTamanioPx);
	void setFotogramaActual(int nroFotograma);
	void setSentidoReproduccion(SentidoReproduccion sr);
	void dibujar();
	void update();
	void cambiarAnimacion(Animacion* nuevaAnim);
	Vector2f getPosicion();
	int getAnchoPx();
	int getAltoPx();
	Vector2f getDimensionesPx();
	void cambiarOrientacionHaciaDerecha();
	void cambiarOrientacionHaciaIzquierda();
	void setLoopMode(LoopMode loopMode);

	friend ostream& operator<<(ostream &o, const Sprite &s);
	string toString();
};

#endif /* SRC_VISTA_SPRITE_H_ */

