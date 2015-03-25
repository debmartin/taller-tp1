#ifndef __Game__
#define __Game__
#include <vector>
#include <SDL2/SDL.h>

class Game {
private:
	bool m_bRunning;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	// SINGLETON
	Game(): m_bRunning(true), m_pWindow(NULL), m_pRenderer(NULL) {}
	static Game* s_pInstance;

public:

	SDL_Renderer* getRenderer() const { return  m_pRenderer; }
	bool init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool running();

	// create the public  instance function
	static Game* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}
};

typedef Game TheGame;

#endif /* defined (__Game__) */
