#include "src/Juego.h"
#include "test/Test.h"
#include "src/modelo/CargadorDeObjetos.h"

Juego* cargarJuego(string escenarioPath){
	Logger::getInstance()->info("#################################################");
	Logger::getInstance()->info("############ INICIA LA CARGA DEL JUEGO ##########");
	Logger::getInstance()->info("#################################################");

	CargadorDeOjbetos cargador_de_objetos(escenarioPath);

    list<Personaje*>* personajes = cargador_de_objetos.cargarPersonajes();
    list<PersonajeDibujable*>* personajesDibujables = cargador_de_objetos.cargarPersonajesDibujables();

    //cargo los personajes y personajes dibujables
	list<Personaje*>::iterator it_personajes = personajes->begin();
	list<PersonajeDibujable*>::iterator it_personajesDibujables = personajesDibujables->begin();

	Personaje* personaje1 = *(it_personajes++);
	Personaje* personaje2 = *(it_personajes);
	PersonajeDibujable* personajeDibujable1 = *(it_personajesDibujables++);
	PersonajeDibujable* personajeDibujable2 = *(it_personajesDibujables);

	// cargar el escenario grafico
	cargador_de_objetos.cargarEscenarioGrafico(personajeDibujable1, personajeDibujable2);

    std::pair<Personaje*, PersonajeDibujable*> jugador1(personaje1, personajeDibujable1);
    std::pair<Personaje*, PersonajeDibujable*> jugador2(personaje2, personajeDibujable2);
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
		/*
		if ( argumento == "-test" )
		{
			Test tests;
			tests.ejecutar();
          return 0;
		}
		*/
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

	return 0;
}
