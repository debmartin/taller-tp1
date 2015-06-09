#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <string>

#include "src/Juego.h"
#include "src/modelo/CargadorDeObjetos.h"
#include "src/modelo/Jugador.h"
#include "src/modelo/Personaje.h"
#include "src/Musica.h"
#include "src/Sonido.h"
#include "src/Sonidos.h"
#include "src/utils/Logger.h"
#include "src/vista/PersonajeDibujable.h"
#include "src/vista/VentanaGrafica.h"

Juego* cargarJuego(string escenarioPath){
	Logger::getInstance()->info("#################################################");
	Logger::getInstance()->info("############ INICIA LA CARGA DEL JUEGO ##########");
	Logger::getInstance()->info("#################################################");

	CargadorDeOjbetos cargador_de_objetos(escenarioPath);

	cargador_de_objetos.cargarInfo_desdeMenus();

	Jugador* jugador1 = cargador_de_objetos.cargarJugador1();
	Jugador* jugador2 = cargador_de_objetos.cargarJugador2();

	if ( jugador1->getPersonaje()->getId() == jugador2->getPersonaje()->getId())
	{
		// TODO dejo de funcionar. no funcionaba antes de agregar las pantallas para el tp3
		//jugador2->getPersonajeDibujable()->cambiarColor(jugador1->getPersonajeDibujable()->getColorAlternativo());
	}
	cargador_de_objetos.cargarEscenarioGrafico(jugador1->getPersonajeDibujable(), jugador2->getPersonajeDibujable());

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

        g_game->update(recargar);

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
//			Test tests;
//			tests.ejecutar();
		}
		else
		{
			Musica* musica = new Musica("mortal64.mid", 100);
			musica->reproducir();

			//carga de los sonidos
			Sonidos::getInstancia()->agregar("sonido_saltar", new Sonido("crispy.wav",150,2));
			Sonidos::getInstancia()->agregar("sonido_pinia", new Sonido("Kungya.wav",150,2));
			Sonidos::getInstancia()->agregar("sonido_patada", new Sonido("BigHit.wav",150,2));
			Sonidos::getInstancia()->agregar("sonido_deslizar", new Sonido("ShvDie.wav",150,2));
			Sonidos::getInstancia()->agregar("sonido_arma", new Sonido("LiuFire.wav",150,2));
			Sonidos::getInstancia()->agregar("sonido_gancho", new Sonido("NiteAxe.wav",150,2));
			Sonidos::getInstancia()->agregar("sonido_bebe", new Sonido("BabyCry.wav",150,2));

			bool recargar = true;
			while (recargar){
				recargar = false;
				string escenario_path(argumento);
				Juego* juego = cargarJuego(argumento);
				correrJuego(juego, recargar);
			}

			cout<<"detener sonidos"<<endl;
			musica->detener();
			delete musica;

			Logger::getInstance()->info("#################################################");
			Logger::getInstance()->info("################## JUEGO FINALIZADO #############");
			Logger::getInstance()->info("#################################################");
		}
	}

	return 0;
}
