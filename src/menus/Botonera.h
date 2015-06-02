/*
 * Botonera.h
 *
 *  Created on: 16/5/2015
 *      Author: ariel
 */

#ifndef SRC_BOTONERA_H_
#define SRC_BOTONERA_H_

#include <SDL2/SDL_rect.h>
#include <map>
#include <string>

class Posicion;

union SDL_Event;


using namespace std;

class Textura;

class Boton;

const int SCREEN_WIDTH 	= 640;
const int SCREEN_HEIGHT = 480;


class Botonera {
private:
	int cant_filas;
	int cant_columnas;
	Textura* gButtonSpriteSheetTexture;
	map<int,SDL_Rect>* map_gSpriteClips;
	Boton*** matriz;
	Posicion* posEnfocado;
	string IdContenidoElegido;
public:
	Botonera();
	Botonera(string tipo, int cant_filas, int cant_columnas, Posicion* posicion, Posicion* posIni_enfocado);
	bool loadMedia(string path_imagen);
	virtual ~Botonera();
	void manejarEvento( SDL_Event evento );
	void actualizarModelo(bool* salirMenu);
	void dibujar();

	int getCantColumnas();
	int getCantFilas();
	string getIdContenidoElegido();
private:
	void elegirIdContenido(string idContenido);
};

#endif /* SRC_BOTONERA_H_ */
