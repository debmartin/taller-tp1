/*
 * Escenario.h
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_ESCENARIO_H_
#define SRC_MODELO_ESCENARIO_H_

class Escenario {
private:
	float ancho;
	float alto;
	int ypiso;
	//string fondo;

public:
	Escenario();
	virtual ~Escenario();
	float getAlto() const;
	void setAlto(float alto);
	float getAncho() const;
	void setAncho(float ancho);
	int getYpiso() const;
	void setYpiso(int ypiso);
};

#endif /* SRC_MODELO_ESCENARIO_H_ */
