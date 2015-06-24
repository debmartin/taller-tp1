#ifndef SRC_VISTA_HUD_H_
#define SRC_VISTA_HUD_H_

#include <map>
#include <string>
#include <deque>
#include <SDL2/SDL.h>
#include "BarraEnergia.h"
#include "../../modelo/Observador.h"
#include "../../modelo/Personaje.h"
#include "../../modelo/Vector2f.h"
#include "../../vista/Sprite.h"
#include "../../vista/Animacion.h"
#include "../../controlador/ColaEventos.h"

//#include "../../controlador/ControladorJoystick.h"

#define POSICION_PORCENTUAL_BARRA1 Vector2f(10, 10)
#define POSICION_PORCENTUAL_BARRA2 Vector2f(60, 10)
#define DIMENSION_PORCENTUAL_BARRA Vector2f(30, 10)

#define TIEMPO_LIMITE_MOSTRAR_NOMBRE_COMBO 1000
#define TIEMPO_INICIAL_RELOJ_SEGUNDOS 11

class HUD: public Observador {
public:
	void disminuirEnergia1(float offset);
	void disminuirEnergia2(float offset);
	void setEnergia1(float nuevaEnergia);
	void setEnergia2(float nuevaEnergia);
	SDL_Texture* updateTexture();
	void recibirNotificacion(Observable* unObservable);
	void dibujar();
	SDL_Texture* renderText(
			std::string mensaje,
			std::string pathFuente,
			SDL_Color 		   color,
			int 			   tamanioFuentePx,
			SDL_Renderer*      renderer);

	void mostrarMensajeCombo(string nombreCombo);


	//RELOJ
	void arrancarReloj();
	void pausarReloj();
	bool seAcaboElTiempo();
	void resetReloj();
	void playReloj();


	//SINGLETON
	static HUD* Instance();
	bool init(
			SDL_Window* gWindow,
			string nombre_personaje1,
			string nombre_personaje2,
			ColaEventos* colaDeTeclas1,
			bool combosVisibles = true
		);
	virtual ~HUD();

	// MOSTRAR NOMBRE COMBO EN PANTALLA
	void update();

private:
	SDL_Texture*  crearTexturaTransparente(int ancho, int alto);
	SDL_Window*   gWindow;
	SDL_Renderer* gRenderer;
	BarraEnergia* barraDeEnergia1;
	BarraEnergia* barraDeEnergia2;
	SDL_Texture*  tHUD;

	ColaEventos* colaDeTeclas;

	map<string, Sprite*>* mBotones;
	map<string, Animacion*>* mAnimaciones;

	Animacion* aFondoBoton;
	Sprite* sFondoBoton;

	Animacion* aCaja;
	Sprite* sCaja;
	bool combosVisibles;

	Uint32 W(SDL_Texture* t);
	Uint32 H(SDL_Texture* t);

	// SINGLETON
	HUD();
	static HUD* instancia_unica;

	// MOSTRAR NOMBRE COMBO EN PANTALLA
	string nombreComboActual;
	bool mostrandoNombreCombo;
	Uint32 tiempoInicioMostrar;

	// RELOJ
	bool relojFuncionando;
	Uint32 tiempoTranscurrido;
	Uint32 tiempoInicial;
	Uint32 tiempoMostrado;
};

#endif /* SRC_VISTA_HUD_H_ */
