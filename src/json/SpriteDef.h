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
};

#endif /* SRC_JSON_SPRITEDEF_H_ */
