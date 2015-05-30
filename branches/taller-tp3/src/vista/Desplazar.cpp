#include "Desplazar.h"

void Desplazar::H(SDL_Surface* sOriginal, Uint16 Hinicial, Uint16 Hfinal, Uint16 desplazamiento) {

	Uint8 r,g,b,a;
	Uint16 h,s,v;
	SDL_LockSurface(sOriginal);
	Uint32* pixel = (Uint32*) sOriginal->pixels;

	for (int i = 0; i < (sOriginal->w)*(sOriginal->h); i++) {
		SDL_GetRGBA(pixel[i], sOriginal->format, &r, &g, &b, &a);
		PixelColor::RGBtoHSV(r, g, b, h, s, v);

		if (estaEntre(h, Hinicial, Hfinal))
			h = desplazarH(h,desplazamiento);

		PixelColor::HSVtoRGB(h, s, v, r, g, b);
		pixel[i] = SDL_MapRGBA(sOriginal->format, r, g, b, a);
	}

	SDL_UnlockSurface(sOriginal);

}

Uint16 Desplazar::argumento(Uint16 argumento) {
	return argumento % 360;
}

Uint16 Desplazar::desplazarH(Uint16 anguloH, Uint16 offset) {
	return argumento(anguloH + offset);
}

bool Desplazar::estaEntre(Uint16 H, Uint16 Hinicial, Uint16 Hfinal) {
	return (Hinicial <= H && H <= Hfinal);
}
