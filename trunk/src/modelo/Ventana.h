/*
 * Ventana.h
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_VENTANA_H_
#define SRC_MODELO_VENTANA_H_

class Ventana {
private:
	int ancho_px;
	int alto_px;
	float ancho;
public:
	Ventana();
	virtual ~Ventana();
	int getAltoPx() const;
	void setAltoPx(int altoPx);
	float getAncho() const;
	void setAncho(float ancho);
	int getAnchoPx() const;
	void setAnchoPx(int anchoPx);
};

#endif /* SRC_MODELO_VENTANA_H_ */
