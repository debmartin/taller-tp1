#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <map>
#include <string>
#include <utility>

#include "src/json/JugadorDef.h"
#include "src/Juego.h"
#include "src/modelo/CargadorDeObjetos.h"
#include "src/modelo/Personaje.h"
#include "src/utils/Logger.h"
#include "src/vista/PersonajeDibujable.h"
#include "src/vista/VentanaGrafica.h"
#include "test/Test.h"

Juego* cargarJuego(string escenarioPath){
	Logger::getInstance()->info("#################################################");
	Logger::getInstance()->info("############ INICIA LA CARGA DEL JUEGO ##########");
	Logger::getInstance()->info("#################################################");

	CargadorDeOjbetos cargador_de_objetos(escenarioPath);

	/*
	 * cargo los personajes y personajes dibujables para  los jugadores
	 */
	string nombrePersonaje_delJugador1 = cargador_de_objetos.cargarJugador1()->getIdPersonaje();
	string nombrePersonaje_delJugador2 = cargador_de_objetos.cargarJugador2()->getIdPersonaje();

    map<string, Personaje*>* personajes = cargador_de_objetos.cargarPersonajes();
    map<string, PersonajeDibujable*>* personajesDibujables = cargador_de_objetos.cargarPersonajesDibujables();

	Personaje* personaje_delJugador1;
	Personaje* personaje_delJugador2;
	PersonajeDibujable* personajeDibujable_delJugador1;
	PersonajeDibujable* personajeDibujable_delJugador2;

	if (nombrePersonaje_delJugador1 == nombrePersonaje_delJugador2)
	{

		personaje_delJugador1 			= personajes->find(nombrePersonaje_delJugador1)->second;
		personaje_delJugador2 			= personajes->find(nombrePersonaje_delJugador1)->second;
		personajeDibujable_delJugador1 	= personajesDibujables->find(nombrePersonaje_delJugador1)->second;
		personajeDibujable_delJugador2 	= personajesDibujables->find(nombrePersonaje_delJugador1)->second;

		personajeDibujable_delJugador2->cambiarColor(personajeDibujable_delJugador1->getColorAlternativo());
	}
	else
	{
		personaje_delJugador1 			= personajes->find(nombrePersonaje_delJugador1)->second;
		personaje_delJugador2 			= personajes->find(nombrePersonaje_delJugador2)->second;
		personajeDibujable_delJugador1  = personajesDibujables->find(nombrePersonaje_delJugador1)->second;
		personajeDibujable_delJugador2  = personajesDibujables->find(nombrePersonaje_delJugador2)->second;
	}

	// cargar el escenario grafico
	cargador_de_objetos.cargarEscenarioGrafico(personajeDibujable_delJugador1, personajeDibujable_delJugador2);

    pair<Personaje*, PersonajeDibujable*> jugador1(personaje_delJugador1, personajeDibujable_delJugador1);
    pair<Personaje*, PersonajeDibujable*> jugador2(personaje_delJugador2, personajeDibujable_delJugador2);
	Juego* juego = new Juego(jugador1, jugador2);

    return juego;
}

void correrJuego(Juego* g_game, bool& recargar){
	Logger::getInstance()->info("Juego corriendo");

    static const int FPS = 60;
    static const int DELAY_TIME = 1000.0f / FPS;
    Uint32 frameStart, frameTime;
    while (g_game->running())
    {

        frameStart = SDL_GetTicks();

        g_game->handleEvents(recargar);

        g_game->update();

        g_game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < DELAY_TIME)
            SDL_Delay((int)(DELAY_TIME - frameTime));
    }
    delete g_game;
    delete VentanaGrafica::Instance();
}

int main(int argc, char* args[])
{
	//para correr los test
	if ( argc > 1 )
	{
		string argumento(args[1]);
		Logger::getInstance()->info("argumento desde la consola: "+argumento);
		if ( argumento == "-test" )
		{
			Test tests;
			tests.ejecutar();
		}
		else
		{
			bool recargar = true;
			while (recargar){
				recargar = false;
				string escenario_path(argumento);
				Juego* juego = cargarJuego(argumento);
				correrJuego(juego, recargar);
			}

			Logger::getInstance()->info("#################################################");
			Logger::getInstance()->info("################## JUEGO FINALIZADO #############");
			Logger::getInstance()->info("#################################################");
		}
	}

	return 0;
}
