#ifndef __Game__
#define __Game__
#include <SDL2/SDL.h>
#include <iostream>

class Game {
private:
	bool m_bRunning;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

public:

	Game();
	~Game();

	bool init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool running();

};

#endif /* defined (__Game__) */
