#include "src/Juego.h"
#include "test/Test.h"
#include "src/modelo/CargadorDeObjetos.h"

int main(int argc, char* args[])
{
	//para correr los test
	if ( argc > 1 )
	{
		string parametro(args[1]);
		Logger::getInstance()->info("opcion_consola: "+parametro);
		if ( parametro == "-test" )
		{
			Test tests;
			tests.ejecutar();
		}
		else
		{
			string escenario_path(parametro);

			static const int FPS = 60;
			static const int DELAY_TIME = 1000.0f / FPS;

			Uint32 frameStart, frameTime;

			///////////////Inicializacion del Cargador de Objetos////
			CargadorDeOjbetos cargador_de_objetos;
			cargador_de_objetos.cargarObjetos(escenario_path);

			EscenarioGrafico* escenario = cargador_de_objetos.getEscenarioGrafico();
			Personaje* jugador = cargador_de_objetos.getPersonaje();
			PersonajeDibujable* personajeDibujable = cargador_de_objetos.getPersonajeDibujable();

			Juego g_game(VentanaGrafica::Instance(), escenario, jugador, personajeDibujable);

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

		}
	}

	return 0;
}
