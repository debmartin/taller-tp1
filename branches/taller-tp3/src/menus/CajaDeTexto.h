/*
 * CajaDeTexto.h
 *
 *  Created on: 10/6/2015
 *      Author: ariel
 */

#ifndef CAJADETEXTO_H_
#define CAJADETEXTO_H_

#include <SDL2/SDL_pixels.h>
#include <string>

struct SDL_Renderer;

class Textura;

struct SDL_Color;
union SDL_Event;

using namespace std;

class CajaDeTexto {
private:
	int cant_caracteres;
	int pos_x;
	int pos_y;
	int ancho;
	int alto;
	Textura* textura;
	SDL_Color textColor;
	bool enfocado;
	string texto;
public:
	CajaDeTexto(int cant_caracteres, int pos_x, int pos_y);
	virtual ~CajaDeTexto();
	bool manejarEvento(SDL_Event e);
	void dibujar(bool renderText);
	bool loadMedia();
	string getTexto() const;
	bool estoyEnfocado();
	void setTexto(string texto);
};

#endif /* CAJADETEXTO_H_ */
