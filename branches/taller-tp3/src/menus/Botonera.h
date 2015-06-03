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
	Posicion* posicionEnfocadaDelJugador1;
	Posicion* posicionEnfocadaDelJugador2;
	string IdContenidoElegido_paraJugador1;
	string IdContenidoElegido_paraJugador2;
	bool salirMenu_jugador1;
	bool salirMenu_jugador2;
	string tipo;
public:
	Botonera();
	Botonera(string tipo, int cant_filas, int cant_columnas, Posicion* posicion);
	bool loadMedia(string path_imagen);
	virtual ~Botonera();
	void manejarEventoJugador1( SDL_Event evento );
	void manejarEventoJugador2( SDL_Event evento );
	void actualizarModelo(bool* salirMenu);
	void dibujar();

	int getCantColumnas();
	int getCantFilas();

	void setPosicionEnfocadaDelJugador1(Posicion* posicionEnfocadaDelJugador1);
	void setPosicionEnfocadaDelJugador2(Posicion* posicionEnfocadaDelJugador2);

	string getIdContenidoElegidoParaJugador1();
	string getIdContenidoElegidoParaJugador2();

private:
	void elegirIdContenidoParaJugador1(string idContenido);
	void elegirIdContenidoParaJugador2(string idContenido);
};

#endif /* SRC_BOTONERA_H_ */
