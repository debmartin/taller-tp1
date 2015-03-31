#include "src/Juego.h"
#include "test/Test.h"

#include "src/vista/VentanaGrafica.h"

#include <SDL2/SDL.h>

int main(int argc, char* args[])
{	
	static const int FPS = 60;
	static const int DELAY_TIME = 1000.0f / FPS;

	Uint32 frameStart, frameTime;

	//para correr las pruebas comentar o descomentar estas 2 lineas
	Test tests;
	tests.ejecutar();

	Juego g_game("Taller de programacion TP: Mortal Kombat", 100, 100, 640, 480, false);

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
