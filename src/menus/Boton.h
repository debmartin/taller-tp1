/*
 * Boton.h
 *
 *  Created on: 16/5/2015
 *      Author: ariel
 */

#ifndef SRC_BOTON_H_
#define SRC_BOTON_H_

#include <map>

class Posicion;

class Textura;

using namespace std;
#include<iostream>

#include <SDL2/SDL_rect.h>

union SDL_Event;

const int BUTTON_WIDTH = 118.20;
const int BUTTON_HEIGHT = 127;

enum LButtonSprite
{
	BUTTON_SPRITE_OUT = 0,
	BUTTON_SPRITE_OVER_MOTION = 1,
	BUTTON_SPRITE_DOWN = 2,
	BUTTON_SPRITE_TOTAL = 3
};


//The mouse button
class Boton{

private:
	//Top left position
	SDL_Point mPosition;
	//Currently used global sprite
	LButtonSprite mCurrentSprite;
	// poscion en la matriz de la botonera
	Posicion* posicionModelo;
	bool elegido;

public:

	Boton(Posicion* posicionModelo, Posicion* posicionVista);

	//Shows button sprite
	void render(Textura* textura, map<int,SDL_Rect>* gSpriteClips);

	virtual ~Boton();

	friend ostream& operator<<(ostream &o, const Boton &b);
	Posicion* getPosicionModelo() const;
	void elegirSprite();

};

#endif /* SRC_BOTON_H_ */
