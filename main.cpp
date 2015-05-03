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
	string id_personaje1 = cargador_de_objetos.cargarJugador1()->getIdPersonaje();
	string id_personaje2 = cargador_de_objetos.cargarJugador2()->getIdPersonaje();

    map<string, Personaje*>* personajes = cargador_de_objetos.cargarPersonajes();
    map<string, PersonajeDibujable*>* personajesDibujables = cargador_de_objetos.cargarPersonajesDibujables();
	Personaje* personaje1 = personajes->find(id_personaje1)->second;
	Personaje* personaje2 = personajes->find(id_personaje2)->second;
	PersonajeDibujable* personajeDibujable1 = personajesDibujables->find(id_personaje1)->second;
	PersonajeDibujable* personajeDibujable2 = personajesDibujables->find(id_personaje2)->second;

	/*
	 * verifico si los jugadores usan el mismo personaje
	 */
	if (id_personaje1 == id_personaje2)
	{
		//TODO terminar la implementacion del operador= para Personaje Y PersonajeDibujable
		if ( id_personaje1 == "personaje-1" )
		{
			//personaje2 = personaje1;
			// TODO verificar la direccion nueva
			personajeDibujable2 = personajeDibujable1->clonar();
		}
		else if ( id_personaje1 == "personaje-2" )
		{
			//personaje1 = personaje2;
			// TODO verificar la direccion nueva
			personajeDibujable1 = personajeDibujable2->clonar();
		}

		personajeDibujable2->cambiarColor(personajeDibujable1->getColorAlternativo());

	}

	// cargar el escenario grafico
	cargador_de_objetos.cargarEscenarioGrafico(personajeDibujable1, personajeDibujable2);

    pair<Personaje*, PersonajeDibujable*> jugador1(personaje1, personajeDibujable1);
    pair<Personaje*, PersonajeDibujable*> jugador2(personaje2, personajeDibujable2);
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
