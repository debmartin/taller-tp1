/*
 * EfectoSangre.h
 *
 *  Created on: 19/6/2015
 *      Author: val
 */

#ifndef SRC_VISTA_EFECTOSANGRE_H_
#define SRC_VISTA_EFECTOSANGRE_H_

#include "Efecto.h"
#include "Animacion.h"
#include "Renderizador.h"
#include "VentanaGrafica.h"

#define PATH_EFECTO_SANGRE "RECURSOS/EFECTOS/SANGRE/sangre-golpe.png"
#define TIEMPO_VISIBLE_SANGRE 25
#define CANT_FOTOGRAMAS_EFECTO_SANGRE 8
#define FPS_EFECTO_SANGRE 20
#define ID_EFECTO_SANGRE "sangre"
#define PATH_EFECTO_EXPLOSION_SANGRE "RECURSOS/EFECTOS/SANGRE/explosion-sangre.png"
#define CANT_FOTOGRAMAS_EFECTO_EXPLOSION_SANGRE 13
#define FPS_EFECTO_EXPLOSION_SANGRE 20
#define ID_EFECTO_EXPLOSION_SANGRE "explosion-sangre"
#define TIEMPO_VISIBLE_EXPLOSION_SANGRE 50

class EfectoSangre: public Efecto {
private:
	Vector2f posicion;
	Animacion* animacionEfecto;
	Sprite* spriteEfecto;
	bool visible;
	int tiempoVisible;
	int tiempo;
	DireccionObjeto direccionEfecto;
public:
	EfectoSangre(Vector2f pos, string path, int cant_fotograma, int fps, string id, int tiempo_visible);
	virtual ~EfectoSangre();
	void dibujar();
	void update();
	void posicionar(Vector2f posicion);
	Vector2f obtenerPosicionEnVentana();
	void ejecutarEfecto(Vector2f pos, DireccionObjeto direccion);
};

#endif /* SRC_VISTA_EFECTOSANGRE_H_ */
