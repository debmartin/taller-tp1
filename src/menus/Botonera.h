/*
 * Botonera.h
 *
 *  Created on: 16/5/2015
 *      Author: ariel
 */

#ifndef SRC_BOTONERA_H_
#define SRC_BOTONERA_H_

#include <string>

class ControladorBotonera;

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
	Textura* gButtonSpriteSheetTexture2;
	Textura* gButtonSpriteSheetTexture3;
	Boton*** matriz;
	Posicion* posicionEnfocadaDelJugador1;
	Posicion* posicionEnfocadaDelJugador2;
	string IdContenidoElegido_paraJugador1;
	string IdContenidoElegido_paraJugador2;
	bool salirMenu_jugador1;
	bool salirMenu_jugador2;
	string tipo;

	string tipoDeControl_jugador1;
	string tipoDeControl_jugador2;
	string modo_juego_elegido;
	ControladorBotonera* controladorBotonera;
public:
	Botonera(string tipo, int cant_filas, int cant_columnas, Posicion* posicion, string tipoDeControl_jugador1, string tipoDeControl_jugador2, string modo_juego_elegido="");
	bool loadMedia(string path_imagen, string path_imagen2, string path_imagen3);
	virtual ~Botonera();
	void manejarEventoJugador( SDL_Event evento );
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