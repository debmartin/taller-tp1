#include "src/Juego.h"
#include "test/Test.h"
#include "src/modelo/CargadorDeObjetos.h"

Juego* cargarObjetos(string escenarioPath){
    ///////////////Inicializacion del Cargador de Objetos////
    CargadorDeOjbetos cargador_de_objetos;
    cargador_de_objetos.cargarObjetos(escenarioPath);

    EscenarioGrafico* escenario = cargador_de_objetos.getEscenarioGrafico();
    Personaje* jugador = cargador_de_objetos.getPersonaje();
    PersonajeDibujable* personajeDibujable = cargador_de_objetos.getPersonajeDibujable();

    Juego* juego = new Juego(VentanaGrafica::Instance(), escenario, jugador, personajeDibujable);
    return juego;
}

void correrJuego(string escenarioPath, bool& recargar){
    Juego* g_game = cargarObjetos(escenarioPath);
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
//		if ( parametro == "-test" )
//		{
//			Test tests;
//			tests.ejecutar();
//		}
//		else
//		{
		    bool recargar = true;
		    while (recargar){
                recargar = false;
                string escenario_path(argumento);
                correrJuego(escenario_path, recargar);
		    }
//		}
	}

	return 0;
}
