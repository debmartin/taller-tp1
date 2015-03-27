#ifndef __Game__
#define __Game__
#include <vector>
#include <SDL2/SDL.h>
#include "vista/Sprite.h" // TODO: solo para test
#include <iostream>
#include <string>
using namespace std;

class Game {
private:
	bool m_bRunning;
	Sprite* sprSubZeroQuieto; // TODO: solo para test
	Sprite* sprSubZeroCaminando; // TODO: solo para test
public:

	Game(const char* title, int xpos, int ypos, int height, int width, bool fullscreen);
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
