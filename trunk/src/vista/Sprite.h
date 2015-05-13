
#ifndef SRC_VISTA_SPRITE_H_
#define SRC_VISTA_SPRITE_H_

#include <iostream>
#include <string>

#include "../modelo/Vector2f.h"

class Animacion;

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

class Sprite: public Loggeable {

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
	UbicacionPivote ubicacionDibujado;

public:
	Sprite(Animacion* animInicial, Vector2f& posicion, OrientacionSprite orientacion, UbicacionPivote ubicacion = SPR_ARRIBA_IZQUIERDA);
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
	Vector2f getDimensionesPx();
	void cambiarOrientacionHaciaDerecha();
	void cambiarOrientacionHaciaIzquierda();

	friend ostream& operator<<(ostream &o, const Sprite &s);
	string toString();
};

#endif /* SRC_VISTA_SPRITE_H_ */
