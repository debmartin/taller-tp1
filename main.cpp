#include "src/Juego.h"
#include "test/Test.h"
#include "src/modelo/CargadorDeObjetos.h"

Juego* cargarJuego(string escenarioPath){
	Logger::getInstance()->info("#################################################");
	Logger::getInstance()->info("############ INICIA LA CARGA DEL JUEGO ##########");
	Logger::getInstance()->info("#################################################");

	CargadorDeOjbetos cargador_de_objetos(escenarioPath);
    Personaje* jugador = cargador_de_objetos.cargarPersonaje();
    PersonajeDibujable* personajeDibujable = cargador_de_objetos.cargarPersonajeDibujable();
    EscenarioGrafico* escenario = cargador_de_objetos.cargarEscenarioGrafico(personajeDibujable);

    Juego* juego = new Juego(escenario, jugador, personajeDibujable);

    //juego->agregarPersonajes(cargador_de_objetos.cargarPersonajes(), cargador_de_objetos.cargarPersonajesDibujables());

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
