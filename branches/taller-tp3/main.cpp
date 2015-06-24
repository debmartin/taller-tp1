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

// variables globales
string idPersonaje1Elegido_g;
string idPersonaje2Elegido_g;
string modo_juego_g;
string nombrePersonajeElegido1_g;
string nombrePersonajeElegido2_g;

Juego* cargarJuego(string escenarioPath, int& cant_rounds){
	Logger::getInstance()->info("#################################################");
	Logger::getInstance()->info("############ INICIA LA CARGA DEL JUEGO ##########");
	Logger::getInstance()->info("#################################################");

	CargadorDeOjbetos cargador_de_objetos(escenarioPath);

	if ( (cant_rounds%2) == 1 )
	{
		cargador_de_objetos.cargarInfo_desdeMenus();

		// tomar la info desde los menus y cargarla en variables globales
		idPersonaje1Elegido_g = cargador_de_objetos.getIdPersonaje1Elegido();
		idPersonaje2Elegido_g = cargador_de_objetos.getIdPersonaje2Elegido();
		modo_juego_g = cargador_de_objetos.verModoDeJuego();
		nombrePersonajeElegido1_g = cargador_de_objetos.getNombrePersonajeElegido1();
		nombrePersonajeElegido2_g = cargador_de_objetos.getNombrePersonajeElegido2();
	}
	else
	{
		// recargar info que se cargaron en las variables globales de arriba
		cargador_de_objetos.setIdPersonaje1Elegido(idPersonaje1Elegido_g);
		cargador_de_objetos.setIdPersonaje2Elegido(idPersonaje2Elegido_g);
		cargador_de_objetos.setModoJuego(modo_juego_g);
		cargador_de_objetos.setNombrePersonajeElegido1(nombrePersonajeElegido1_g);
		cargador_de_objetos.setNombrePersonajeElegido2(nombrePersonajeElegido2_g);
	}

	Jugador* jugador1 = cargador_de_objetos.cargarJugador1();
	Jugador* jugador2 = cargador_de_objetos.cargarJugador2();

	if ( jugador1->getPersonaje()->getId() == jugador2->getPersonaje()->getId())
	{
		// TODO dejo de funcionar. no funcionaba antes de agregar las pantallas para el tp3
		ColorAlternativoDef* c = jugador1->getPersonajeDibujable()->getColorAlternativo();

		jugador2->getPersonajeDibujable()->cambiarColor(c);

	}
	cargador_de_objetos.cargarEscenarioGrafico(jugador1->getPersonajeDibujable(), jugador2->getPersonajeDibujable());

	//
	string modoJuego = cargador_de_objetos.verModoDeJuego();
	string nombrePersonaje1 = cargador_de_objetos.getNombrePersonajeElegido1();
	string nombrePersonaje2 = cargador_de_objetos.getNombrePersonajeElegido2();

	Juego* juego = new Juego(jugador1, jugador2, modoJuego, nombrePersonaje1, nombrePersonaje2);

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

void agregarSonidos()
{
	Sonidos::getInstancia()->iniciar();

	Sonidos::getInstancia()->agregar("sonido_saltar", new Sonido("crispy.wav",150,2));
	Sonidos::getInstancia()->agregar("sonido_saltar_sonya", new Sonido("Snyahup.wav",150,2));
	Sonidos::getInstancia()->agregar("sonido_pinia", new Sonido("Kungya.wav",150,2));
	Sonidos::getInstancia()->agregar("sonido_golpe_sonya", new Sonido("Snyaha.wav",150,2));
	Sonidos::getInstancia()->agregar("sonido_golpe2_sonya", new Sonido("Snyayah.wav",150,2));
	Sonidos::getInstancia()->agregar("sonido_patada", new Sonido("BigHit.wav",150,2));
	Sonidos::getInstancia()->agregar("sonido_deslizar", new Sonido("Kungaww.wav",150,2));
	Sonidos::getInstancia()->agregar("sonido_arma", new Sonido("LiuFire.wav",150,2));
	Sonidos::getInstancia()->agregar("sonido_arma_sub", new Sonido("SubIce2.wav",150,2));
	Sonidos::getInstancia()->agregar("sonido_arma_sonya", new Sonido("SnyaRing.wav",150,2));
	Sonidos::getInstancia()->agregar("sonido_gancho", new Sonido("NiteAxe.wav",150,2));
	Sonidos::getInstancia()->agregar("sonido_bebe", new Sonido("BabyCry.wav",150,2));
	Sonidos::getInstancia()->agregar("sonido_finish", new Sonido("FinHim2.wav",150,2));
	Sonidos::getInstancia()->agregar("sonido_sonya_win", new Sonido("SonyaWin1.wav",150,2));
	Sonidos::getInstancia()->agregar("sonido_subzero_win", new Sonido("SubWin1.wav",150,2));
}

int main(int argc, char* args[])
{
	//para correr los test
	if ( argc > 1 )
	{
		string argumento(args[1]);

		string archivo_configuracion(args[1]);
		Logger::getInstance()->iniciar(archivo_configuracion);

		Logger::getInstance()->info("argumento desde la consola: "+argumento);

		bool recargar = true;
		int cant_rounds = 1;
		while (recargar)
		{
			//Musica* musica = new Musica("mortal64.mid", 100);
			Musica* musica = new Musica("mortal-kombat-theme.mp3", 100);
			musica->reproducir();
			agregarSonidos();

			recargar = false;
			string escenario_path(argumento);
			Juego* juego = cargarJuego(argumento, cant_rounds);
			correrJuego(juego, recargar);
			cant_rounds++;

			musica->detener();
			delete musica;
		}

		Logger::getInstance()->info("#################################################");
		Logger::getInstance()->info("################## JUEGO FINALIZADO #############");
		Logger::getInstance()->info("#################################################");
	}

	return 0;
}
