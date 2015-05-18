/*
 * Objeto.h
 *
 *  Created on: 28/4/2015
 *      Author: val
 */

#ifndef SRC_MODELO_OBJETO_H_
#define SRC_MODELO_OBJETO_H_


#include "Trayectoria.h"

#define POS_INICIAL_OBJETO Vector2f(0,0)
#define VELOCIDAD_OBJETO Vector2f(10,10)

typedef enum estado_objeto
{
	VISIBLE,
	NO_VISIBLE,
} estado_objeto;

typedef enum direccion_objeto
{
	DIRECCION_DERECHA,
	DIRECCION_IZQUIERDA,
} direccion_objeto;

class Objeto {
public:
	Objeto();
	Objeto(Vector2f posicion);
	virtual ~Objeto();
	virtual void posicionar(Vector2f posicion) = 0;
	virtual int quitarEnergia() = 0;
	virtual void update() = 0;
	virtual void arrojar() = 0;
	virtual void cambiarEstado(estado_objeto unEstado) = 0;
	virtual void definirDireccionInicial(direccion_objeto dir) = 0;
	virtual void cambiarDireccion() = 0;
	virtual void cambiarTrayectoria(Trayectoria* trayectoria) = 0;
};

#endif /* SRC_MODELO_OBJETO_H_ */
