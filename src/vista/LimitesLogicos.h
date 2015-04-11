/*
 * LimitesLogicos.h
 *
 *  Created on: 3/4/2015
 *      Author: val
 */

#ifndef SRC_VISTA_LIMITESLOGICOS_H_
#define SRC_VISTA_LIMITESLOGICOS_H_

class LimitesLogicos{
private:
	double ancho_logico;
	double alto_logico;
	double y_piso_logico;

public:
	LimitesLogicos(double ando, double alto,double y_piso);
	double getAnchoLogico();
	double getAltoLogico();
	double getYPisoLogico();

	//TODO: Val. Definir si un personaje esta fuera de rango.
	~LimitesLogicos();
};

#endif /* SRC_VISTA_LIMITESLOGICOS_H_ */
