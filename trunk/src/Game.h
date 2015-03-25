#ifndef __Game__
#define __Game__
#include <vector>
#include <SDL2/SDL.h>

#include <iostream>
#include <string>
using namespace std;

class Game {
private:
	bool m_bRunning;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	// SINGLETON
	Game();
	static Game* instancia_unica;

public:

	SDL_Renderer* getRenderer() const { return  m_pRenderer; }
	bool init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool running();
	~Game();

	// create the public  instance function
	static Game* Instance();
};

typedef Game TheGame;

#endif /* defined (__Game__) */
