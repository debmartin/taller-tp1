#ifndef DESPLAZAR_H_
#define DESPLAZAR_H_
#include <SDL2/SDL.h>
#include "PixelColor.h"
#include <iostream>

using namespace std;

class Desplazar{
	private:
		Desplazar();
		static Uint16 argumento(Uint16 argumento);
		static Uint16 desplazarH(Uint16 anguloH, Uint16 offset);
		static bool estaEntre(Uint16 H, Uint16 Hinicial, Uint16 Hfinal);
	public:
		virtual ~Desplazar();
		static void H(SDL_Surface* sOriginal, Uint16 Hinicial, Uint16 Hfinal, Uint16 desplazamiento);
};

#endif /* DESPLAZAR_H_ */
