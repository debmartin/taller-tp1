#include "src/Juego.h"
#include "test/Test.h"

#include "src/vista/VentanaGrafica.h"
#include "src/vista/EscenarioGrafico.h"
#include "src/vista/Capa.h"
#include <SDL2/SDL.h>

#define TITULO_VENTANA "Taller de programacion TP: Mortal Kombat"
#define XPOS_VENTANA_INICIO 100
#define YPOS_VENTANA_INICIO 100
#define ALTO_VENTANA_INICIO 480
#define ANCHO_VENTANA_INICIO 640
#define INICIAR_FULLSCREEN false
#define ANCHO_ESCENARIO 3000

#define IMAGEN_FONDO "../taller-tp1/imagenes/screen-pit.png"
#define IMAGEN_ZUBZERO_CAMINANDO "../taller-tp1/imagenes/zubzero-caminando.png"
#define IMAGEN_ZUBZERO_QUIETO "../taller-tp1/imagenes/zubzero-quieto.png"

#define ID_FONDO "screen-pit"
#define ID_ZUBZERO_CAMINANDO "zubzero-caminando"
#define ID_ZUBZERO_QUIETO "zubzero-quieto"

int main(int argc, char* args[])
{
	static const int FPS = 60;
	static const int DELAY_TIME = 1000.0f / FPS;

	Uint32 frameStart, frameTime;

	//para correr las pruebas comentar o descomentar estas 2 lineas
//	Test tests;
//	tests.ejecutar();


    bool exito = VentanaGrafica::Instance()->init(TITULO_VENTANA, \
    XPOS_VENTANA_INICIO, YPOS_VENTANA_INICIO, ALTO_VENTANA_INICIO, \
    ANCHO_VENTANA_INICIO, INICIAR_FULLSCREEN);

    if (! exito)
		cout << "Error al inicializar juego" << endl;

    Animacion fondoAnim(IMAGEN_FONDO, 1, 1, ID_FONDO, VentanaGrafica::Instance()->getRenderer());
    Animacion zubCaminando(IMAGEN_ZUBZERO_CAMINANDO, 9, 10, ID_ZUBZERO_CAMINANDO, VentanaGrafica::Instance()->getRenderer());
    Animacion zubQuieto(IMAGEN_ZUBZERO_QUIETO, 12, 10,  ID_ZUBZERO_QUIETO, VentanaGrafica::Instance()->getRenderer());

    Capa fondoCapa(&fondoAnim, 640);
    std::pair<double,double> posInicialPersonaje(100, 195);
    PersonajeDibujable personaje(posInicialPersonaje, &zubQuieto);
    personaje.agregarAnimacion(&zubQuieto);
    personaje.agregarAnimacion(&zubCaminando);

    list<Dibujable*> capasYPersonajes;
    capasYPersonajes.push_back((Dibujable*) &fondoCapa);
    capasYPersonajes.push_back((Dibujable*) &personaje);

    EscenarioGrafico* escenario = new EscenarioGrafico(ANCHO_ESCENARIO, ALTO_VENTANA_INICIO, &capasYPersonajes);
	Juego g_game(VentanaGrafica::Instance());

	//levantar la información inicial mediante json
	//... usar libreria jsonCpp


	while (g_game.running())
	{
		frameStart = SDL_GetTicks();

		g_game.handleEvents();
		g_game.update();
		g_game.render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < DELAY_TIME)
			SDL_Delay((int)(DELAY_TIME - frameTime));
	}

	g_game.clean();

	return 0;
}
