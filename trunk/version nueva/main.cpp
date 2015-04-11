#include "src/Juego.h"
//#include "test/Test.h"

#include "src/vista/VentanaGrafica.h"
#include "src/vista/EscenarioGrafico.h"
#include "src/vista/Capa.h"
#include "src/modelo/Personaje.h"
#include <SDL2/SDL.h>

#define TITULO_VENTANA "Taller de programacion TP: Mortal Kombat"
#define POS_VENTANA_INICIO Vector2f(100, 100)
#define ALTO_PX_VENTANA_INICIO 480
#define ANCHO_PX_VENTANA_INICIO 640
#define ANCHO_LOGICO_VENTANA_INICIO 640
#define INICIAR_FULLSCREEN false
#define ANCHO_ESCENARIO 1500
#define ALTO_ESCENARIO 600
#define Y_PISO 40
#define ANCHO_LOGICO_CAPA1	600
#define ANCHO_LOGICO_CAPA2	1000

#define IMAGEN_FONDO1 "Goro1.jpg"
#define IMAGEN_FONDO2 "Goro2.jpg"
//#define IMAGEN_FONDO2 "mario.jpg"
//#define IMAGEN_FONDO "Pit2.png"
//#define IMAGEN_FONDO "Pit.jpg"
//#define IMAGEN_FONDO "escenario2.gif"
//#define IMAGEN_FONDO "screen-pit.png"
#define IMAGEN_ZUBZERO_CAMINANDO "zubzero-caminando.png"
#define IMAGEN_ZUBZERO_QUIETO "zubzero-quieto.png"

#define CANT_FOTOGRAMAS_FONDO 1
#define CANT_FOTOGRAMAS_FONDO2 1
#define CANT_FOTOGRAMAS_ZUBQUIETO 12
#define CANT_FOTOGRAMAS_ZUBCAMINANDO 9

#define FPS_FONDO 1
#define FPS_FONDO2 1
#define FPS_ZUBQUIETO 10
#define FPS_ZUBCAMINANDO 10
//#define IMAGEN_FONDO "../version nueva/imagenes/screen-pit.png"
//#define IMAGEN_ZUBZERO_CAMINANDO "../version nueva/imagenes/zubzero-caminando.png"
//#define IMAGEN_ZUBZERO_QUIETO "../version nueva/imagenes/zubzero-quieto.png"

#define POSICION_INICIAL_CAPA Vector2f(0, 0)
#define POSICION_INICIAL_PERSONAJE Vector2f(100, 195)
#define FACTOR_ESCALA_PERSONAJE Vector2f(2.0f, 2.0f)

#define ANCHO_PERSONAJE 20
#define ALTO_PERSONAJE 35
#define ANCHO_PERSONAJE_SPRITES 20

int main(int argc, char* args[])
{
	static const int FPS = 60;
	static const int DELAY_TIME = 1000.0f / FPS;

	Uint32 frameStart, frameTime;

	//para correr las pruebas comentar o descomentar estas 2 lineas
//	Test tests;
//	tests.ejecutar();
    Vector2f tamanioVentanaPx(ANCHO_PX_VENTANA_INICIO, ALTO_PX_VENTANA_INICIO);
    Vector2f tamanioVentanaLogico(ANCHO_LOGICO_VENTANA_INICIO, ALTO_ESCENARIO);
    bool exito = VentanaGrafica::Instance()->init(TITULO_VENTANA, POS_VENTANA_INICIO, tamanioVentanaPx, tamanioVentanaLogico, INICIAR_FULLSCREEN);

    if (! exito)
		cout << "Error al inicializar juego" << endl;

	Animacion fondoAnim(IMAGEN_FONDO1, CANT_FOTOGRAMAS_FONDO, FPS_FONDO, ID_FONDO, Renderizador::Instance()->getRenderer());
	Animacion fondoAnim2(IMAGEN_FONDO2, CANT_FOTOGRAMAS_FONDO2, FPS_FONDO2, ID_FONDO, Renderizador::Instance()->getRenderer());

	Animacion zubQuieto(IMAGEN_ZUBZERO_QUIETO, CANT_FOTOGRAMAS_ZUBQUIETO, FPS_ZUBQUIETO,  ID_ZUBZERO_QUIETO, Renderizador::Instance()->getRenderer());
	Animacion zubCaminando(IMAGEN_ZUBZERO_CAMINANDO, CANT_FOTOGRAMAS_ZUBCAMINANDO, FPS_ZUBCAMINANDO, ID_ZUBZERO_CAMINANDO, Renderizador::Instance()->getRenderer());

	Vector2f tamIniCapa(ANCHO_LOGICO_CAPA1, ALTO_ESCENARIO);
	Vector2f tamIniCapa2(ANCHO_LOGICO_CAPA2, ALTO_ESCENARIO);
    Vector2f posInCapa = POSICION_INICIAL_CAPA;

    Vector2f relacionAspectos = VentanaGrafica::Instance()->obtener_relacion_aspectos();
	Capa fondoCapa(&fondoAnim, tamIniCapa, posInCapa, relacionAspectos);
	Capa fondoCapa2(&fondoAnim2, tamIniCapa2, posInCapa, relacionAspectos);

	Personaje jugador(ANCHO_PERSONAJE, ALTO_PERSONAJE, ANCHO_PERSONAJE_SPRITES, POSICION_INICIAL_PERSONAJE, VentanaGrafica::Instance());

	PersonajeDibujable personaje(&zubQuieto, POSICION_INICIAL_PERSONAJE, FACTOR_ESCALA_PERSONAJE, &jugador);
	personaje.agregarAnimacion(&zubQuieto);
	personaje.agregarAnimacion(&zubCaminando);

	list<Capa*> capas;
	capas.push_back(&fondoCapa);
	capas.push_back(&fondoCapa2);

	list<Dibujable*> capasYPersonajes;
	capasYPersonajes.push_back((Dibujable*) &fondoCapa);
	capasYPersonajes.push_back((Dibujable*) &fondoCapa2);
	capasYPersonajes.push_back((Dibujable*) &personaje);



	EscenarioGrafico escenario(ANCHO_ESCENARIO, ALTO_ESCENARIO, Y_PISO, &capasYPersonajes, &capas);
    VentanaGrafica::Instance()->agregarEscenario(&escenario);
    VentanaGrafica::Instance()->centrar_ventana();
    escenario.centrar_capas();

    cout << "carga correcta" << endl;
	Juego g_game(VentanaGrafica::Instance(), &escenario, &jugador, &personaje);


	//levantar la información inicial mediante json
	//... usar libreria jsonCpp
    cout << "creacion juego correcta" << endl;


	while (g_game.running())
	{

		frameStart = SDL_GetTicks();

		g_game.handleEvents();

		g_game.update();
	    //cout << "game running" << endl;

		g_game.render();
	    //cout << "game running2" << endl;

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < DELAY_TIME)
			SDL_Delay((int)(DELAY_TIME - frameTime));
	}

	return 0;
}
