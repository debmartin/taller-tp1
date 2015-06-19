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

#define PATH_EFECTO_SANGRE "RECURSOS/EFECTOS/SANGRE/sangre25.png"

class EfectoSangre: public Efecto {
private:
	Vector2f posicion;
	Animacion* animacionEfecto;
	Sprite* spriteEfecto;
	bool visible;
	int tiempoVisible;
	DireccionObjeto direccionEfecto;
public:
	EfectoSangre(Vector2f posicion);
	virtual ~EfectoSangre();
	void dibujar();
	void update();
	void posicionar(Vector2f posicion);
	Vector2f obtenerPosicionEnVentana();
	void ejecutarEfecto(Vector2f pos, DireccionObjeto direccion);
};

#endif /* SRC_VISTA_EFECTOSANGRE_H_ */
