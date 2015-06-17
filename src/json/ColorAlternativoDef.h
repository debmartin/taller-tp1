/*
 * ColorAlternativoDef.h
 *
 *  Created on: 30/4/2015
 *      Author: ariel
 */

#ifndef SRC_JSON_COLORALTERNATIVODEF_H_
#define SRC_JSON_COLORALTERNATIVODEF_H_

#include <iostream>
#include <string>

#include "../utils/Loggeable.h"

class ColorAlternativoDef: public Loggeable{
private:
	double hinicial;
	double hfinal;
	double desplazamiento;
public:
	ColorAlternativoDef();
	ColorAlternativoDef(double hinicial, double hfinal, double desplazamiento);

	void setHinicial(double hinicial);
	void setHfinal(double hfinal);
	void setDesplazamiento(double desplazamiento);

	double getHinicial() const;
	double getHfinal() const;
	double getDesplazamiento() const;

	virtual ~ColorAlternativoDef();
	friend ostream& operator<<(ostream &o, const ColorAlternativoDef &c);
	string toString();
};

#endif /* SRC_JSON_COLORALTERNATIVODEF_H_ */
