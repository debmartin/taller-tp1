#include "src/Game.h"
#include "test/Test.h"

int main(int argc, char* args[])
{	
	//para correr las pruebas comentar o descomentar estas 2 lineas
	Test tests;
	tests.ejecutar();

	Game* g_game = NULL;

	g_game = new Game();

	//levantar la información inicial mediante json
	//... usar libreria jsonCpp

	g_game->init("Chapter 1: Setting up SDL", 100, 100, 640, 480, false);

	while (g_game->running())
	{
		g_game->handleEvents();
		g_game->update();
		g_game->render();
	}

	g_game->clean();

	return 0;
}
