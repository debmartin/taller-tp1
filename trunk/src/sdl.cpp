//============================================================================
// Name        : sdl.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

int main() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Quit();
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
