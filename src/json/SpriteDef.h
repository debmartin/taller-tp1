/*
 * SpriteDef.h
 *
 *  Created on: 14/4/2015
 *      Author: ariel
 */

#ifndef SRC_JSON_SPRITEDEF_H_
#define SRC_JSON_SPRITEDEF_H_

#include <iostream>
#include <string>

using namespace std;


class SpriteDef {
private:
	string imagen;
	double ancho;
	int cant_fotogramas;
	int fps;
public:
	SpriteDef();
	SpriteDef(string imagen, double ancho, int cant_fotogramas, int fps);
	virtual ~SpriteDef();
	double getAncho() const;
	int getCantFotogramas() const;
	int getFps() const;
	const string& getImagen() const;
	friend ostream& operator<<(ostream &o, const SpriteDef &s);
};

#endif /* SRC_JSON_SPRITEDEF_H_ */
