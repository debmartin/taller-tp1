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

#include "../utils/Loggeable.h"
#include "CajaDef.h"
#include <list>

#define IMAGEN_DEFAULT "img/sprites_defecto.png"
#define CANT_FOTOGRAMAS_DEFAULT 1
#define FPS_DEFAULT 10

using namespace std;


class SpriteDef: public Loggeable {
private:
	string imagen;
	string id_sprite;
	int cant_fotogramas;
	int fps;

public:
	SpriteDef();
	SpriteDef(string imagen, string id, int cant_fotogramas, int fps);
	virtual ~SpriteDef();
	int getCantFotogramas() const;
	int getFps() const;
	void setCantFotogramas(int nuevaCant);
	void setFps(int nuevoFps);
	void setImagen(string nuevaImagen);
	const string& getImagen() const;
	const string& getIdSprite() const;
	friend ostream& operator<<(ostream &o, const SpriteDef &s);
	string toString();
};

#endif /* SRC_JSON_SPRITEDEF_H_ */
